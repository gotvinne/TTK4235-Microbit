#include <stdio.h>
#include "g_queue.h"
#include "esm.h"
#include "hardware.h"


int queue_floor_arrived(){
        if(current_floor == p_order_queue[0]){
                return 1;
        }
        return 0;
}




int queue_execute_new_order(){
	s = 0;
	for(int i = 0, i < 4; i++){
		s += p_order_queue[i];
	}
	if(s==-4){
		return 0;
	}
	return 1;
}
