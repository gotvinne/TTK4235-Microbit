#include "user.h"
#include "hardware.h"
#include "queue.h"

#pragma once 


void new_order(int floor, HardwareOrder type, Order* new_o){
	new_o->floor_destination = floor;
	new_o->order_type = type; 
}


void set_order(const Order new_o){//Tror denne funksjonen er litt feil da den allokerer ny kø hver gang den kalles - Gunnar 
	p_buttom_queue = (Order*)malloc(sizeof(Order));
	*(p_buttom_queue+buttom_queue_length) = new_o; 
	buttom_queue_length++; 
}
 
e_elevator_event user_read_event(){
        if(hardware_read_stop_signal()){
                return stop_button_pressed;
        }
        if(current_floor == p_order_queue[0]){
                return floor_arrived;
        }
        if(hardware_read_obstruction_signal()){
                return obstruction_button_pressed;
        }
        if(hardware_init() == 0){
                return calibrating_finished;
        }
        return execute_new_order;
}

Order user_get_order(){
        Order ord;
	int floor_dest = -1;
	HardwareOrder ord_type = HARDWARE_ORDER_UP; //initialiseres slik default, endres på om nødvendig uansett
	for(unsigned int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
		for(unsigned int i = 0; i < 3; i++){//itererer over alle typer HardwareOrder
			HardwareOrder temp_ord_type = HARDWARE_ORDER_UP;
			if(i == hardware_order_type_bit(HARDWARE_ORDER_DOWN)){
                                temp_ord_type = HARDWARE_ORDER_DOWN;
                        }
			else if(i == hardware_order_type_bit(HARDWARE_ORDER_DOWN)){
				temp_ord_type = HARDWARE_ORDER_DOWN;
			}
			else if(i == hardware_order_type_bit(HARDWARE_ORDER_INSIDE)){
                                temp_ord_type = HARDWARE_ORDER_INSIDE;
                        }
			if(hardware_read_order(f,temp_ord_type)){
				floor_dest = f;
				ord_type = temp_ord_type;
				f = HARDWARE_NUMBER_OF_FLOORS; //Gjør at vi hopper ut av ytre loop
				i = 3; //Gjør at vi hopper ut av indre loop
				break;
			}

		}
	}
        ord.floor_destination = floor_dest;
        ord.order_type = ord_type;
        return ord;
}


