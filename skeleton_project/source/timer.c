#include "timer.h"
#include "queue.h"



static clock_t start_time;

int timer(int c_floor){
    start_time = clock();
    while((float)(clock()-start_time)/(CLOCKS_PER_SEC)<3){
        Order new_order = user_get_order();
        if(new_order.floor_destination != c_floor){
		    queue_attach_order(&new_order, p_button_queue);
        }
        if(hardware_read_obstruction_signal()){
            start_time = clock();
        }
        queue_set_button_lights(p_button_queue);
        while(hardware_read_stop_signal()){
            start_time = clock();
			hardware_command_stop_light(1);			
            queue_initialize(p_button_queue);
		}
		hardware_command_stop_light(0);
    }
    return 1;
}
