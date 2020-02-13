
#include "user.h"
 


void setOrder(){
 
//tester litt først. 

int floor = 1;
int test = hardware_read_order(floor, HARDWARE_ORDER_UP);
if (test != 0){
	printf("Dette går ja!");
}	
}
