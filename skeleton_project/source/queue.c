#include "queue.h"
#include "user.h"


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


void queue_clear_all_orders(Order* b_q, int* o_q){
	for (unsigned int i = 0; i < ORDER_QUEUE_LENGTH; i++){
		o_q[i] = -1;
	}
	queue_initialize_empty_button_queue(b_q); 
}


void queue_attach_order_to_button_queue(Order new_o, Order* b_q){
        b_q[queue_size_of_button_queue(b_q)] = new_o;
}


void queue_remove_order_from_button_queue(Order* b_q){
        for(unsigned int i = 0; i < queue_size_of_button_queue(b_q); i++){
                b_q[i] = b_q[i+1];
        }
}

