#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>

enum com_state_e { SYN, SYN_ACK, ACK, DONE };

void msg_destroy( void* data )
{
    free( ( int* )data );
}

void* msg_copy( void* data, size_t size )
{
    int* copy = malloc( size );
    *copy = *( int* )data;
    return ( void* )copy;
}

int l( void* handler )
{
    int* data = malloc( sizeof( int ) );
    *data = 1;
    smx_msg_t* msg_x = smx_msg_create( data, sizeof( int ), msg_copy,
            msg_destroy );
    SMX_CHANNEL_WRITE( handler, l, x, msg_x );
    return SMX_BOX_TERMINATE;
}

int m( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, m, x );
    dzlog_info( "m, received: %d", *( int* )msg->data );
    ( *( int* )msg->data )++;
    SMX_CHANNEL_WRITE( handler, m, x, msg );
    return SMX_BOX_TERMINATE;
}

int r( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, r, x );
    dzlog_info( "r, received: %d", *( int* )msg->data );
    SMX_MSG_DESTROY( msg );
    return SMX_BOX_TERMINATE;
}
