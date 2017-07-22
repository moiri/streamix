#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

int a( void* handler )
{
    char ch;
    char* data;
    smx_msg_t* msg;
    if( read(STDIN_FILENO, &ch, 1) > 0 )
    {
        data = malloc( sizeof( char ) );
        *data = ch;
        msg = smx_msg_create( data, sizeof( char ), NULL, NULL );
        SMX_CHANNEL_WRITE( handler, a, x, msg );
        if( ch == ( char )27 )
            return SMX_BOX_TERMINATE;
    }
    return SMX_BOX_CONTINUE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg != NULL ) {
        dzlog_info( "received data_x: %c", *( char* )msg->data );
        SMX_MSG_DESTROY( msg );
        sleep(1);
    }
    return 0;
}
