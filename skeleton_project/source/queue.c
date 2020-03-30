#include "queue.h"
#include "hardware.h"
#include  "esm.h"
#include <stdlib.h>
#include <stdio.h>


int queue_size(Order* p_b_q){
	int size = 0;
	for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
		if(p_b_q[i].floor_destination == -1){
			return size;
		}
		size++;
		
	}
	return size;
}


void queue_initialize(Order* p_b_q){
	Order init = {-1, HARDWARE_ORDER_INSIDE};
	for (int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
		p_b_q[i] = init; 
	}
}

static int queue_unique_button(Order new_order, Order* p_b_q){
	int u_floor = new_order.floor_destination;
	HardwareOrder u_order = new_order.order_type;
	for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
       if((p_b_q[i].floor_destination == u_floor) && (p_b_q[i].order_type == u_order)){
		   return 0;
	   }
    }
	return 1;
} 

void queue_attach_order(Order* new_o, Order* p_b_q){
	if(user_legal_order(*new_o) && queue_unique_button(*new_o,p_b_q)){
        p_b_q[queue_size(p_b_q)] = *new_o;
	}
}


void queue_remove_order(Order* p_b_q, int floor){
    if(floor != -1){
		for(unsigned int i = 0; i < BUTTON_QUEUE_LENGTH-1; i++){
        	if(p_b_q[i].floor_destination == floor){
				for(int j = i; j < BUTTON_QUEUE_LENGTH-1; j++){
						p_b_q[j] = p_b_q[j+1];
				}
				if (i != 0){
				p_b_q[BUTTON_QUEUE_LENGTH-1].floor_destination = -1;
      			p_b_q[BUTTON_QUEUE_LENGTH-1].order_type = HARDWARE_ORDER_INSIDE;
				}
			}	
    	}
	}
}

int queue_last_valid_floor_dest(int destination){
	static int m_last_dest;
	if(destination == -1){
		return m_last_dest;
	}
	m_last_dest = destination;
	return m_last_dest;
}


HardwareMovement move_from_last_valid_floor(HardwareMovement l_movement){
	static HardwareMovement m_last_dir_from_def_floor; 
	if (esm_floor_peaks() == -1){
		return m_last_dir_from_def_floor;
	}
	m_last_dir_from_def_floor = l_movement; 
	return m_last_dir_from_def_floor;
}

static int queue_under_current_floor(HardwareMovement move_from_last_valid_floor){
	if (move_from_last_valid_floor == HARDWARE_MOVEMENT_DOWN){
		return 1;
	}
	return 0; 
}

static int queue_passed_floor(int floor, int c_floor, int under, HardwareMovement dir){
	if (dir == HARDWARE_MOVEMENT_UP){
		if(c_floor < floor){
			return 0; 
		}
		else if(c_floor == floor){
			if (under && esm_floor_peaks() != -1){
				return 0; 
			}
			return 1;
		}
		return 1;
	}
	else {
		if(c_floor > floor){
			return 0;
		}
		else if(c_floor == floor){
			if (!under && esm_floor_peaks() != -1){
				return 0;
			}
			return 1;
		}
		return 1; 
	}
}


static int queue_legal_swap(int c_floor, int j, Order* p_b_q, HardwareMovement dir){
	//HardwareMovement l_movement = move_from_last_valid_floor(dir);
	int under = queue_under_current_floor(dir);
	if(dir == HARDWARE_MOVEMENT_UP){
		if(((p_b_q[j].floor_destination > p_b_q[j+1].floor_destination)) && (p_b_q[j+1].order_type != HARDWARE_ORDER_DOWN)){
			if(!queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under, dir)){
				return 1;
			}
		}
		else if(p_b_q[j+1].order_type == HARDWARE_ORDER_INSIDE && p_b_q[j].order_type == HARDWARE_ORDER_INSIDE && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under,dir)){
			return 1;
		}
		else if(p_b_q[j+1].order_type == HARDWARE_ORDER_DOWN && p_b_q[j].order_type == HARDWARE_ORDER_DOWN && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under,dir)){
			if(p_b_q[j+1].floor_destination > p_b_q[j].floor_destination){
				return 1;
			}
			return 0;
		}
		// else if(under && p_b_q[j+1].order_type == HARDWARE_ORDER_UP && p_b_q[j].order_type == HARDWARE_ORDER_DOWN && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor-1,under,dir)){
		// 	return 1;
		// }
		// else if(p_b_q[j+1].order_type == HARDWARE_ORDER_DOWN && p_b_q[j].order_type == HARDWARE_ORDER_UP && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under,dir)){
		// 	return 1;
		// }
		else{
			return 0;
		}
	}
	else if(dir == HARDWARE_MOVEMENT_DOWN){
		if(((p_b_q[j].floor_destination < p_b_q[j+1].floor_destination)) && (p_b_q[j+1].order_type != HARDWARE_ORDER_UP)){
			if(!queue_passed_floor(p_b_q[j+1].floor_destination,c_floor, under, dir)){
				return 1;
			}
		}
		else if(p_b_q[j+1].order_type == HARDWARE_ORDER_INSIDE && p_b_q[j].order_type == HARDWARE_ORDER_INSIDE && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under,dir)){
			return 1;
		}
		else if(p_b_q[j+1].order_type == HARDWARE_ORDER_UP && p_b_q[j].order_type == HARDWARE_ORDER_UP && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under,dir)){
			if(p_b_q[j+1].floor_destination < p_b_q[j].floor_destination){
				return 1;
			}
			return 0;
		}
		// else if(p_b_q[j+1].order_type == HARDWARE_ORDER_UP && p_b_q[j].order_type == HARDWARE_ORDER_DOWN && queue_passed_floor(p_b_q[j+1].floor_destination,c_floor-1,under,dir)){
		// 	return 1;
		// }
		// else if(p_b_q[j+1].order_type == HARDWARE_ORDER_DOWN && p_b_q[j].order_type == HARDWARE_ORDER_UP && !queue_passed_floor(p_b_q[j+1].floor_destination,c_floor,under,dir)){
		// 	return 1;
		// }
		else{
			return 0;
		}
	}
	return 0;
}

void queue_bubble_sort_dir(Order* p_b_q, HardwareMovement dir, int c_floor){ //fjernet static
	if(dir == HARDWARE_MOVEMENT_UP){
		//printf("UP sorting\n");
		for(unsigned int i = 0; i < queue_size(p_b_q); i++){
			for(unsigned int j = 0; j < queue_size(p_b_q) -i -1; j++){
				if(queue_legal_swap(c_floor,j,p_b_q,dir)){
					Order swap = p_b_q[j];
                    p_b_q[j] = p_b_q[j+1];
                    p_b_q[j+1] = swap;
                }
            }
    	}
	}
	else if(dir == HARDWARE_MOVEMENT_DOWN) {
		//printf("DOWN sorting\n");
		for(unsigned int i = 0; i < queue_size(p_b_q); i++){
			for(unsigned int j = 0; j < queue_size(p_b_q) -i -1; j++){
                if(queue_legal_swap(c_floor,j,p_b_q,dir)){
					Order swap = p_b_q[j];
                    p_b_q[j] = p_b_q[j+1];
                    p_b_q[j+1] = swap;
					
                }
            }
        }
	}
}

void queue_update_last_active_dir(HardwareMovement* l_movement, int c_floor, int floor_dest){
	static HardwareMovement saved_movement;
	if(c_floor < floor_dest){
		*l_movement = HARDWARE_MOVEMENT_UP;
	}
	else if(c_floor > floor_dest){
		*l_movement = HARDWARE_MOVEMENT_DOWN;
	}
	else{
		*l_movement = saved_movement;
	}
	saved_movement = *l_movement;
}



int queue_get_order_dest(Order* p_b_q, int c_floor, HardwareMovement l_movement){
	//HardwareMovement priority_movement = hardware_get_priority_movement(c_floor,p_b_q[0].floor_destination);
	queue_bubble_sort_dir(p_b_q, l_movement,c_floor);
	return p_b_q[0].floor_destination;
}

void queue_set_button_lights(Order* p_b_q){
		
        HardwareOrder order_types[3] = {
                HARDWARE_ORDER_UP,
                HARDWARE_ORDER_INSIDE,
                HARDWARE_ORDER_DOWN
        };
		for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        	for(int i = 0; i < 3; i++){
            	HardwareOrder type = order_types[i];
            	hardware_command_order_light(f, type, 0);
        	}
    	}
        for(int j = 0; j < queue_size(p_b_q); j++){
                for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
                        for(int i = 0; i < 3; i++){
                                HardwareOrder type = order_types[i];
                                if(p_b_q[j].order_type == type && p_b_q[j].floor_destination == f){
                                        hardware_command_order_light(f, type, 1);
                                }
                                else{
                                        hardware_command_order_light(f, type, 0);
                                }
                        }
                }
        }
}

HardwareMovement queue_last_movement(Order* p_b_q, int c_floor){
    static HardwareMovement l_movement = HARDWARE_MOVEMENT_UP;
    int change; 

	switch (l_movement){
		case HARDWARE_MOVEMENT_UP:
		{
		if (queue_size(p_b_q) == 0){
			change = 0; 
			break;
		}
		for (int i = 0; i <= queue_size(p_b_q); i++){
            if (p_b_q[i].floor_destination > c_floor){
                change = 0; 
				break;
            }
        }
		change = 1; 
		break;
		}
		case HARDWARE_MOVEMENT_DOWN:{
		if (queue_size(p_b_q) == 0){
			change = 0; 
			break;
		}
		for (int i = 0; i <= queue_size(p_b_q); i++){
            if (p_b_q[i].floor_destination < c_floor){
                change = 0; 
				break;
            }
        }
		change = 1;
		break; 
		}
		case HARDWARE_MOVEMENT_STOP:
		{
			printf("VI er i stopptilstand!");
			break;
		}
	};

    if (change == 1){
        if (l_movement == HARDWARE_MOVEMENT_UP){
            l_movement = HARDWARE_ORDER_DOWN;
			printf("DOWN\n");
        }
        else {
            l_movement = HARDWARE_ORDER_UP;
			printf("UP\n");
        }
    }
    return l_movement; 
}


