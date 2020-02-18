#ifndef ORDER_QUEUE_LENGTH
#define ORDER_QUEUE_LENGTH 4
#define BUTTON_QUEUE_LENGTH 12
/**
 * @file 
 * @brief queue implementation
 */

/**
 * @brief int array of size 4, holds the sequence of events
 */ 
int* order_queue[ORDER_QUEUE_LENGTH] = {-1,-1,-1,-1};

/**
 * @brief that holds every upcomming order
 * 
 * @warning array size differs
 */ 
Order* buttom_queue[BUTTON_QUEUE_LENGTH]; 

/**
 * @brief Calculates the size of the button_queue.
 *
 * @return Returns an int between 0 and BUTTON_QUEUE_LENGTH
 */
int queue_size_of_button_queue(Order* b_q);

/**
 * @brief Deletes all orders in both button_queue and order_queue.
 */
void queue_clear_all_orders(Order* b_q, int* o_q);

/**
 * @brief initialising @p buttom_queue with @c 15 Order struct.
 * @warning @p floor_destination is @c -1 and @p order_type is @c HARDWARE_ORDER_INSIDE by default
 */
void queue_initialize_empty_buttom_queue();


/**
 * @brief Attaches an order @p o from the user in to the buttom_queue @p p_buttom_queue
 *
 * @param[in] o The order from the user
 * @param[in] p_b_q A pointer to the global buttom queue (should be p_buttom_queue)
 */
void queue_attach_order_to_button_queue(Order o, Order* p_b_q);

/**
 * @brief Removes the first order of the button queue
 */
void queue_remove_order_from_button_queue()

#endif
