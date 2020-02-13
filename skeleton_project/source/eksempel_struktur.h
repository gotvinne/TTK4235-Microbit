#include <stdio.h>

typedef enum{
	Calibrating,
	Moving,
	Stopped_Door_Closed,
	Stopped_Door_Open
}eElevatorState;


typedef enum{
	Stop_Button_Pressed,
	Floor_Arrived,
	Read_New_Order
}eElevatorEvent;
