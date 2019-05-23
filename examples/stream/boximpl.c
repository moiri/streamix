#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

void* a_init( void* handler )
{
    (void)(handler);
    printf( "enter any list of characters, followed by return\n" );
    printf( "ESC, followed by return will terminate the application\n" );
    return NULL;
}

void a_cleanup( void* state ) { (void)(state); }

int a( void* handler, void* state )
{
    char ch;
    char* data;
    smx_msg_t* msg;
    (void)(state);
    if( read(STDIN_FILENO, &ch, 1) > 0 )
    {
        data = malloc( sizeof( char ) );
        *data = ch;
        msg = SMX_MSG_CREATE( data, sizeof( char ), NULL, NULL, NULL );
        SMX_CHANNEL_WRITE( handler, a, x, msg );
        if( ch == ( char )27 )
            return SMX_NET_END;
    }
    return SMX_NET_CONTINUE;
}

void* b_init( void* handler )
{
    (void)(handler);
    return NULL;
}

void b_cleanup( void* state ) { (void)(state); }

int b( void* handler, void* state )
{
    smx_msg_t* msg;
    (void)(state);
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg != NULL ) {
        printf( "received data: %c\n", *( char* )msg->data );
        SMX_MSG_DESTROY( msg );
        sleep(1);
    }
    return 0;
}
