/**
 * @author  Simon Maurer
 * @file    a.c
 *
 * The implementation of the streamix box a.
 *
 * ADD DESCRITPTION HERE
 */

#include <stdlib.h>
#include <unistd.h>
#include "smxrts.h"
#include "a.h"

/******************************************************************************/
int a( void* h, void* state )
{
    char ch;
    char* data;
    smx_msg_t* msg;
    (void)(state);
    if( read(STDIN_FILENO, &ch, 1) > 0 )
    {
        data = malloc( sizeof( char ) );
        *data = ch;
        msg = SMX_MSG_CREATE( h, data, sizeof( char ), NULL, NULL, NULL );
        SMX_CHANNEL_WRITE( h, a, x, msg );
        if( ch == ( char )27 )
            return SMX_NET_END;
    }
    return SMX_NET_CONTINUE;
}

/******************************************************************************/
void a_cleanup( void* h, void* state )
{
    ( void )( h );
    ( void )( state );
}

/******************************************************************************/
int a_init( void* h, void** state )
{
    ( void )( h );
    ( void )( state );
    printf( "enter any list of characters, followed by return\n" );
    printf( "ESC, followed by return will terminate the application\n" );
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_a( void* h )
{
    return START_ROUTINE_NET( h, a );
}
