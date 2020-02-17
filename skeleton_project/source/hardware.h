/**
 * @file
 * @brief Driver for the elevator hardware.
 *
 * Neatly wraps up Martin Korsgaard's spaghetti
 * from 2006 ;)
 *
 * Kolbjørn Austreng
 */
#ifndef HARDWARE_H
#define HARDWARE_H
#define HARDWARE_NUMBER_OF_FLOORS 4


/**
 * @brief Movement type used in @c hardware_command_movement.
 */
typedef enum {
    HARDWARE_MOVEMENT_UP,
    HARDWARE_MOVEMENT_STOP,
    HARDWARE_MOVEMENT_DOWN
} HardwareMovement;

/**
 * @brief Order type used in @c hardware_read_order
 * and in @c hardware_command_order_light.
 */
typedef enum {
    HARDWARE_ORDER_UP,
    HARDWARE_ORDER_INSIDE,
    HARDWARE_ORDER_DOWN
} HardwareOrder;

/**
 * @brief Initializes the elevator control hardware.
 * Must be called once before other calls to the elevator
 * hardware driver.
 *
 * @return 0 on success. Non-zero for failure.
 */
int hardware_init();

/**
 * @brief Commands the elevator to either move up or down,
 * or commands it to halt.
 *
 * @param movement Commanded movement.
 */
void hardware_command_movement(HardwareMovement movement);

/**
 * @brief Polls the hardware for the current stop signal.
 *
 * @return 1 if the stop signal is high; 0 if it is low.
 */
int hardware_read_stop_signal();

/**
 * @brief Polls the hardware for the current obstruction signal.
 *
 * @return 1 if the obstruction signal is high; 0 if it is low.
 */
int hardware_read_obstruction_signal();

/**
 * @brief Polls the floor sensor for the given @p floor.
 *
 * @param floor Inquired floor.
 *
 * @return 1 if the elevator is at @p floor, otherwise 0;
 */
int hardware_read_floor_sensor(int floor);

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
int hardware_read_order(int floor, HardwareOrder order_type);

/**
 * @brief Commands the hardware to open- or close the elevator door.
 *
 * @param door_open A truthy value (non-zero) to open the door;
 * 0 to close.
 */
void hardware_command_door_open(int door_open);

/**
 * @brief Commands the hardware to turn on the floor indicator
 * for @p floor. All indicators all mutually exclusive; other
 * indicator lights will turn off.
 *
 * @param floor Floor to turn on the indicator for.
 *
 * @warning Owing to peculiarities in the hardware construction,
 * there will always be one indicator active.
 */
void hardware_command_floor_indicator_on(int floor);

/**
 * @brief Sets the light in the panel stop button.
 *
 * @param on A truthy value (non-zero) to turn the light on;
 * 0 to turn it off.
 */
void hardware_command_stop_light(int on);


/**
 * @brief Sets the light in a button corresponding to an order
 * of type @p order_type, at floor @p floor.
 *
 * @param floor The floor of the order indicator.
 * @param order_type The type of order.
 * @param on A truthy value (non-zero) to turn the light on;
 * 0 to turn it off.
 */
void hardware_command_order_light(int floor, HardwareOrder order_type, int on);

/**
 * @brief Sets the requiered movement to the elevator to reach the next floor in the queue @p p_queue given its position
 *
 * @param p_queue An int pointer to the next floor the elevator should be in.
 * @warning Its position is calculated by esm_current_floor()
 * in esm.h
 * 
 */
void hardware_command_set_elevator_movement(int* p_queue);

/**
 * @brief Open the door in three seconds if in defined floor.
 * @return Returns 0 if it opens. -1 if the door did not open.
 */
int hardware_command_door_open_3_sec();

/**
 * @brief Makes the elevator stop when the stop button is pressed.
 * Tries to open door if in defined floor.
 */
void hardware_command_stop_button_pressed_actions();

/**
 * @brief Turn off all order ligths. 
 */
void hardware_clear_all_order_lights();

/**
 * @brief Set all lights that should be on, depending on @p current_floor,
 * the button queue @p p_button_queue and the size of this queue @p size_of_p_button_queue
 * 
 * @param p_button_queue A pointer to an @p Order struct
 * @param size_of_p_button_queue An int representing the size of the p_button_queue array.
*/
void hardware_set_all_lights(Order* p_button_queue, int size_of_p_button_queue);

/**
 * @brief Initializes the hardware and io and makes the elevator go to the first floor.
 */
void hardware_calibrate();


#endif
