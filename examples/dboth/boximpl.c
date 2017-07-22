#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <unistd.h>

int a1( void* handler )
{
    static int count = 0;
    int* data = malloc( sizeof( int ) );
    *data = count;
    smx_msg_t* msg = smx_msg_create( ( void* )data, sizeof( int ), NULL, NULL );
    dzlog_info( "send data_x: %d", *( int* )msg->data );
    SMX_CHANNEL_WRITE( handler, a1, x, msg );
    sleep(2);
    count++;
    if( count > 5 ) return SMX_BOX_TERMINATE;
    return SMX_BOX_CONTINUE;
}

int a2( void* handler )
{
    static int count = 0;
    int* data1 = malloc( sizeof( int ) );
    int* data2 = malloc( sizeof( int ) );
    sleep(1);
    *data1 = count;
    smx_msg_t* msg = smx_msg_create( ( void* )data1, sizeof( int ),
            NULL, NULL );
    dzlog_info( "send data_y: %d", *( int* )msg->data );
    SMX_CHANNEL_WRITE( handler, a2, y, msg );
    count++;
    *data2 = count;
    msg = smx_msg_create( ( void* )data2, sizeof( int ),
            NULL, NULL );
    dzlog_info( "send data_y: %d", *( int* )msg->data );
    SMX_CHANNEL_WRITE( handler, a2, y, msg );
    count++;
    sleep(2);
    if( count > 9 ) return SMX_BOX_TERMINATE;
    return SMX_BOX_CONTINUE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    dzlog_info( "reading from x" );
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg == NULL ) {
        dzlog_info( "no data available on x" );
    }
    else {
        dzlog_info( "received data_x: %d", *( int* )msg->data );
        smx_msg_destroy( msg, 1 );
    }
    dzlog_info( "reading from y" );
    msg = SMX_CHANNEL_READ( handler, b, y );
    if( msg == NULL ) {
        dzlog_info( "no data available on y" );
    }
    else {
        dzlog_info( "received data_y: %d", *( int* )msg->data );
        smx_msg_destroy( msg, 1 );
    }
    return 0;
}
