/* 
 * File:   cli.h
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
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

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
    
    NONE = 1 << 0,
    UPDATE = 1 << 1,
    SEARCH = 1 << 2,
    ALL    = 1 << 3,
    SYNC   = 1 << 4,
    QUERY  = 1 << 5,
    REMOVE = 1 << 6,
    HELP   = 1 << 7,

    SYNC_SEARCH = SYNC | SEARCH,
    SYNC_UPDATE = SYNC | UPDATE,
    SYNC_UPDATE_ALL = SYNC | UPDATE | ALL,
            
    QUERY_SEARCH = QUERY | SEARCH, 
    

} cli_option_t;

/**
Defines the basic parameter that were parsed from commandline
**/
typedef struct {
    cli_option_t options;
    char* package;
} cli_config;

static cli_config CMD_CFG;


void cli_usage();
void cli_sync_usage();
void cli_query_usage();
void cli_remove_usage();
void cli_init();
void cli_free();

void cli_parse(int argc, char *argv[]);
void cli_gather_packagename(int argc,char*argv[]);
void cli_check_help();
void cli_process();
void cli_parse_suboptions(char opt); 
void cli_invalid_option();
void cli_check_packageName();

#endif
