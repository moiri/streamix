/**
 * @file test_r.c
 *
 * THIS FILE WAS GENERATED BY THE STREAMIX TOOL `smxtrsp`. DO NOT EDIT THIS
 * FILE!
 *
 * ALL CHANGES MADE TO THIS FILE WILL BE OVERWRITTEN WHEN RECOMPILING THE
 * STREAMIX-SOURCE FILE!
 *
 * The test file which allows to test the box implementation.
 */

#ifndef APP_VERSION
#define APP_VERSION "unknown"
#endif

#include <unistd.h>
#include "smxrts.h"
#include "r.h"
#include "test_r.h"

#define JSON_APP_CONFIG_PATH "test.json"

int main( int argc, char **argv )
{
    int c;
    char* conf_file;

    if( access( JSON_APP_CONFIG_PATH, F_OK ) != -1 )
        conf_file = JSON_APP_CONFIG_PATH;
    else
        fprintf( stderr, "warning: no default app config file found\n" );

    while( ( c = getopt( argc, argv, "hvc:" ) ) != -1 )
        switch( c ) {
            case 'h':
                printf( "Usage:\n  %s [OPTION...]\n\n", argv[0] );
                printf( "Options:\n" );
                printf( "  -h            This message.\n" );
                printf( "  -v            The version of the box implementation.\n" );
                printf( "  -c 'FILE'     Configuration file to be passed to the application.\n" );
                printf( "                If no file is specified the application falls back to:\n" );
                printf( "                 1. '%s' in the application root\n", JSON_APP_CONFIG_PATH );
                return 0;
            case 'v':
                printf( "r v%s\n", APP_VERSION );
                return 0;
            case 'c':
                conf_file = optarg;
                break;
            case '?':
                if( optopt == 'c' )
                    fprintf ( stderr, "Option -%c requires an argument.\n",
                            optopt );
                else
                    fprintf ( stderr, "Unknown option character `\\x%x'.\n",
                            optopt );
                return 1;
            default:
                abort();
        }

    smx_rts_t* rts = smx_program_init( conf_file );

    SMX_NET_CREATE( 0, Test, r, 0 );
    SMX_NET_INIT( 0, 1, 0 );
    SMX_CHANNEL_CREATE( 2, 1, SMX_FIFO, x );
    SMX_CONNECT( 0, 2, r, x, in );
    SMX_PROGRAM_INIT_RUN();
    SMX_NET_RUN( 0, r );
    SMX_NET_WAIT_END( 0 );
    SMX_CHANNEL_DESTROY( 2 );
    SMX_NET_DESTROY( 0 );

    smx_program_cleanup( rts );
}
