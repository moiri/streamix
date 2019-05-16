#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int l( void* handler, void* state )
{
    int* data = malloc( sizeof( int ) );
    *data = fgetc( state );
    smx_msg_t* msg_x = SMX_MSG_CREATE( data, sizeof( int ), NULL, NULL, NULL );
    SMX_CHANNEL_WRITE( handler, l, x, msg_x );
    if( feof( state ) )
        return SMX_NET_END;
    return SMX_NET_RETURN;
}

void l_cleanup( void* state )
{
    fclose( state );
}

int l_init( void* handler, void** state )
{
    xmlNodePtr cur = SMX_NET_GET_CONF( handler );
    xmlChar* name = NULL;

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

    FILE *fp = fopen( (const char*)name, "r" );
    if( fp == NULL )
    {
        SMX_LOG( handler, error, "cannot open file %s", name );
        return 1;
    }
    *state = fp;
    xmlFree(name);
    return 0;
}

int m( void* handler, void* state )
{
    (void)(state);
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, m, x );
    SMX_CHANNEL_WRITE( handler, m, x, msg );
    return 0;
}

void m_cleanup( void* state )
{
    (void)(state);
}

int m_init( void* handler, void** state )
{
    (void)(handler);
    (void)(state);
    return 0;
}

int r( void* handler, void* state )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, r, x );
    if(msg == NULL) return SMX_NET_END;
    fputc( *( int* )msg->data, state );
    SMX_MSG_DESTROY( msg );
    return SMX_NET_RETURN;
}

void r_cleanup( void* state )
{
    fclose( state );
}

int r_init( void* handler, void** state )
{
    xmlNodePtr cur = SMX_NET_GET_CONF( handler );
    xmlChar* name = NULL;

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
    FILE *fp = fopen( (const char*)name, "w" );
    if( fp == NULL )
    {
        SMX_LOG( handler, error, "cannot open file %s", name );
        return 1;
    }
    *state = fp;
    xmlFree(name);
    return 0;
}
