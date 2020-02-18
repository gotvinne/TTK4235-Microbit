#include "queue.h"
#include "user.h"

void attatch_order_to_queue(Order* new_o){//Ikkje enig i denne grunna .size() - Gunnar

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


int queue_size_of_button_queue(Order* b_q){
	int size = 0;
	while(b_q->floor_destination != -1){
		size++;
		b_q++;
	}
	return size;
}


void queue_initialize_empty_button_queue(Order* b_q){
	for(int i = 0; i < queue_size_of_button_queue(b_q); i++){
		b_q[i].floor_destination = -1;
		b_q[i].order_type = HARDWARE_ORDER_INSIDE;
	}
}


void queue_attach_order_to_button_queue(Order new_o, Order* b_q){
        b_q[queue_size_of_button_queue(b_q)] = new_o;
}


void queue_remove_order_from_button_queue(Order* b_q){
        for(unsigned int i = 0; i < queue_size_of_button_queue(b_q); i++){
                b_q[i] = b_q[i+1];
        }
}

