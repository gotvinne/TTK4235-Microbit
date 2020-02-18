#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "eksempel_struktur.h"
#include "hardware.h"
#include "user.h"

void run_elevator(){
	e_elevator_state e_next_state = calibrating;

	while(1){
		e_elevator_event e_new_event = user_read_event();
		switch(e_next_state){
			case calibrating:
				{
					printf("Calibrating...\n");
					hardware_calibrate();	
					e_next_state = stopped_door_closed;
					break;
				}
			case  moving:
				{
					printf("Moving...\n");
					hardware_command_set_elevator_movement(); //Her skal int peker til order_queue vere input
					if(e_new_event == stop_button_pressed){
						printf("Stop_Button_Pressed.\n");
						e_next_state = stopped_door_closed;
						break;	
					}
					if(e_new_event == floor_arrived){
						printf("You arrived your destination.\n");
						printf("Should delete order from queue.\n");
						e_next_state = stopped_door_closed;
						break;
					}
					if(e_new_event == execute_new_order){
						printf("Motor still driving.\n");
						if(p_order_queue[0] == -1){//viss ein ikkje har fleire bestillingar
							e_next_state = stopped_door_closed;
							break;
						}
						break;
					}
					break;
				}
			case stopped_door_closed:
				{
					printf("Stopped_Door_Closed...\n");
					if(e_new_event == stop_button_pressed){
						queue_clear_all_orders(); //Skal slette begge køene med bestillinger og destinasjoner
						printf("Stop light on.\n");
						hardware_command_stop_light(1);
                                               	if(esm_floor_peaks() != -1){//if in defined floor
							e_next_state = stopped_door_open;
							break;
                                               	}
                                               	else{
                                               	        printf("Doors are still closed. Not in a defined floor.\n");
							while(hardware_read_stop_button()){}//holder alt på pause så lenge stopknapp er inne
                                             		break;
					       	}
						hardware_command_stop_light(0);
						break;
					}
					if(e_new_event == floor_arrived){//usikker på denne
						printf("Floor_Arrived.\n");
						e_next_state = stopped_door_open;
						break;
					}
					if(e_new_event == execute_new_order){
						printf("Read_Floor_Order.\n");
						e_next_state = moving;
						break;
					}
					break;
				}
			case stopped_door_open:
				{
					printf("Stopped_Door_Open...\n");
					while(hardware_read_stop_signal()){
						printf("Stop light on.\n");
						hardware_command_stop_light(1);
						printf("Door open.\n");
						hardware_command_door_open(1);
					}
					printf("Door open in 3 sec.\n");
					hardware_command_door_open_3sec();
					e_next_state = stopped_door_closed;
					break;
				}

		}
	}
}
