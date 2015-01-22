#ifndef CMDLINE_H
#define CMDLINE_H

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
    SYNC,
    SYNC_SEARCH,
    SYNC_UPDATE,
    SYNC_UPDATE_ALL,

    QUERY,
    QUERY_PACKAGE,

    REMOVE

} OptionType;

/** Defines the basic parameter that were parsed from commandline
**/
struct Cmdline{
    OptionType OPTIONS;
    char* package;
} CMDLine;

#endif
