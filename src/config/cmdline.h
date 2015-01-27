#ifndef CMDLINE_H
#define CMDLINE_H

#include <stdio.h>
#include <getopt.h>

/**
Defines the possible options that can passed to the texpack
SYNC = S
SYNC_SEARCH = Ss
SYNC_UPDATE = Su
SYNC_UPDATE_ALL = Syua
QUERY = Q
QUERY_PACKAGE = Qs 
REMOVE = R
**/
typedef enum{
    UPDATE = 1 << 0,
    SEARCH = 1 << 1,
    ALL    = 1 << 2,
    SYNC   = 1 << 3,
    QUERY  = 1 << 4,
    REMOVE = 1 << 5,
    NONE   = 1 << 6,

    SYNC_SEARCH = SYNC | SEARCH,
    SYNC_UPDATE = SYNC | UPDATE,
    SYNC_UPDATE_ALL = SYNC | UPDATE | ALL,
    QUERY_SEARCH = QUERY | SEARCH, 
    

} TpOptionType;

/**
Defines the basic parameter that were parsed from commandline
**/
typedef struct {
    TpOptionType options;
    char* package;
} TpCmdlineConfig;


void tpPrintCommonUsage();
TpCmdlineConfig tpParseCmdline(int argc, char* argv[]);
void tpParseSync(char* argv[],TpCmdlineConfig * config);
void tpParseUpdate(char* argv[], TpCmdlineConfig * config);
void tpParseRemove(char* argv[], TpCmdlineConfig * config);


#endif
