#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

void* a( void* handler )
{
    char ch;
    smx_msg_t* msg;
    while(read(STDIN_FILENO, &ch, 1) > 0 )
    {
        msg = SMX_MSG_CREATE( NULL, NULL, NULL );
        msg->data = malloc( sizeof( char ) );
        *( char* )( msg->data ) = ch;
        SMX_CHANNEL_WRITE( handler, A, x, msg );
        if( ch == ( char )27 )
            break;
    }
    return NULL;
}

void* b( void* handler )
{
    smx_msg_t* msg;
    int run = 1;
    while( run ) {
        msg = SMX_CHANNEL_READ( handler, B, x );
        dzlog_info( "b, received data_x: %c", *( char* )msg->data );
        if( *( char* )msg->data == ( char )27 )
            run = 0;
        free( ( char* )msg->data );
        SMX_MSG_DESTROY( msg );
        sleep(1);
    }
    return NULL;
}
