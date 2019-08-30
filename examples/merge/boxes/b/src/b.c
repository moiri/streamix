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
#include "a_msg.h"

/******************************************************************************/
int b( void* h, void* state )
{
    smx_msg_t* msg;
    b_state_t* merge_state = state;
    msg = SMX_CHANNEL_READ( h, b, x );
    if(msg == NULL) return SMX_NET_END;
    a_x_data_t* data = msg->data;
    if(data->id == merge_state->idx1)
        fputc( ( int )data->data, merge_state->fp1 );
    else if(data->id == merge_state->idx2)
        fputc( ( int )data->data, merge_state->fp2 );
    SMX_MSG_DESTROY( h, msg );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void b_cleanup( void* h, void* state )
{
    ( void )( h );

    if( state == NULL )
        return;

    b_state_t* merge_state = state;
    fclose( merge_state->fp1 );
    fclose( merge_state->fp2 );
    free(merge_state);
}

/******************************************************************************/
int b_init( void* h, void** state )
{
    bson_t* conf = SMX_NET_GET_CONF( h );
    smx_config_error_t err;
    int idx1, idx2;
    const char* name1 = smx_config_get_string( conf, "file1", NULL );
    const char* name2 = smx_config_get_string( conf, "file2", NULL );

    if( name1 == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file1'" );
        return 1;
    }
    if( name2 == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file2'" );
        return 1;
    }

    idx1 = smx_config_get_int_err( conf, "idx1", &err );
    if( err > 0 )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'idx1'" );
        return 1;
    }

    idx2 = smx_config_get_int_err( conf, "idx2", &err );
    if( err > 0 )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'idx2'" );
        return 1;
    }

    b_state_t* merge_state = malloc(sizeof(struct b_state_s));
    merge_state->idx1 = idx1;
    merge_state->idx2 = idx2;
    merge_state->fp1 = fopen( name1, "w" );
    if( merge_state->fp1 == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name1 );
        return 1;
    }
    merge_state->fp2 = fopen( name2, "w" );
    if( merge_state->fp2 == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name2 );
        return 1;
    }
    *state = merge_state;
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_b( void* h )
{
    return START_ROUTINE_NET( h, b );
}
