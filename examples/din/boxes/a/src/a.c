/**
 * @author  ADD YOUR NAME
 * @file    a.c
 *
 * The implementation of the streamix box a.
 *
 * ADD DESCRITPTION HERE
 */

#include <unistd.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "smxrts.h"
#include "a.h"

/******************************************************************************/
int a( void* h, void* state )
{
    a_state_t* a_state = state;
    int symb = fgetc( a_state->fp );
    if( feof( a_state->fp ) )
        return SMX_NET_END;
    int* data = malloc( sizeof( int ) );
    *data = symb;
    smx_msg_t* msg_x = SMX_MSG_CREATE( h, data, sizeof( int ), NULL, NULL, NULL );
    SMX_CHANNEL_WRITE( h, a, x, msg_x );
    usleep( a_state->sleep );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void a_cleanup( void* h, void* state )
{
    ( void )( h );
    if( state == NULL ) return;
    a_state_t* a_state = state;
    fclose( a_state->fp );
    free( a_state );
}

/******************************************************************************/
int a_init( void* h, void** state )
{
    xmlNodePtr cur = SMX_NET_GET_CONF( h );
    xmlChar* name = NULL;
    xmlChar* sleep = NULL;

    if( cur == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion" );
        return 1;
    }

    name = xmlGetProp(cur, (const xmlChar*)"file");
    if( name == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file'" );
        return 1;
    }

    sleep = xmlGetProp(cur, (const xmlChar*)"sleep");
    if( name == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'sleep'" );
        return 1;
    }

    a_state_t* a_state = malloc(sizeof(struct a_state_s));
    a_state->sleep = atoi( (const char*)sleep );
    a_state->fp = fopen( (const char*)name, "r" );
    if( a_state->fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = a_state;
    xmlFree(name);
    xmlFree(sleep);
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_a( void* h )
{
    return START_ROUTINE_NET( h, a );
}
