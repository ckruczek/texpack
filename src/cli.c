/* 
 * File:   cli.c
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

#include "cli.h"
#include "http.h"

/** 
    Init the global commandline config.
**/
void cli_init()
{
    CMD_CFG.options = NONE;
}

/**
    Free everything from the commandline config
    that had reserved memory.
**/
void cli_free()
{
    free(CMD_CFG.package);
}

/**
   Print the common usage for texpack
 **/
void cli_usage()
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
void cli_sync_usage()
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
    Print the particular help for the query option.
**/
void cli_query_usage()
{
    fprintf(stdout,"texpack -Q:\n");
    fprintf(stdout,"\tList all installed packages.\n");
    fprintf(stdout,"texpack -Qs packagename:\n");
    fprintf(stdout,"\tSearch the local package database for a package.\n\tDisplays package informationen.\n");
}

/**
    Print the particular help for the remove option.
**/
void cli_remove_usage()
{
    fprintf(stdout,"texpack -Q packagename:\n");
    fprintf(stdout,"\tRemove a package from the system.\n");
}

/**
    Print the invalid option error message
**/
void cli_invalid_option()
{
    printf("Invalid option\n");
    cli_usage();
}

/**
    Parse the commandline parameter
    and move on to handling of particular
    options.
**/
void cli_parse(int argc, char* argv[])
{
    // prevent getopt to print error message on
    // unknown parameter
    opterr = 0;
    char *optionString = "SQRsuah";
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
    
    for(int i = optind; i < argc; i++)
    {
        if(strcmp(argv[i],"--help") == 0 )
        {
            CMD_CFG.options |= HELP;
        }
    }
    
    // reset the index for parsing and move on to suboptions
    optind = 1;
    while((option =getopt(argc,argv,optionString)) != -1)
    {
        cli_parse_suboptions(option);
    }
    cli_gather_packagename(argc,argv);
    cli_process();
}

/**
 * This method is responsible for gathering package names from
 * commandline.
 * @param argc - The amount of commandline parameters
 * @param argv - The commandline parameter
 */
void cli_gather_packagename(int argc, char* argv[])
{
    if(optind < argc)
    {
        CMD_CFG.package = argv[optind];
    }
}

/**
 * This methods is responsible regarding the suboption
 * parsing.
 * @param opt - The suboption character.
 */
void cli_parse_suboptions(char opt)
{
    cli_option_t temp;
    
    if(isupper(opt))
        return;
    
    switch(opt)
    {
        case 's':
            temp = SEARCH;
            break;
        case 'u':
            temp = UPDATE;
            break;
        case 'a':
            temp = ALL;
            break;
        default:
            temp = NONE;
    }
    CMD_CFG.options |= temp;
}
/**
 * This methods process the final result of the commandline
 * parameter. 
 * It delegates then to the methods responsible for further
 * processing.
 */
void cli_process()
{
    cli_option_t options = CMD_CFG.options;
    
    if((options & SYNC) && (options & HELP))
    {
        cli_sync_usage();
        return;
    }
    if((options & QUERY) && (options & HELP))
    {
        cli_query_usage();
        return;
    }
    if((options & REMOVE) && (options & HELP))
    {
        cli_remove_usage();
        return;
    }
    
    if(options & NONE)
    {
        cli_invalid_option();
        return;
    }
    
    switch(options)
    {
        case SYNC:
            fprintf(stdout,"Sync choosen\n");
            http_request(HTTP_PACKAGE_URL,NULL);
            break;
        case SYNC_SEARCH:
            fprintf(stdout,"SYNC_SEARCH choosen with '%s'\n",CMD_CFG.package);
            break;
        case SYNC_UPDATE:
            fprintf(stdout,"SYNC_UPDATE choosen with '%s'\n",CMD_CFG.package);
            break;
        case SYNC_UPDATE_ALL:
            fprintf(stdout,"SYNC_UPDATE_ALL choosen\n");
            break;
        case QUERY:
            fprintf(stdout,"QUERY choosen\n");
            break;
        case QUERY_SEARCH:
            fprintf(stdout,"QUERY_SEARCH choosen with '%s'\n",CMD_CFG.package);
            break;
        case REMOVE:
            fprintf(stdout,"REMOVE choosen\n");
            break;
        case NONE:
        default:
            cli_invalid_option();
            break;
    }
}
