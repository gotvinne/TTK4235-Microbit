#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "esm.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    current_floor = esm_calculate_current_floor(esm_floor_peaks());
    int floors[4] = {0, 3, 1, 2};
    for(int i = 0; i < 4; i++){
	   hardware_command_set_elevator_movement(&floors[i]);
    }
    return 0;
}
