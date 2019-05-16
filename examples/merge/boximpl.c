#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int a( void* handler, void* state )
{
    a_state_t* a_state = state;
    merge_msg_t* data = malloc(sizeof(struct merge_msg_s));
    data->data = fgetc( a_state->fp );
    data->id = a_state->idx;
    smx_msg_t* msg_x = SMX_MSG_CREATE( data, sizeof( struct merge_msg_s ), NULL,
            NULL, NULL );
    SMX_CHANNEL_WRITE( handler, a, x, msg_x );
    if( feof( a_state->fp ) )
        return SMX_NET_END;
    return SMX_NET_RETURN;
}

void a_cleanup( void* state )
{
    a_state_t* a_state = state;
    fclose( a_state->fp );
    free( a_state );
}

int a_init( void* handler, void** state )
{
    xmlNodePtr cur = SMX_NET_GET_CONF( handler );
    xmlChar* name = NULL;
    xmlChar* idx = NULL;

    if( cur == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion" );
        return 1;
    }

    name = xmlGetProp(cur, (const xmlChar*)"file");
    if( name == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion, no property 'file'" );
        return 1;
    }

    idx = xmlGetProp(cur, (const xmlChar*)"idx");
    if( name == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion, no property 'idx'" );
        return 1;
    }

    a_state_t* a_state = malloc(sizeof(struct b_state_s));
    a_state->idx = atoi( (const char*)idx );
    a_state->fp = fopen( (const char*)name, "r" );
    if( a_state->fp == NULL )
    {
        SMX_LOG( handler, error, "cannot open file %s", name );
        return 1;
    }
    *state = a_state;
    xmlFree(name);
    xmlFree(idx);
    return 0;
}

int b( void* handler, void* state )
{
    smx_msg_t* msg;
    b_state_t* merge_state = state;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if(msg == NULL) return SMX_NET_END;
    merge_msg_t* data = msg->data;
    if(data->id == merge_state->idx1)
        fputc( ( int )data->data, merge_state->fp1 );
    else if(data->id == merge_state->idx2)
        fputc( ( int )data->data, merge_state->fp2 );
    SMX_MSG_DESTROY( msg );
    return SMX_NET_RETURN;
}

void b_cleanup( void* state )
{
    b_state_t* merge_state = state;
    fclose( merge_state->fp1 );
    fclose( merge_state->fp2 );
    free(merge_state);
}

int b_init( void* handler, void** state )
{
    xmlNodePtr cur = SMX_NET_GET_CONF( handler );
    xmlChar* name1 = NULL;
    xmlChar* name2 = NULL;
    xmlChar* idx1 = NULL;
    xmlChar* idx2 = NULL;

    if( cur == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion" );
        return 1;
    }

    name1 = xmlGetProp(cur, (const xmlChar*)"file1");
    if( name1 == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion, no property 'file1'" );
        return 1;
    }

    name2 = xmlGetProp(cur, (const xmlChar*)"file2");
    if( name2 == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion, no property 'file2'" );
        return 1;
    }

    idx1 = xmlGetProp(cur, (const xmlChar*)"idx1");
    if( idx1 == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion, no property 'idx1'" );
        return 1;
    }

    idx2 = xmlGetProp(cur, (const xmlChar*)"idx2");
    if( idx2 == NULL )
    {
        SMX_LOG( handler, error, "invalid box configuartion, no property 'idx2'" );
        return 1;
    }

    b_state_t* merge_state = malloc(sizeof(struct b_state_s));
    merge_state->idx1 = atoi( (const char*)idx1 );
    merge_state->idx2 = atoi( (const char*)idx2 );
    merge_state->fp1 = fopen( (const char*)name1, "w" );
    if( merge_state->fp1 == NULL )
    {
        SMX_LOG( handler, error, "cannot open file %s", name1 );
        return 1;
    }
    merge_state->fp2 = fopen( (const char*)name2, "w" );
    if( merge_state->fp2 == NULL )
    {
        SMX_LOG( handler, error, "cannot open file %s", name2 );
        return 1;
    }
    *state = merge_state;
    xmlFree(name1);
    xmlFree(name2);
    xmlFree(idx1);
    xmlFree(idx2);
    return 0;
}
