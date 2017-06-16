#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>

enum com_state_e { SYN, SYN_ACK, ACK, DONE };

void msg_destroy( void* data )
{
    free( (char*)data );
}

void* msg_copy( void* data )
{
    char* copy = malloc( sizeof( char ) );
    *copy = *( char* )data;
    return ( void* )copy;
}

void* msg_init()
{
    char* init = malloc( sizeof( char ) );
    *init = '0';
    return ( void* )init;
}

void* a( void* handler )
{
    smx_msg_t* msg_x = SMX_MSG_CREATE( msg_init, msg_copy, msg_destroy );
    smx_msg_t* msg_y = SMX_MSG_CREATE( msg_init, msg_copy, msg_destroy );
    *( char* )( msg_x->data ) = 'x';
    *( char* )( msg_y->data ) = 'y';
    SMX_CHANNEL_WRITE( handler, A, x, msg_x );
    SMX_CHANNEL_WRITE( handler, A, y, msg_y );
    return NULL;
}

void* b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, B, y );
    dzlog_info( "b, received data_y: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    msg = SMX_CHANNEL_READ( handler, B, x );
    dzlog_info( "b, received data_x: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    return NULL;
}
