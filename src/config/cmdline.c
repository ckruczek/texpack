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
    TpCmdlineConfig cfg;
    {
        switch(c)
        {
        }
    }
    return cfg;
}
