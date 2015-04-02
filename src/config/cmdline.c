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

TpOptionConfig OPTIONS[] = 
{
    { {'S',SYNC}, { {'s',SEARCH },
                    {'u',UPDATE},
                    {'a',ALL } }, NULL },
};

/** 
    Init the global commandline config.
**/

/**
    Free everything from the commandline config
    that had reserved memory.
**/
/**
    Extract the option part from the commandline
    parameter without the leading '-'.
    @Param: param - The parameter to extract
    the string without the '-'
    @Param: option - A array of pointer where the
    result of the extraction goes.
    
    E.g.: param = '-Syua' option:["Syua"]
    @Return: 0 - Indicating extraction was 
    sucessfull
            -1 - Indicating extraction was
                unsucessfull
**/
int tpExtractOption(char *param, char **option)
{
    *option = strtok(param,"-");
    if(*option != NULL)
        return 0;

    return -1;
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
TpCmdlineConfig tpParseCmdline(int argc, char* argv[])
{
    TpCmdlineConfig cfg;
    cfg.options = NONE;
    cfg.package = "";
    if(argc > 1)
    {
        // extract only the part without the leading -
        char *opt = NULL;
        if(tpExtractOption(argv[1],&opt) != -1)
        {
            int size = sizeof(OPTIONS) / sizeof(OPTIONS[0]);
            for(int i = 0; i < size; i++)
            {
                TpOptionConfig ocfg = OPTIONS[i];
                if(opt[0] == ocfg.mainOption.name)
                {
                    cfg.mainOption = ocfg.mainOption.name;
                    cfg.subOptions = (char*)malloc(sizeof(char) * (strlen(opt) - 1)); 
                    if(strlen(opt) > 1)
                    {
                        strncpy(cfg.subOptions,opt+1,strlen(opt) - 1);
                    }
                    tpParseSubOptions(&cfg,ocfg.mainOption.type, argc,argv);
                }
            }
            if(cfg.options == NONE)
            {
                tpInvalidOption();
            }
            return cfg;
        }
    }
    return cfg;
}

/**
    Parse suboptions and check if they match
    any predeclared subOptions within the 
    OPTIONS map.
    @Param: rootType - The root type the suboptions belong to.
    @Param: argc - The number of arguments passed from commandline
    @Param: argv - The arguments passed from commandline
**/
void tpParseSubOptions(TpCmdlineConfig *cfg,TpOptionType rootType, int argc, char *argv[])
{
    cfg->options = rootType;
    if(argc == 3)
    {
        if(strcmp(argv[2],"--help") == 0)
        {
            tpPrintSyncHelp();
            return;
        }

        char *temp = cfg->subOptions;
        while(*temp)
        {
            for(int i = 0; i < MAX_SUBOPTIONS; i++)
            {   
                TpOptionConfig ocfg = OPTIONS[0];
                if(OPTIONS[0].subOptions[i].name == *temp)
                {
                    printf("found %c in string\n",*temp);
                    cfg->options |= ocfg.subOptions[i].type;
                }

            }
            temp++;
        }
    }
}

