/**
 * @file
 * @brief Positioning of the elevator
 *
 */

#ifndef ESM_H
#define ESM_H


/**
 * @brief Finding floor number when the elevator passes the sensors
 *
 * @return Returns 0..3 (success), -1 (failure)
 */
int esm_floor_peaks();


// /**
//  * @brief Calculating the position of the elevator given the peak @p peak that
//  * should trig it to change.
//  *
//  * @param peak This peak is calculated by a function that finds the number of the floor.
//  *
//  * @warning Uses the hardware functions ...
//  * @return Returns an int 0..3 (success), or -1 (failure)
//  */
// int esm_calculate_current_floor(int peak, int* c_floor);
// //Trenge vi den? 

/**
 * @brief Elevator state used in the switch in main.
 */
typedef enum{
	MOVING,
	STOPPED_DOOR_CLOSED,
	STOPPED_DOOR_OPEN
}ElevatorState;

/**
 * @brief Events that can occure in the different states in @c e_elevator_state
 */ 
typedef enum{
	STOP_BUTTON_PRESSED,
	FLOOR_ARRIVED,
	EXECUTE_NEW_ORDER,
	OBSTRUCTION_BUTTON_PRESSED,
}ElevatorEvent;

// /**
//  * @brief Finding what signals the user are triggering
//  * @warning It exists events that the user can not do himself, like execute_new_order and floor_arrived
//  * @return Returns the event that the user is affecting the system with
//  */
// ElevatorEvent esm_read_event(int floor_dest, int c_floor);

/**
 * @brief The function with the arcitecture of the finite state machine.
 */
void run_elevator();

#endif
