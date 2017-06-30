#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>

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
    char* data2 = malloc( sizeof( char ) );
    smx_msg_t* msg;
    *data1 = 'x';
    msg = smx_msg_create( data1, sizeof( char ), msg_copy, msg_destroy );
    SMX_CHANNEL_WRITE( handler, a, x, msg );
    *data2 = 'y';
    msg = smx_msg_create( data2, sizeof( char ), msg_copy, msg_destroy );
    SMX_CHANNEL_WRITE( handler, a, y, msg );
    return SMX_BOX_TERMINATE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, y );
    dzlog_info( "b, received data_y: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    msg = SMX_CHANNEL_READ( handler, b, x );
    dzlog_info( "b, received data_x: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    return SMX_BOX_TERMINATE;
}
