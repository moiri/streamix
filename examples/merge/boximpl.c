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

int a( void* handler )
{
    smx_msg_t* msg_x = SMX_MSG_CREATE( msg_init, msg_copy, msg_destroy );
    *( char* )( msg_x->data ) = 'x';
    SMX_CHANNEL_WRITE( handler, a, x, msg_x );
    return SMX_BOX_TERMINATE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg == NULL )
        return SMX_BOX_TERMINATE;
    dzlog_info( "b, received data: %c", *( char* )msg->data );
    SMX_MSG_DESTROY( msg );
    return SMX_BOX_CONTINUE;
}
