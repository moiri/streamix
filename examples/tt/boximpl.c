#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

void msg_destroy( void* data )
{
    free( (char*)data );
}

void* msg_copy( void* data, size_t size )
{
    char* copy = malloc( size );
    *copy = *( char* )data;
    return ( void* )copy;
}

int a( void* handler )
{
    char* data1 = malloc( sizeof( char ) );
    smx_msg_t* msg;
    *data1 = 'x';
    msg = smx_msg_create( data1, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "sending data_x: %c", *( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a, x, msg );
    sleep(2);
    return SMX_BOX_CONTINUE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    dzlog_info( "received data_x: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    return SMX_BOX_CONTINUE;
}
