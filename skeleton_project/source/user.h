#include "hardware.h"
/**
 * @brief user impementation
 * 
 */

/**
 * @brief order struct, holds @p order_floor and @p order_type
 */ 
typedef struct{
    int floor_destination; 
    HardwareOrder order_type; 
} Order; 

/**
 * @brief constructs Order struct
 * @param[in] order floor @p order_floor
 * @param[in] ordertype, up, down and inside @p order_type
 * @param[in] order pointer @p new. 
 */
Order user_make_order(int order_floor, HardwareOrder order_type);

/**
 * @brief add order struct into @p buttom_queue[]
 * @param[in] an const struct order @p new_order
 * 
 * @warning allocates a order pointer
 */
void user_set_order(const Order new_order);

/**
 * @brief Events that can occure in the different states in @c e_elevator_state
 */
typedef enum{
        stop_button_pressed,
        floor_arrived,
        obstruction_button_pressed,
	execute_new_order,
        calibrating_finished,
}e_elevator_event;


/**
 * @brief Finding what signals the user are triggering
 * @warning It exists events that the user can not do himself, but this is calibrating conditions (don't care)
 * @return Returns the event that the user is affecting the system with
 */
e_elevator_event user_read_event();

