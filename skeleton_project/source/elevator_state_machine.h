/**
 * @file
 * @breif Positioning of the elevator
 *
 */

/**
 * @brief The int that holds the elevators current floor.
 *
 * @warning Initialized as 0.
 */
int current_floor = 0;


/**
 * @brief Finding floor number when the elevator passes the sensors
 *
 * @return Returns 0..3 (success), -1 (failure)
 */
int elevator_state_machine_floor_peaks();


/**
 * @brief Calculating the position of the elevator given the peak @p peak that
 * should trig it to change.
 *
 * @param peak This peak is calculated by a function that finds the number of the floor.
 *
 * @warning Uses the hardware functions ...
 * @return Returns an int 0..3 (success), or -1 (failure)
 */
int elevator_state_machine_calculate_current_floor(int peak);
