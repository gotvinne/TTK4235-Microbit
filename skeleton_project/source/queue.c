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


void queue_attach_order_to_button_queue(Order new_o){
	p_button_queue[queue_size_of_button_queue()] = new_o;
}

//ikkje kommentert dette
void queue_remove_order_from_button_queue(){
	for(unsigned int i = 0; i < queue_size_of_button_queue(p_button_queue); i++){
		p_button_queue[i] = p_button_queue[i+1];
	}
}


int queue_floor_arrived(){
        if(current_floor == p_order_queue[0]){
                return 1;
        }
        return 0;
}

//veit ikkje om denne er heilt nødvendig å ha...
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

int queue_size_of_button_queue(b_q){
	int size = 0;
	while(b_q->floor_destination != -1){
		size++;
		b_q++;
	}
	return size;
}


void queue_initialize_empty_button_queue(){
	for(int i = 0; i < queue_size_of_button_queue(q_button_queue); i++){
		p_button_queue[i].floor_destination = -1;
		p_button_queue[i].order_type = HARDWARE_ORDER_INSIDE;
	}
}


