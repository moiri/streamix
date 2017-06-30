#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>


int a( void* handler )
{
    static int count = 0;
    int* data  = malloc( sizeof( int ) );
    *data = count;
    smx_msg_t* msg_x = smx_msg_create( data, sizeof( int ), NULL, NULL );
    SMX_CHANNEL_WRITE( handler, a, x, msg_x );
    sleep(1);
    count++;
    if( count > 9 ) return SMX_BOX_TERMINATE;
    return SMX_BOX_CONTINUE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg == NULL ) return SMX_BOX_TERMINATE;
    dzlog_info( "b, received data_x: %d", *( int* )msg->data );
    SMX_MSG_DESTROY( msg );
    sleep(2);
    return SMX_BOX_CONTINUE;
}
