/**
 * @author  ADD YOUR NAME
 * @file    m.c
 *
 * The implementation of the streamix box m.
 *
 * ADD DESCRITPTION HERE
 */

#include "smxrts.h"
#include "m.h"

/******************************************************************************/
int m( void* h, void* state )
{
    (void)(state);
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( h, m, x );
    if( msg == NULL ) return SMX_NET_END;
    SMX_CHANNEL_WRITE( h, m, x, msg );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void m_cleanup( void* h, void* state )
{
    ( void )( h );

    if( state == NULL )
        return;

    // FREE THE FIELDS OF THE STATE VARIABLE

    free( state );
}

/******************************************************************************/
int m_init( void* h, void** state )
{
    ( void )( h );
    *state = NULL;
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_m( void* h )
{
    return START_ROUTINE_NET( h, m );
}
