/**
 * @author  ADD AUTHOR NAME
 * @file    b_msg.h
 *
 * This file holds custom message data types for the streamix box b.
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

#ifndef BOX_b_MSG_H
#define BOX_b_MSG_H


#endif
