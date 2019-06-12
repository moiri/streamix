#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

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

void a_cleanup( void* h, void* state )
{
    ( void )( h );
    ( void )( state );
}

int a_init( void* h, void** state )
{
    ( void )( h );
    ( void )( state );
    printf( "enter any list of characters, followed by return\n" );
    printf( "ESC, followed by return will terminate the application\n" );
    return 0;
}

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

void b_cleanup( void* h, void* state )
{
    ( void )( h );
    ( void )( state );
}

int b_init( void* h, void** state )
{
    ( void )( h );
    ( void )( state );
    return 0;
}
