#include "boximpl.h"
#include "boxgen.h"
#include "smxrts.h"
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int a( void* handler, void* state )
{
    int* data = malloc( sizeof( int ) );
    *data = fgetc( state );
    smx_msg_t* msg_x = SMX_MSG_CREATE( data, sizeof( int ), NULL, NULL, NULL );
    SMX_CHANNEL_WRITE( handler, a, x, msg_x );
    if( feof( state ) )
        return SMX_NET_END;
    return SMX_NET_RETURN;
}

void a_cleanup( void* state )
{
    fclose( state );
}

int a_init( void* handler, void** state )
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

int b( void* handler, void* state )
{
    smx_msg_t* msg;
    msg = SMX_CHANNEL_READ( handler, b, x );
    if(msg == NULL) return SMX_NET_END;
    fputc( *( int* )msg->data, state );
    SMX_MSG_DESTROY( msg );
    return SMX_NET_RETURN;
}

void b_cleanup( void* state )
{
    fclose( state );
}

int b_init( void* handler, void** state )
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
