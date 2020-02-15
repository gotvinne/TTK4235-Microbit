#include "g_queue.h"
#include "user.h"
#include "hardware.h"


void setOrder(){
	//tester litt først. 
	int floor = 1;
	int test = hardware_read_order(floor, HARDWARE_ORDER_UP);
	if (test != 0){
		printf("Dette går ja!");
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

