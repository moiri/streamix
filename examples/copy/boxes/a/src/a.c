/**
 * @author  ADD YOUR NAME
 * @file    a.c
 *
 * The implementation of the streamix box a.
 *
 * ADD DESCRITPTION HERE
 */

#include <bson.h>
#include "smxrts.h"
#include "a.h"

/******************************************************************************/
int a( void* h, void* state )
{
    int symb = fgetc( state );
    if( feof( state ) )
        return SMX_NET_END;
    int* data = malloc( sizeof( int ) );
    *data = symb;
    smx_msg_t* msg_x = SMX_MSG_CREATE( h, data, sizeof( int ), NULL, NULL, NULL );
    SMX_CHANNEL_WRITE( h, a, x, msg_x );
    return SMX_NET_RETURN;
}

/******************************************************************************/
void a_cleanup( void* h, void* state )
{
    ( void )( h );

    if( state == NULL )
        return;

    // FREE THE FIELDS OF THE STATE VARIABLE

    fclose( state );
}

/******************************************************************************/
int a_init( void* h, void** state )
{
    bson_t* conf = SMX_NET_GET_CONF( h );
    const char* name = smx_config_get_string( conf, "file", NULL );

    if( name == NULL )
    {
        SMX_LOG( h, error, "invalid box configuartion, no property 'file'" );
        return 1;
    }

    FILE *fp = fopen( name, "r" );
    if( fp == NULL )
    {
        SMX_LOG( h, error, "cannot open file %s", name );
        return 1;
    }
    *state = fp;
    return 0;
}

/******************************************************************************/
/* DO NOT MODIFY!                                                             */
/******************************************************************************/
void* start_routine_a( void* h )
{
    return START_ROUTINE_NET( h, a );
}
