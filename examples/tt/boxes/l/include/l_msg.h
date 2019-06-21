/**
 * @author  ADD AUTHOR NAME
 * @file    l_custom.h
 *
 * This file holds custom message data types for the streamix box l.
 *
 * Message data types must be allocated when creating a streamix message.
 * Functions that allow to free, copy, and unpack may be passed to the message
 * creation macro SMX_MSG_CREATE(). If NULL instead of these function
 * definitions is passed to SMX_MSG_CREATE the following default actions are
 * performed:
 * - copy:    return memcopy( data, size )
 * - destroy: free( data )
 * - unpack:  return data
 *
 * Note that a message data type must not necessary be a structure as suggested
 * below. If a basic type is used no custom data structure or custom copy,
 * free, or unpack function is required. However, the data **must** be
 * allocated in order to exist outside the scope of the net function.
 *
 * Further, note that only message types for output ports are prepared as
 * message types for input ports should be provided by the connecting box
 * implementation.
 */

#include <stdio.h>

#ifndef BOX_l_MSG_H
#define BOX_l_MSG_H

/** ::l_x_data_s */
typedef struct l_x_data_s l_x_data_t;

struct l_x_data_s
{
    // ADD MSG DATA FIELDS
};

/**
 * The custom copy function to perform a copy of the message data.
 *
 * @param data
 *  A void pointer to the data structure.
 * @param size
 *  The size of the data.
 * @return
 *  A void pointer to the copied data.
 */
void* l_x_copy( void* data, size_t size );

/**
 * The custom destroy function to destroy the data inside a message.
 *
 * @param data
 *  A void pointer to the data to be freed.
 */
void l_x_destroy( void* data );

/**
 * The custom unpack function for the message payload.
 *
 * @param data
 *  A void pointer to the message payload.
 * @return
 *  A void pointer to the unpacked message payload.
 */
void* l_x_unpack( void* data );


#endif
