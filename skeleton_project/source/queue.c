#include "queue.h"
#include "user.h"

void buttom_queue_init(){
	Order new_order;
	make_order(-1,HARDWARE_ORDER_INSIDE,&new_order);

for (unsigned int i = 0; i < BUTTOM_QUEUE_LENGTH; i++){
	buttom_queue[i] = (Order*)malloc(sizeof(Order));
	buttom_queue[i] = new_order; 
}

void queue_delete_order(unsigned int position){
	if (position > 3){
		printf("Error unvalid position\n");
		return; 
	}
	order_queue[position].floor_destination = -1; 
}

void buttom_delete_order(){


void queue_clear_all_orders(){
	
	for (unsigned int i = 0; i < ORDER_QUEUE_LENGTH; i++){
		queue_delete_order(i);
	}
	
	
}

void attatch_order_to_queue(Order* new_o){

    for (unsigned int i = 0; i < p_order_queue.size(); i++){
        
        if (p_order_queue[i] == -1){
            p_order_queue[i] = new_o->floor_destination; 
            return; 
        }
    }
    else{
        printf("Order-queue is full");
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




