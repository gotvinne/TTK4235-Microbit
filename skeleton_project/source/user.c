#include "user.h"
#include "hardware.h"
#include "queue.h" 


Order user_make_order(int floor, HardwareOrder type){
	
	Order new;
	new.floor_destination = floor;
	new.order_type = type; 

	return new; 
	/*
	new_o->floor_destination = floor;
	new_o->order_type = type;
	*/
}//skal teste denne funksjonen. 


void user_set_order(const Order new_order){
	int i;
	for (i=0; i < BUTTON_QUEUE_LENGTH; i++){
	if (buttom_queue[i].floor_destination == -1){
	buttom_queue[i] = new_o;
	}
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

