#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "queue.h"
#include "esm.h"

static int m_current_floor = 0;
//extern HardwareMovement last_movement;

int esm_floor_peaks(){
	int readed_floor = -1;
	for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
		if (hardware_read_floor_sensor(i) == 1){
			readed_floor = i;
		}
	}
	return readed_floor;
}

static int esm_calculate_current_floor(int peak, int* c_floor){
	switch(peak){
		case -1:
			return *c_floor;
		default:
			*c_floor = peak; 
			return peak; 
	}
}	

static ElevatorEvent esm_read_event(int floor_dest, int c_floor){
        if(c_floor == floor_dest && esm_floor_peaks() != -1){
                return FLOOR_ARRIVED;
		}
		
		else if (hardware_read_stop_signal()){
                return STOP_BUTTON_PRESSED;
        }
        
        else if (hardware_read_obstruction_signal()){
                return OBSTRUCTION_BUTTON_PRESSED;
        }
        return EXECUTE_NEW_ORDER;
}



void run_elevator(){
	hardware_calibrate();
	p_button_queue = (Order*)malloc(BUTTON_QUEUE_LENGTH*sizeof(Order));
	queue_initialize(p_button_queue);
	queue_set_button_lights(p_button_queue);
    ElevatorState e_next_state= STOPPED_DOOR_CLOSED;
	HardwareMovement last_movement = HARDWARE_MOVEMENT_UP;
	while(1){
        m_current_floor = esm_calculate_current_floor(esm_floor_peaks(),&m_current_floor);
		hardware_command_floor_indicator_on(m_current_floor);
        Order new_order = user_get_order();
		queue_attach_order(&new_order, p_button_queue);
		int floor_dest = queue_get_order_dest(p_button_queue,m_current_floor,last_movement);
		int last_valid_floor_dest = queue_last_valid_floor_dest(floor_dest);
		//HardwareMovement last_movement = hardware_get_priority_movement(m_current_floor, last_valid_floor_dest);
		//HardwareMovement last_active_movement = queue_last_active_dir(last_movement,m_current_floor,last_valid_floor_dest);
		ElevatorEvent e_new_event = esm_read_event(floor_dest, m_current_floor);
		// for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
		// 	printf("%d\t",p_button_queue[i].floor_destination);
		// }
		// printf("\n");
		if(last_movement == HARDWARE_MOVEMENT_UP){
			printf("LAST UP, floor dest = %d, last_valid_floor_dest = %d\n",floor_dest, last_valid_floor_dest);
		}
		else if(last_movement == HARDWARE_MOVEMENT_DOWN){
			printf("LAST DOWN, floor dest = %d, last_valid_floor_dest = %d\n",floor_dest, last_valid_floor_dest);
		}
		switch(e_next_state){
			case  MOVING:
				{
					queue_set_button_lights(p_button_queue);
					if(e_new_event == STOP_BUTTON_PRESSED){
						e_next_state = STOPPED_DOOR_CLOSED;
						break;	
					}
					if(e_new_event == FLOOR_ARRIVED){
						hardware_command_go_to(floor_dest,m_current_floor); //test dette 
						queue_remove_order(p_button_queue, m_current_floor);
						queue_set_button_lights(p_button_queue);
						e_next_state = STOPPED_DOOR_OPEN;
						break;
					}
					if(e_new_event == EXECUTE_NEW_ORDER || e_new_event == OBSTRUCTION_BUTTON_PRESSED){
						if(floor_dest == -1){//No orders to execute
							e_next_state = STOPPED_DOOR_CLOSED;
							break;
						}
						else if(floor_dest == m_current_floor && (esm_floor_peaks()==-1)){//Elevator not in defined floor
							if(last_movement == HARDWARE_MOVEMENT_UP){
								if(floor_dest <= last_valid_floor_dest){
									hardware_command_go_to(floor_dest, m_current_floor+1); //force down 
								}
								else{
									hardware_command_go_to(floor_dest, m_current_floor-1); //force up
								}
							}
							else if(last_movement == HARDWARE_MOVEMENT_DOWN){
								if(floor_dest >= last_valid_floor_dest){
									hardware_command_go_to(floor_dest, m_current_floor-1);
								}
								else{
									hardware_command_go_to(floor_dest, m_current_floor+1);
								}
							}
							queue_update_last_active_dir(&last_movement,m_current_floor,floor_dest);
							break;
						}
						else if(floor_dest != m_current_floor && (esm_floor_peaks()!=-1)){
							queue_update_last_active_dir(&last_movement,m_current_floor,floor_dest);
							hardware_command_go_to(floor_dest,m_current_floor);
							break;
						}
						else{
							hardware_command_go_to(queue_get_order_dest(p_button_queue,m_current_floor, last_movement),m_current_floor);
							break;
						}
						break;
					}
					break;
				}
			case STOPPED_DOOR_CLOSED:
				{
					queue_set_button_lights(p_button_queue);
					hardware_command_movement(HARDWARE_MOVEMENT_STOP);
					if(e_new_event == STOP_BUTTON_PRESSED){
						if(esm_floor_peaks() != -1){
							queue_initialize(p_button_queue);
							hardware_command_stop_light(1);
							hardware_command_door_open(1);
							e_next_state = STOPPED_DOOR_OPEN;
							break;
                        }
                        else{
							//ENDRET FRA last_movement til last_active_movement
							//last_movement = queue_last_active_dir(last_movement, m_current_floor,p_button_queue[0].floor_destination); //denne kan ikkje vere stopp
							queue_initialize(p_button_queue);
							hardware_command_stop_light(1);
							while(hardware_read_stop_signal()){
								
							}
							hardware_command_stop_light(0);
                            break;
					    }
						hardware_command_stop_light(0);
						break;
					}
					if(e_new_event == EXECUTE_NEW_ORDER){
						e_next_state = MOVING;
						break;
					}
					if(e_new_event == FLOOR_ARRIVED){
						queue_remove_order(p_button_queue, m_current_floor);
						queue_set_button_lights(p_button_queue);
						e_next_state = STOPPED_DOOR_OPEN;
						break;
					}
					if(e_new_event == OBSTRUCTION_BUTTON_PRESSED){
						e_next_state = MOVING;
					}
					break;
				}
			case STOPPED_DOOR_OPEN:
				{
					queue_remove_order(p_button_queue,m_current_floor);
					queue_set_button_lights(p_button_queue);
					
					if(e_new_event == STOP_BUTTON_PRESSED){
						while(hardware_read_stop_signal()){
							hardware_command_stop_light(1); 
							queue_initialize(p_button_queue);
						}
						hardware_command_stop_light(0);
						hardware_command_door_open_3_sec(m_current_floor);
					}
					else if(e_new_event == FLOOR_ARRIVED){
						queue_remove_order(p_button_queue,m_current_floor);
						queue_set_button_lights(p_button_queue);
						hardware_command_door_open_3_sec(m_current_floor);
					}
                    else if (e_new_event == OBSTRUCTION_BUTTON_PRESSED){
						hardware_command_door_open_3_sec(m_current_floor);
                    }
					else{
						hardware_command_door_open_3_sec(m_current_floor);
					}

					queue_set_button_lights(p_button_queue);
					hardware_command_door_open(0);
					e_next_state = STOPPED_DOOR_CLOSED;
					break;
				}
		}
	}
	free(p_button_queue);
}
