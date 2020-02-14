#include <stdio.h>
#include "eksempel_struktur.h"


int main(){
	e_elevator_state e_next_state = calibrating;
	int in_floor = 0; //Bare en midlertidig variabel skal si om heisen er posisjonert en definert etasje eller ikkje.
	e_elevator_event read_events[6] = {stop_button_pressed, read_new_order, floor_arrived, read_new_order, floor_arrived, stop_button_pressed};
	e_elevator_event read_event = stop_button_pressed;

	int runs = 0;
	while(runs != 6){
		printf("Run %d\n",runs);
		e_elevator_event e_new_event = read_events[runs];
		switch(e_next_state){
			case calibrating:
				{
					printf("Calibrating...\n");
					e_next_state = moving;
					break;
				}
			case  moving:
				{
					printf("Moving...\n");
					if(e_new_event == stop_button_pressed){
						printf("Stop_Button_Pressed.\n");
						e_next_state = stopped_door_closed;
						break;	
					}
					if(e_new_event == floor_arrived){
						printf("You arrived your destination.\n");
						printf("Should delete order from queue.\n");
						e_next_state = stopped_door_closed;
						break;
					}
					if(e_new_event == read_new_order){
						printf("Read_New_Order.\n");
						break;
					}
					break;
				}
			case stopped_door_closed:
				{
					printf("Stopped_Door_Closed...\n");
					if(e_new_event == stop_button_pressed){
						//Should be in a loop while the stop button is pressed
                                                printf("Stop light on.\n");
                                                if(in_floor){
							e_next_state = stopped_door_open;
							break;
                                                }
                                                else{
                                                        printf("Doors are still closed. Not in a defined floor.\n");
                                               		break;
					       	}
					}
					if(e_new_event == floor_arrived){
						printf("Floor_Arrived.\n");
						e_next_state = stopped_door_open;
						break;
					}
					if(e_new_event == read_new_order){
						printf("Read_Floor_Order.\n");
						e_next_state = moving;
						break;
					}
					break;
				}
			case stopped_door_open:
				{
					printf("Stopped_Door_Open...\n");
					while(e_new_event == stop_button_pressed){
						printf("Stop light on.\n");
						printf("Door open.\n");
					}
					printf("Door open in 3 sec.\n");
					e_next_state = stopped_door_closed;
					break;
				}

		}
		runs++;
	}
	return 0;
}
