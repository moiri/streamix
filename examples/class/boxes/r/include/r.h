/**
 * @author  ADD AUTHOR NAME
 * @file    r_custom.h
 *
 * This file holds custom definitions for the streamix box r.
 * Use this file to define the state structure as well as auxilary functions.
 * The state structure allows to keep persistent information during net
 * iterations.
 *
 * The state structure must be allocated and initialized in the function
 * r_init() and freed in the function r_free().
 */

#include "r_sig.h"
#include "r_msg.h"

#ifndef BOX_r_H
#define BOX_r_H

/** ::r_state_s */
typedef struct r_state_s r_state_t;

/**
 * The state structure of r.
 */
struct r_state_s
{
    // ADD STATE FIELDS
};

/**
 * This function is the start routine which is passed to the thread. It
 * performs the work of the net. The function is executed periodically until
 * all consumers or producers of the net have terminated or SMX_NET_END is
 * returned.
 *
 * @param h
 *  A pointer to the net handler. This handler must be passed to most streamix
 *  macros but must not be modified.
 * @param state
 *  A pointer to the state variable of the net. This state variable must be
 *  allocated in r_init() and freed in r()_cleanup.
 * @return
 *  Either of the following values:
 *  - SMX_NET_RETURN: the RTS determines when the net is terminated.
 *  - SMX_NET_CONTINUE: forces the net to continue to operate.
 *  - SMX_NET_END: forces the net to terminate after the current iteration.
 */
int r( void* h, void* state );

/**
 * The cleanup function of the net. This function is executed once the net is
 * terminated (either automatically by the RTS or by returning SMX_NET_END in
 * r()).
 *
 * @param h
 *  A pointer to the net handler. This handler must be passed to most streamix
 *  macros but must not be modified.
 * @param state
 *  A pointer to the state variable of the net. This state variable must be
 *  freed here if it was allocated in 
 */
void r_cleanup( void* h, void* state );

/**
 * The initialisation function of the net. This function is executed before the
 * net thread is started. All nets have to complete their initialisation before
 * any net thread is started. Use this function to initialise the state variable
 * and assign initial values to fields as needed.
 *
 * @param h
 *  A pointer to the net handler. This handler must be passed to most streamix
 *  macros but must not be modified.
 * @param state
 *  A pointer to the state variable pointer. To access the state variable
 *  pointer dereference this arguments (i.e. *state = ...)
 * @return
 *  If the initialisation return 0. If the initialisation fails, return -1.
 *  Returning -1 will terminate (or rather never execute) the net.
 */
int r_init( void* h, void** state );

/**
 * This function is predefined and must not be changed. It will be passed to the
 * net thread upon creation and will be executed as soon as the thread is
 * started. This function calls a macro which is define in the RTS and handles
 * the initialisation, the main loop of the net and the cleanup.
 *
 * @param h
 *  A pointer to the net handler.
 * @return
 *  This function always returns NULL.
 */
void* start_routine_r( void* h );

#endif
