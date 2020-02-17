#include "queue.h"
#include "user.h"

void attatch_order_to_queue(Order* new_o){

    for (unsigned int i = 0; i < p_order_queue.size(); i++){
        
        if (p_order_queue[i] == -1){
            p_order_queue[i] = new_o->floor_destination; 
            break; //usikker her
        }
    }
    else{
        printf("Order-queue is full");
    }

}

void queue_initialize_empty_button_queue(Order* b_q){
        for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
		b_q->floor_destination = -1; //initialisering av etasje
                b_q->order_type = HARDWARE_ORDER_UP; //Bare en default retning i initialiseringa
        	b_q++;
}


void queue_add_button_order_from_user(Order user_order, Order* b_q){
	for(int i = 0; i < BUTTON_QUEUE_LENGTH; i++){
		if(b_q->floor_destination == -1){
			b_q->floor_destination = user_order.floor_destination;
			b_q->order_type = user_order.order_type;
		}
		else{
			b_q++;
		}
}


int queue_floor_arrived(){
        if(current_floor == p_order_queue[0]){
                return 1;
        }
        return 0;
}


int queue_execute_new_order(){
    int s = 0;
    for(int i = 0, i < 4; i++){
        s += p_order_queue[i];
    }
    if(s==-4){
        return 0;
    }
    return 1;
}




