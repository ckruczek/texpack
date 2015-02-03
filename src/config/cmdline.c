/*
   This file is part of Foobar.

   Foobar is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Foobar is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "cmdline.h"

TpOptionConfig OPTIONS[] = 
{
    { "S",  SYNC, &tpParseSync },
    { "Ss", SYNC_SEARCH,&tpParseSync },
    { "Su", SYNC_UPDATE, &tpParseSync},
    { "Sua", SYNC_UPDATE_ALL, &tpParseSync },
};

int tpExtractOption(char *param, char **option)
{
    *option = strtok(param,"-");
    if(*option != NULL)
        return 0;

    return -1;
}

/*
   Print the common usage for texpack
 */
void tpPrintCommonUsage()
{
    fprintf(stdout, "usage: texpack <operation> [...]\n");
    fprintf(stdout, "operations:\n");
    fprintf(stdout, "\ttexpack {-S} <options> [package]\n");
    fprintf(stdout, "\ttexpack {-Q} <options> [package]\n");
    fprintf(stdout, "\ttexpack {-R} <options> [package]\n");
    fprintf(stdout, "use 'texpack {-h} with an option for available options\n");
}

void tpInvalidOption()
{
    printf("Invalid option\n");
    tpPrintCommonUsage();
}

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
                if(strcmp(opt,OPTIONS[i].optionString) == 0)
                {
                    cfg.options = OPTIONS[i].optionType;        
                    OPTIONS[i].callback(&cfg,argc,argv);
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

void tpParseSync(TpCmdlineConfig *cfg,int argc, char *argv[])
{
   switch(cfg->options)
   {
        case SYNC:
        case SYNC_UPDATE:
        case SYNC_SEARCH:
            if(argc >= 3)
            {
                cfg->package = (char*)malloc(strlen(argv[2]) + 1);
                strcpy(cfg->package,argv[2]);
            }
            break;
        default:
            break;
   }
}
