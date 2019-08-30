/**
 * @author  ADD YOUR NAME
 * @file    b.c
 *
 * The implementation of the streamix box b.
 *
 * ADD DESCRITPTION HERE
 */

#include "smxrts.h"
#include "b.h"

/******************************************************************************/
int b( void* h, void* state )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( h, b, x );
    if(msg == NULL) return SMX_NET_END;
    fputc( *( int* )msg->data, state );
    SMX_MSG_DESTROY( h, msg );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void b_cleanup( void* h, void* state )
{
    ( void )( h );

    if( state == NULL )
        return;

    // FREE THE FIELDS OF THE STATE VARIABLE

    fclose( state );
}

/******************************************************************************/
int b_init( void* h, void** state )
{
    bson_t* conf = SMX_NET_GET_CONF( h );
    const char* name = smx_config_get_string( conf, "file", NULL );

    if( name == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file'" );
        return 1;
    }

    FILE *fp = fopen( name, "w" );
    if( fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = fp;
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_b( void* h )
{
    return START_ROUTINE_NET( h, b );
}
