/**
 * @author  ADD YOUR NAME
 * @file    r.c
 *
 * The implementation of the streamix box r.
 *
 * ADD DESCRITPTION HERE
 */

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "smxrts.h"
#include "r.h"

/******************************************************************************/
int r( void* h, void* state )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( h, r, x );
    if(msg == NULL) return SMX_NET_END;
    fputc( *( int* )msg->data, state );
    SMX_MSG_DESTROY( h, msg );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void r_cleanup( void* h, void* state )
{
    ( void )( h );

    if( state == NULL )
        return;

    fclose( state );
}

/******************************************************************************/
int r_init( void* h, void** state )
{
    xmlNodePtr cur = SMX_NET_GET_CONF( h );
    xmlChar* name = NULL;

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
    FILE *fp = fopen( (const char*)name, "w" );
    if( fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = fp;
    xmlFree(name);
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_r( void* h )
{
    return START_ROUTINE_NET( h, r );
}
