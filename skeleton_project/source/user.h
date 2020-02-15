/**
 * @file
 * @brief Organizing the user inputs.
 *
 */ 


int stopButton; 

void setOrder();  

/**
 * @brief Events that can occure in the different states in @c e_elevator_state
 */
typedef enum{
        stop_button_pressed,
        floor_arrived,
        obstruction_button_pressed,
	execute_new_order,
        calibrating_finished,
	nothing
}e_elevator_event;


/**
 * @brief Finding what signals the user are triggering
 * @warning It exists events that the user can not do himself, but this is calibrating conditions (don't care)
 * @return Returns the event that the user is affecting the system with
 */
e_elevator_event user_read_event();
