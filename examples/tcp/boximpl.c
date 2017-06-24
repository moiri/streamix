#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

void* msg_init()
{
    int* init = malloc( sizeof( int ) );
    *init = 42;
    return ( void* )init;
}

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
    return SMX_BOX_TERMINATE;
}

int b( void* handler )
{
    smx_msg_t* msg = SMX_MSG_CREATE( msg_init, NULL, msg_destroy );
    sleep(1);
    SMX_CHANNEL_WRITE( handler, b, syn, msg );

    msg = SMX_CHANNEL_READ( handler, b, syn_ack );
    dzlog_info( "b, received data: %d", *( int* )msg->data );
    *( int* )msg->data += 5;

    sleep(1);
    SMX_CHANNEL_WRITE( handler, b, ack, msg );
    return SMX_BOX_TERMINATE;
}
