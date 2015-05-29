/* 
 * File:   cmdline.c
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

#include "cmdline.h"

/** 
    Init the global commandline config.
**/
void tpInitCmdConfig()
{
    CMD_CFG.options = NONE;
    CMD_CFG.package = malloc(sizeof(char));
}

/**
    Free everything from the commandline config
    that had reserved memory.
**/
void tpFreeCmdConfig()
{
    free(CMD_CFG.package);
}

/**
   Print the common usage for texpack
 **/
void tpPrintCommonUsage()
{
    fprintf(stdout, "usage: texpack <operation> [...]\n");
    fprintf(stdout, "operations:\n");
    fprintf(stdout, "\ttexpack {-S} <options> [package]\n");
    fprintf(stdout, "\ttexpack {-Q} <options> [package]\n");
    fprintf(stdout, "\ttexpack {-R} <options> [package]\n");
    fprintf(stdout, "use 'texpack {-S|-Q|-R} {--help}' with an option for available options\n");
}

/**
    Print the particular help for the Sync option.
**/
void tpPrintSyncHelp()
{
    fprintf(stdout,"texpack -S packagename:\n");
    fprintf(stdout,"\tInstall or reinstall the package.\n");
    fprintf(stdout,"texpack -Ss packagename:\n");
    fprintf(stdout,"\tSearch the global repository for the package, only a part of \n\tthe package suffice.\n");
    fprintf(stdout,"texpack -Su packagename:\n");
    fprintf(stdout,"\tUpgrade the given package.\n");
    fprintf(stdout,"texpack -Sua:\n");
    fprintf(stdout,"\tUpgrade all packages given in the database.\n");
}

/**
    Print the invalid option error message
**/
void tpInvalidOption()
{
    printf("Invalid option\n");
    tpPrintCommonUsage();
}

/**
    Parse the commandline parameter
    and move on to handling of particular
    options.
**/
void tpParseCmdline(int argc, char* argv[])
{
    char *optionString = "SQRsua";
    char *packageName;
    char option;
    
    while((option = getopt(argc,argv,optionString)) != -1)
    {
        switch(option)
        {
            case 'S':
                CMD_CFG.options = SYNC;
                break;
            case 'Q':
                CMD_CFG.options = QUERY;
                break;
            case 'R':
                CMD_CFG.options = REMOVE;
                break;
            default:
                CMD_CFG.options = NONE;
                break;
        }
        if(CMD_CFG.options != NONE)
            break;
    }
    
    // reset the index for parsing and move on to suboptions
    optind = 1;
    while((option =getopt(argc,argv,optionString)) != -1)
    {
        // check whether sync is somehow set
        if(CMD_CFG.options & SYNC)
        {
            tpProcessSync(option);
        }
        else if(CMD_CFG.options & QUERY)
        {
            tpProcessSync(option);
        }
        else if(CMD_CFG.options & REMOVE)
        {
            tpProcessSync(option);
        }
    }
}

void tpProcessSync(char opt)
{
    switch(opt)
    {
        case 's':
            CMD_CFG.options |= SEARCH;
            break;
        case 'u':
            CMD_CFG.options |= UPDATE;
            break;
        case 'a':
            CMD_CFG.options |= ALL;
            break;
        default:
            CMD_CFG.options = NONE;
            break;
    }
}

