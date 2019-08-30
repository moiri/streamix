/**
 * @author  ADD YOUR NAME
 * @file    b.c
 *
 * The implementation of the streamix box b.
 *
 * ADD DESCRITPTION HERE
 */

#include <stdlib.h>
#include <unistd.h>
#include "smxrts.h"
#include "b.h"

/******************************************************************************/
int b( void* h, void* state )
{
    smx_msg_t* msg;
    b_state_t* b_state = state;
    msg = SMX_CHANNEL_READ( h, b, x );
    if( msg != NULL )
    {
        fputc( *( int* )msg->data, b_state->fp );
        SMX_MSG_DESTROY( h, msg );
    }
    usleep( b_state->sleep );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void b_cleanup( void* h, void* state )
{
    ( void )( h );
    if( state == NULL ) return;
    b_state_t* b_state = state;
    fclose( b_state->fp );
    free( b_state );
}

/******************************************************************************/
int b_init( void* h, void** state )
{
    bson_t* conf = SMX_NET_GET_CONF( h );
    smx_config_error_t err;
    int sleep;
    const char* name = smx_config_get_string( conf, "file", NULL );

    if( name == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file'" );
        return 1;
    }

    sleep = smx_config_get_int_err( conf, "sleep", &err );
    if( err > 0 )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'sleep'" );
        return 1;
    }

    b_state_t* b_state = malloc(sizeof(struct b_state_s));
    b_state->sleep = sleep;
    b_state->fp = fopen( name, "w" );
    if( b_state->fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = b_state;
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_b( void* h )
{
    return START_ROUTINE_NET( h, b );
}
