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

int a1( void* handler )
{
    char* data;
    smx_msg_t* msg;

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "x1" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_x: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a1, x, msg );

    dzlog_info( "wait 1s" );
    sleep(1);

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "x2" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_x: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a1, x, msg );

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "x3" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_x: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a1, x, msg );

    dzlog_info( "wait 2s" );
    sleep(2);

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "x4" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_x: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a1, x, msg );

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "x5" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_x: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a1, x, msg );

    return SMX_BOX_TERMINATE;
}

int a2( void* handler )
{
    char* data;
    smx_msg_t* msg;

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "y1" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_y: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a2, y, msg );

    dzlog_info( "wait 1s" );
    sleep(1);

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "y2" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_y: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a2, y, msg );

    dzlog_info( "wait 1s" );
    sleep(1);

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "y3" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_y: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a2, y, msg );

    dzlog_info( "wait 2s" );
    sleep(2);

    data = malloc( sizeof( char ) * 3 );
    sprintf( data, "y4" );
    msg = smx_msg_create( data, sizeof( char ), msg_copy, msg_destroy );
    dzlog_info( "send data_y: %s", ( char* )msg->data );
    SMX_CHANNEL_WRITE( handler, a2, y, msg );

    return SMX_BOX_TERMINATE;
}

int b( void* handler )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if( msg != NULL ) {
        dzlog_info( "received data_x: %s", ( char* )msg->data );
        SMX_MSG_DESTROY( msg );
    }

    msg = SMX_CHANNEL_READ( handler, b, y );
    if( msg != NULL ) {
        dzlog_info( "received data_y: %s", ( char* )msg->data );
        SMX_MSG_DESTROY( msg );
    }

    return 0;
}
