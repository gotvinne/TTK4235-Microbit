/**
 * @file
 * @brief The different states and events that can occure in the finite state machine.
 *
 */


/**
 * @brief Elevator state used in the switch in main.
 */
typedef enum{
	calibrating,
	moving,
	stopped_door_closed,
	stopped_door_open
}e_elevator_state;

/**
 * @brief Events that can occure in the different states in @c e_elevator_state
 */ 
typedef enum{
	stop_button_pressed,
	floor_arrived,
	read_new_order,
	obstruction_button_pressed,
	calibrating_finished,
}e_elevator_event;
