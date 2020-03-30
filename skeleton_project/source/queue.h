#include "user.h"
/**
 * @file 
 * @brief queue implementation
 */

#ifndef QUEUE_H
#define QUEUE_H
#define ORDER_QUEUE_LENGTH 4
#define BUTTON_QUEUE_LENGTH 10

/**
 * @brief Storing the floor the elevator should go to.
 *
 */ 
int order_dest;

/**
 * @brief Storing every button pushed, in the correct sequence they where pushed.
 * 
 * @warning Is not malloced or initialized. Will be malloced in beginning of esm.c and initialized by queue_initialize_empty_button_queue
 */ 
Order* p_button_queue; 

/**
 * @brief Calculates the size of the button_queue.
 *
 * @return Returns an int between 0 and BUTTON_QUEUE_LENGTH
 */
int queue_size(Order* p_b_q);


/**
 * @brief initialising @p buttom_queue with @c 15 Order struct.
 * @warning @p floor_destination is @c -1 and @p order_type is @c HARDWARE_ORDER_INSIDE by default
 */
void queue_initialize(Order* p_b_q);

/**
 * @brief Attaches an order @p o from the user in to the buttom_queue @p p_buttom_queue
 *
 * @param[in] o The order from the user
 * @param[in] p_b_q A pointer to the buttom queue
 */
void queue_attach_order(Order* new_o, Order* p_b_q);

/**
 * @brief Removes all orders with the given floor @p floor of the button_queue @p p_b_q 
 */
void queue_remove_order(Order* p_b_q, int floor);

/**
 * @brief Saves the last floor the elevator was moving towards
 * 
 * @return Return one the numbers between 0..3
 */
int queue_last_valid_floor_dest(int destination);

/**
 * @brief Saves the last direction the elevator was moving in, even when stop button pressed multiple times.
 * 
 */
void queue_update_last_active_dir(HardwareMovement* l_movement, int c_floor, int floor_dest);

/**
 * @brief Calculating the associated order_queue based on the button_queue.
 */
int queue_get_order_dest(Order* p_b_q, int c_floor, HardwareMovement l_movement);


/**
 * @brief Turns on all buttons that are triggered and not processed.
 * @warning This is more like a hardware function, but queue is not accessable in hardware.h.
*/
void queue_set_button_lights(Order* p_b_q);

/**
 * @brief 
 */
void queue_bubble_sort_dir(Order* p_b_q, HardwareMovement dir, int c_floor);

/**
 * @brief
 */
HardwareMovement move_from_last_valid_floor(HardwareMovement l_movement);

HardwareMovement queue_last_movement( Order* p_b_q, int c_floor);

#endif
