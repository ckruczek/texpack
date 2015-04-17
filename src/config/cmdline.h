/* 
 * File:   cmdline.h
 * Author: Christopher Kruczek
 * 
 * Copyright (C) 2015 The texpack Open Source Project
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

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

#define  MAX_SUBOPTIONS  4
/**
Defines the basic parameter that were parsed from commandline
**/
typedef struct {
    TpOptionType options;
    char mainOption;
    char *subOptions;
    char* package;
} TpCmdlineConfig;

static TpCmdlineConfig CMD_CFG;

typedef void (*optionCallback)(int arg,char *argv[]);

typedef struct {
    const char name;
    TpOptionType type;
} TpOption;

typedef struct {
    const TpOption mainOption;
    const TpOption subOptions[MAX_SUBOPTIONS];
    optionCallback callback;
} TpOptionConfig;

void tpPrintCommonUsage();
void tpPrintSyncHelp();
void tpPrintQueryHelp();
void tpPrintRemoveHelp();
void tpInitCmdConfig();
void tpFreeCmdConfig();

void tpParseCmdline(int argc, char *argv[]);
void tpParseSubOptions(TpOptionType rootType,int arg, char *argv[]);
void tpParseSync(int argc,char *argv[],char *rest); 
void tpParseUpdate(int argc, char *argv[], char *rest);
void tpParseRemove(int argc, char *argv[], char *rest);
void tpInvalidOption();

int tpExtractOption(char *param, char **option);

#endif
