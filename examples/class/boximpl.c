#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <zlog.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int l( void* h, void* state )
{
    int symb = fgetc( state );
    if( feof( state ) )
        return SMX_NET_END;
    int* data = malloc( sizeof( int ) );
    *data = symb;
    smx_msg_t* msg_x = SMX_MSG_CREATE( h, data, sizeof( int ), NULL, NULL,
            NULL );
    SMX_CHANNEL_WRITE( h, l, x, msg_x );
    return SMX_NET_RETURN;
}

void l_cleanup( void* h, void* state )
{
    ( void )( h );
    fclose( state );
}

int l_init( void* h, void** state )
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

    FILE *fp = fopen( (const char*)name, "r" );
    if( fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = fp;
    xmlFree(name);
    return 0;
}

int m( void* h, void* state )
{
    (void)(state);
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( h, m, x );
    if( msg == NULL ) return SMX_NET_END;
    SMX_CHANNEL_WRITE( h, m, x, msg );
    return SMX_NET_RETURN;
}

void m_cleanup( void* h, void* state )
{
    ( void )( h );
    ( void )( state );
}

int m_init( void* h, void** state )
{
    ( void )( h );
    ( void )( state );
    return 0;
}

int r( void* h, void* state )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( h, r, x );
    if(msg == NULL) return SMX_NET_END;
    fputc( *( int* )msg->data, state );
    SMX_MSG_DESTROY( h, msg );
    return SMX_NET_RETURN;
}

void r_cleanup( void* h, void* state )
{
    ( void )( h );
    fclose( state );
}

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
