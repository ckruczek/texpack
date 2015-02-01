#ifndef CMDLINE_H
#define CMDLINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

typedef void (*optionCallback)(TpCmdlineConfig *cfg, int arg,char *argv[]);

typedef struct {
    const char* optionString;
    TpOptionType optionType;
    optionCallback callback;
} TpOptionConfig;

void tpPrintCommonUsage();
TpCmdlineConfig tpParseCmdline(int argc, char *argv[]);
void tpParseSync(TpCmdlineConfig *cfg, int argc,char *argv[]); 
void tpParseUpdate(TpCmdlineConfig *cfg, int argc, char *argv[]);
void tpParseRemove(TpCmdlineConfig *cfg, int argc, char *argv[]);
void tpInvalidOption();

int tpExtractOption(char *param, char **option);

#endif
