#include <stdio.h>
#include "eksempel_struktur.h"


int main(){
	eElevatorState eNextState = Calibrating;
	int in_floor = 0; //Bare en midlertidig variabel skal si om heisen er posisjonert en definert etasje eller ikkje.
	eElevatorEvent ReadEvents[6] = {Stop_Button_Pressed, Read_New_Order, Floor_Arrived, Read_New_Order, Floor_Arrived, Stop_Button_Pressed};
	eElevatorEvent ReadEvent = Stop_Button_Pressed;

	int runs = 0;
	while(runs != 6){
		printf("Run %d\n",runs);
		eElevatorEvent eNewEvent = ReadEvents[runs];
		switch(eNextState){
			case Calibrating:
				{
					printf("Calibrating...\n");
					eNextState = Moving;
					break;
				}
			case  Moving:
				{
					printf("Moving...\n");
					if(eNewEvent == Stop_Button_Pressed){
						printf("Stop_Button_Pressed.\n");
						eNextState = Stopped_Door_Closed;
						break;	
					}
					if(eNewEvent == Floor_Arrived){
						printf("You arrived your destination.\n");
						printf("Should delete order from queue.\n");
						eNextState = Stopped_Door_Closed;
						break;
					}
					if(eNewEvent == Read_New_Order){
						printf("Read_New_Order.\n");
						break;
					}
					break;
				}
			case Stopped_Door_Closed:
				{
					printf("Stopped_Door_Closed...\n");
					if(eNewEvent == Stop_Button_Pressed){
						//Should be in a loop while the stop button is pressed
                                                printf("Stop light on.\n");
                                                if(in_floor){
							eNextState = Stopped_Door_Open;
							break;
                                                }
                                                else{
                                                        printf("Doors are still closed. Not in a defined floor.\n");
                                               		break;
					       	}
					}
					if(eNewEvent == Floor_Arrived){
						printf("Floor_Arrived.\n");
						eNextState = Stopped_Door_Open;
						break;
					}
					if(eNewEvent == Read_New_Order){
						printf("Read_Floor_Order.\n");
						eNextState = Moving;
						break;
					}
					break;
				}
			case Stopped_Door_Open:
				{
					printf("Stopped_Door_Open...\n");
					while(eNewEvent == Stop_Button_Pressed){
						printf("Stop light on.\n");
						printf("Door open.\n");
					}
					printf("Door open in 3 sec.\n");
					eNextState = Stopped_Door_Closed;
					break;
				}

		}
		runs++;
	}
	return 0;
}
