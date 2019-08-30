/**
 * @author  ADD YOUR NAME
 *
 * The implementation of the streamix box r test functionality.
 */

#include "smxrts.h"
#include "r_msg.h"
#include "test_r.h"

/******************************************************************************/
smx_msg_t* r_in_data_conversion( void* h, const bson_value_t* data,
        ports_r_in_t idx )
{
    if( data == NULL )
        return NULL;

    // CHANGE THE FOLLOWING VARIABLES TO SUIT YOUR NEEDS

    void* msg_data = NULL;
    size_t size = 0;
    void* copy = NULL;
    void* destroy = NULL;
    void* unpack = NULL;

    // CHANGE THE CASES IN THE FOLLOWING SWITCH STATEMENT TO SUIT YOUR NEEDS

    switch( idx )
    {
        case SMX_PORT_IDX_r_in_x:

            // PERFORM TEST DATA CONVERSION

        break;
        default:
        break;
    }

    return SMX_MSG_CREATE( h, msg_data, size, copy, destroy, unpack );
}

/******************************************************************************/
int r_out_data_conversion( void* h, const bson_value_t* data,
        ports_r_out_t idx, smx_msg_t* msg )
{
    if( data == NULL )
        return -1;

    // CHANGE THE FOLLOWING VARIABLES TO SUIT YOUR NEEDS

    void* msg_data = SMX_MSG_UNPACK( msg );
    (void)(msg_data); // This is just here to prevent a warning.

    // CHANGE THE CASES IN THE FOLLOWING SWITCH STATEMENT TO SUIT YOUR NEEDS

    switch( idx )
    {
        default:
        break;
    }

    return 0;
}
