#include <stdio.h>
#include <stdlib.h>

/** texpack related includes **/
#include "cmdline.h"

int main(int argc, char* argv[])
{
    TpCmdlineConfig cfg = tpParseCmdline(argc,argv);

    printf("Selected options %d and package: %s\n",cfg.options,cfg.package);
    free(cfg.package);
    return 0;
}
