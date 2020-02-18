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
int order_queue[ORDER_QUEUE_LENGTH] = {-1,-1,-1,-1};

/**
 * @brief that holds every upcomming order
 * 
 * @warning array size differs
 */ 
Order buttom_queue[BUTTON_QUEUE_LENGTH]; 

/**
 * @brief initialising @p buttom_queue with @c 15 Order struct.
 * @warning @p floor_destination is @c -1 and @p order_type is @c HARDWARE_ORDER_INSIDE by default
 */
void buttom_queue_init();


/**
 * @brief deletes order from @order_queue
 */
void queue_delete_order(unsigned int position);


/**
 * @brief Puts correct order into @p order_queue
 */
void initialise_order(); 

/**
 * @brief deletes oldest order from @p buttom_queue
 *  @warning frees allocated memory from array 
*/ 
void buttom_delete_order(); 

/**
 * @brief deletes all orders both from @p_order_queue and @p_buttom_queue 
 * @warning the function frees allokated memory
 */ 
void queue_clear_all_orders(); 

/**
 * @brief takes order in @p buttom_queue and inserts floor in @p order_queue 
 */ 
void attach_order_to_queue(Order* new_o)

/**
 * @brief sorts orders in @p order_queue depending on HardwareOrder
 */ 
void sort_order_queue(); 

#endif
