#ifndef ORDER_QUEUE_LENGTH
#DEFINE ORDER_QUEUE_LENGTH = 4 
/**
 * @file 
 * @brief queue implementation
 */

/**
 * @brief int array of size 4, holds the sequence of events
 */ 
int p_order_queue[ORDER_QUEUE_LENGTH] = {-1,-1,-1,-1};

/**
 * @brief that holds every upcomming order
 * 
 * @warning array size differs
 */ 
Order* p_buttom_queue;

/**
 * @brief holds the length of @p p_buttom_queue 
 * 
 */
int buttom_queue_length = 0; 

/**
 * @brief deletes order from @p p_buttom_queue
 */
void queue_delete_order();

/**
 * @brief puts correct order into @p p_order_queue
 */
void initialise_order(); 

/**
 * @brief deletes order from @p p_order_queue
 *  @warning frees allocated memory from array 
*/ 
void buttom_delete_order(); 

/**
 * @brief deletes all orders both from @p p_order_queue and @p p_buttom_queue 
 * @warning the function frees allokated memory
 */ 
void queue_clear_all_orders(); 

/**
 * @brief takes order in @p p_buttom_queue and inserts floor in @p p_order_queue 
 */ 
void attach_order_to_queue(Order* new_o)

/**
 * @brief sorts orders in @p p_order_queue depending on HardwareOrder
 */ 
void sort_order_queue(); 

#endif