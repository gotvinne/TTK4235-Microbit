#include "hardware.h"

#ifndef USER_H
#define USER_H

/**
 * @brief impementation of the user module 
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
 * @brief Constructs Order struct out of pulled buttons.
 */
Order user_get_order();


/**
 * @brief checks if @p new_order is a legal order
 * 
 * @param[in] new_order Order to be checked  
 * @return 1 if the @p new_order is legal, 0 if not. 
 */
int user_legal_order(Order new_order);

#endif


