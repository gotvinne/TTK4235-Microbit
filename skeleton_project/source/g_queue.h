/**
 * @file
 * @brief Organizing the queue system
 */


/**
 * @brief Checkes if the elevator position is in the floor that is first in the queue @p p_order_queue.
 * @return Returns 1 if the elevator have arrived. 0 if not arrived.
*/
int queue_floor_arrived();


/**
 * @brief Checking if there exits an order in the queue.
 * @return Returns 0 if there is no elements in the queue. 1 if there is.
 */ 
int queue_execute_new_order();
