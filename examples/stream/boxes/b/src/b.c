/**
 * @author  Simon Maurer
 * @file    b.c
 *
 * The implementation of the streamix box b.
 *
 * ADD DESCRITPTION HERE
 */

#include <stdlib.h>
#include <unistd.h>
#include "smxrts.h"
#include "b.h"

/******************************************************************************/
int b( void* h, void* state )
{
    smx_msg_t* msg;
    (void)(state);
    msg = SMX_CHANNEL_READ( h, b, x );
    if( msg != NULL ) {
        printf( "received data: %c\n", *( char* )msg->data );
        SMX_MSG_DESTROY( h, msg );
        sleep(1);
    }
    return 0;
}

/******************************************************************************/
void b_cleanup( void* h, void* state )
{
    ( void )( h );
    ( void )( state );
}

/******************************************************************************/
int b_init( void* h, void** state )
{
    ( void )( h );
    ( void )( state );
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_b( void* h )
{
    return START_ROUTINE_NET( h, b );
}
