/**
 * @author  ADD AUTHOR NAME
 * @file    test_l.h
 *
 * This file holds custom definitions for the streamix box l in order
 * to perform testing.
 */

#include <bson.h>
#include "smxtypes.h"
#include "l_sig.h"

#ifndef BOX_TEST_l_H
#define BOX_TEST_l_H

/**
 * This function converts input test data provided in the configuration file
 * into a c format the box implementation will be able to accept.
 *
 * @param h
 *  The net handler.
 * @param data
 *  The test data for a specific input port.
 * @param idx
 *  The index of the port for which the conversion is performed.
 * @return
 *  A newly allocated streamix message.
 */
smx_msg_t* l_in_data_conversion( void* h, const bson_value_t* data,
        ports_l_in_t idx );

/**
 * This function converts output test data provided in the configuration file
 * into a c format and compares it to the data prodced by the box
 * implementation.
 *
 * @param h
 *  The net handler.
 * @param data
 *  The test data for a specific input port.
 * @param idx
 *  The index of the port for which the conversion is performed.
 * @param msg
 *  The message produced by the box implementation.
 * @return
 *  0 to simulate success, -1 to simulate failure
 */
int l_out_data_conversion( void* h, const bson_value_t* data,
        ports_l_out_t idx, smx_msg_t* msg );

#endif
