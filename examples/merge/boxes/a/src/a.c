/**
 * @author  ADD YOUR NAME
 * @file    a.c
 *
 * The implementation of the streamix box a.
 *
 * ADD DESCRITPTION HERE
 */

#include "smxrts.h"
#include "a.h"

/******************************************************************************/
int a( void* h, void* state )
{
    a_state_t* a_state = state;
    int symb = fgetc( a_state->fp );
    if( feof( a_state->fp ) )
        return SMX_NET_END;
    a_x_data_t* data = malloc( sizeof( struct a_x_data_s ) );
    data->data = symb;
    data->id = a_state->idx;
    smx_msg_t* msg_x = SMX_MSG_CREATE( h, data, sizeof( struct a_x_data_s ),
            NULL, NULL, NULL );
    SMX_CHANNEL_WRITE( h, a, x, msg_x );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void a_cleanup( void* h, void* state )
{
    ( void )( h );
    a_state_t* a_state = state;
    fclose( a_state->fp );
    free( a_state );
}

/******************************************************************************/
int a_init( void* h, void** state )
{
    bson_t* conf = SMX_NET_GET_CONF( h );
    smx_config_error_t err;
    int idx;
    const char* name = smx_config_get_string( conf, "file", NULL );

    if( name == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file'" );
        return 1;
    }

    idx = smx_config_get_int_err( conf, "idx", &err );
    if( err > 0 )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'idx'" );
        return 1;
    }

    a_state_t* a_state = malloc(sizeof(struct a_state_s));
    a_state->idx = idx;
    a_state->fp = fopen( name, "r" );
    if( a_state->fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = a_state;
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_a( void* h )
{
    return START_ROUTINE_NET( h, a );
}
