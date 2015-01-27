#include "cmdline.h"

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

TpCmdlineConfig tpParseCmdline(int argc, char* argv[])
{
    char* options = "SQRsua";
    TpCmdlineConfig cfg;
    // configure getopt to print errormessage by unknown parameters
    opterr = 0;
    int c;
    while((c = getopt(argc,argv,options)) != -1)
    {
        switch(c)
        {
            case 'S':
                cfg.options = SYNC;
                break;
            case 'R':
                cfg.options = REMOVE;
                break;
            case 'Q':
                cfg.options = QUERY;
                break;
            case '?':
                break;
            default:
                cfg.options = NONE;
                break;
        }
    }
    optind = 1;
    while((c = getopt(argc,argv,options)) != -1 && cfg.options != NONE)
    {
        switch(c)
        {
            case 's':
                cfg.options |= SEARCH;
                break;
            case 'u':
                cfg.options |= UPDATE;
                break;
            case 'a': 
                cfg.options |= ALL;
                break;
            case '?':
                break;
            default:
                break;
        }
    }

    return cfg;
}
