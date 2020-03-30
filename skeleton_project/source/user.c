#include "user.h"
#include "hardware.h"
 


Order user_get_order(){
	int floor = -1;
	HardwareOrder o_type = HARDWARE_ORDER_INSIDE;
	for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                floor = f;
				o_type = HARDWARE_ORDER_INSIDE;
        }
	    else if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
            	floor = f;
                o_type = HARDWARE_ORDER_DOWN;
	    }
	    else if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                floor = f;
				o_type = HARDWARE_ORDER_UP;
	    }
    }
	Order new = {floor, o_type};
	return new; 
}


int user_legal_order(Order new_order){
	int floor = new_order.floor_destination;
	HardwareOrder type = new_order.order_type;
	if (floor >= 0 && floor <= 3 && (type == HARDWARE_ORDER_DOWN || type == HARDWARE_ORDER_UP || type == HARDWARE_ORDER_INSIDE)){
		return 1; 
	} 
	return 0; 
} 


