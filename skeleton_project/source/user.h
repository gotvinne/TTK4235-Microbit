/**
 * @file
 * @brief User impementation
 * 
 */


/**
 * @brief Order struct, holds @p order_floor and @p order_type
 */ 
typedef struct{
    int floor_destination; 
    HardwareOrder order_type; 
} Order; 

/**
 * @brief Constructs Order struct
 * @param[in] order floor @p order_floor
 * @param[in] ordertype, up, down and inside @p order_type
 * @param[in] order pointer @p new. 
 */
void new_order(int order_floor, HardwareOrder order_type, Order* new_o);

/**
 * @brief Add order struct into @p p_buttom_queue[]
 * @param[in] A const struct order @p new_order
 * 
 * @warning Increments @p buttom_queue_length . 
 * @warning Allocates an order pointer
 */
void set_order(const Order new_o); 

/**
 * @brief Getting user input from panel both inside and outside the elevator and generates a @c Order out of it
 *
 * @return Returns an @c Order with including floor_destination and HardwareOrder.
 */
Order user_get_order();

/**
 * @brief Attaches the @p order to the global p_button_queue.
 * @param order Is the order from the panel. Using iser_get_order() as this parameter.
 */
void user_attach_order_to_button_queue();

/**
 * @brief Events that can occure in the different states in @c e_elevator_state
 */
typedef enum{
        stop_button_pressed,
        floor_arrived,
        obstruction_button_pressed,
       	calibrating_finished,
	execute_new_order
}e_elevator_event;


/**
 * @brief Finding what signals the user are triggering.
 * @warning It exists events that the user can not do himself, but this is calibrating conditions (don't care)
 * @return Returns the event that the user is affecting the system with
 */
e_elevator_event user_read_event();

