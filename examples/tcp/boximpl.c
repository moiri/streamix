#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

void msg_destroy( void* data )
{
    free( ( int* )data );
}

int a( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, a, syn );
    dzlog_info( "a, received data: %d", *( int* )msg->data );
    *( int* )msg->data -= 3;

    sleep(1);
    SMX_CHANNEL_WRITE( handler, a, syn_ack, msg );

    msg = SMX_CHANNEL_READ( handler, a, ack );
    dzlog_info( "a, received data: %d", *( int* )msg->data );
    SMX_MSG_DESTROY( msg );
    return SMX_NET_END;
}

int b( void* handler )
{
    int* data = malloc( sizeof( int ) );
    *data = 42;
    smx_msg_t* msg = smx_msg_create( data, sizeof( int ), NULL, msg_destroy );
    sleep(1);
    SMX_CHANNEL_WRITE( handler, b, syn, msg );

    msg = SMX_CHANNEL_READ( handler, b, syn_ack );
    dzlog_info( "b, received data: %d", *( int* )msg->data );
    *( int* )msg->data += 5;

    sleep(1);
    SMX_CHANNEL_WRITE( handler, b, ack, msg );
    return SMX_NET_END;
}
