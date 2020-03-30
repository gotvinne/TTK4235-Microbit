#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "hardware.h"
#include "esm.h"




static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    
    
    while(1){
        int error = hardware_init();
        if(error != 0){
            fprintf(stderr, "Unable to initialize hardware\n");
            exit(1);
        }
        signal(SIGINT, sigint_handler);

       run_elevator();
    }

    return 0;
}
