/**
 * @author  ADD YOUR NAME
 * @file    b.c
 *
 * The implementation of the streamix box b.
 *
 * ADD DESCRITPTION HERE
 */

#include <libxml/parser.h>
#include <libxml/tree.h>
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
    xmlNodePtr cur = SMX_NET_GET_CONF( h );
    xmlChar* name1 = NULL;
    xmlChar* name2 = NULL;
    xmlChar* idx1 = NULL;
    xmlChar* idx2 = NULL;

    if( cur == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion" );
        return 1;
    }

    name1 = xmlGetProp(cur, (const xmlChar*)"file1");
    if( name1 == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file1'" );
        return 1;
    }

    name2 = xmlGetProp(cur, (const xmlChar*)"file2");
    if( name2 == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file2'" );
        return 1;
    }

    idx1 = xmlGetProp(cur, (const xmlChar*)"idx1");
    if( idx1 == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'idx1'" );
        return 1;
    }

    idx2 = xmlGetProp(cur, (const xmlChar*)"idx2");
    if( idx2 == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'idx2'" );
        return 1;
    }

    b_state_t* merge_state = malloc(sizeof(struct b_state_s));
    merge_state->idx1 = atoi( (const char*)idx1 );
    merge_state->idx2 = atoi( (const char*)idx2 );
    merge_state->fp1 = fopen( (const char*)name1, "w" );
    if( merge_state->fp1 == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name1 );
        return 1;
    }
    merge_state->fp2 = fopen( (const char*)name2, "w" );
    if( merge_state->fp2 == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name2 );
        return 1;
    }
    *state = merge_state;
    xmlFree(name1);
    xmlFree(name2);
    xmlFree(idx1);
    xmlFree(idx2);
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_b( void* h )
{
    return START_ROUTINE_NET( h, b );
}
