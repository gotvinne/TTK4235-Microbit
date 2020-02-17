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




