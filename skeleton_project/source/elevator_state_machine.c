#include <stdio.h>
#include "hardware.h"
#include "channals.h"
#include "io.h"

#include <stdlib.h>

int elevator_state_machine_floor_peaks(){
	int readed_floor = -1;
	//Itererer over alle etasjesensorene
	for(int i = 0; i < 4; i++){
		if (hardware_read_floor_sensor(i) == 1){
			readed_floor = i;
		}
	}
	return readed_floor;
}

int elevator_state_machine_calculate_current_floor(int peak){
	switch(peak){
		case -1:
			return current_floor;
		default:
			return peak;
	}
}	

