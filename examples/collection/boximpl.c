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

int l( void* handler )
{
    smx_msg_t* msg_x = SMX_MSG_CREATE( msg_init, msg_copy, msg_destroy );
    *( char* )( msg_x->data ) = '1';
    SMX_CHANNEL_WRITE( handler, l, x, msg_x );
    return SMX_BOX_TERMINATE;
}

int m( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, m, x );
    dzlog_info( "m, received: %c", *( char* )msg->data );
    *( char* )msg->data = '2';
    SMX_CHANNEL_WRITE( handler, m, x, msg );
    return SMX_BOX_TERMINATE;
}

int r( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, r, x );
    dzlog_info( "r, received: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    return SMX_BOX_TERMINATE;
}
