#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

void msg_destroy( void* data )
{
    free( (int*)data );
}

void* msg_copy( void* data, size_t size )
{
    int* copy = malloc( size );
    *copy = *( int* )data;
    return ( void* )copy;
}

int a( void* handler )
{
    static int count = 0;
    int* data1 = malloc( sizeof( int ) );
    smx_msg_t* msg;
    *data1 = count;
    msg = smx_msg_create( data1, sizeof( int ), msg_copy, msg_destroy );
    dzlog_info( "sending data_x: %d", *( int* )msg->data );
    SMX_CHANNEL_WRITE( handler, a, x, msg );
    count++;
    if(count > 5 )
        return SMX_NET_END;
    return SMX_NET_CONTINUE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg == NULL ) dzlog_info( "no data available on x" );
    else {
        dzlog_info( "received data_x: %d", *( int* )msg->data );
        SMX_MSG_DESTROY( msg );
    }
    return SMX_NET_RETURN;
}
