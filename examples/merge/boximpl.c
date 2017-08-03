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
    char* data = malloc( sizeof( char ) );
    *data = 'x';
    smx_msg_t* msg_x = smx_msg_create( data, sizeof( char ), msg_copy,
            msg_destroy );
    dzlog_info( "send data: %c", *( char* )msg_x->data );
    SMX_CHANNEL_WRITE( handler, a, x, msg_x );
    return SMX_BOX_TERMINATE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg == NULL )
        dzlog_info( "no data available on x" );
    else {
        dzlog_info( "received data: %c", *( char* )msg->data );
        SMX_MSG_DESTROY( msg );
    }
    return 0;
}
