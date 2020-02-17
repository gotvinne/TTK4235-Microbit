#include "user.h"
#include "hardware.h"
#include "queue.h"
#pragma once 


void new_order(int floor, HardwareOrder type, Order* new_o){
	new_o->floor_destination = floor;
	new_o->order_type = type; 
}


void set_order(const Order new_o){ 
	p_buttom_queue = (Order*)malloc(sizeof(Order));
	*(p_buttom_queue+buttom_queue_length) = new_o; 
	buttom_queue_length++; 
}
 
e_elevator_event user_read_event(){
        if(hardware_read_stop_signal()){
                return stop_button_pressed;
        }
        if(queue_floor_arrived()){
                return floor_arrived;
        }
        if(hardware_read_obstruction_signal()){
                return obstruction_button_pressed;
        }
        if(queue_execute_new_order()){
                return execute_new_order;
        }
        if(hardware_init() == 0){
                return calibrating_finished;
        }
        return nothing;
}

