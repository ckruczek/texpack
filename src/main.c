#include <stdio.h>
#include <stdlib.h>

/** texpack related includes **/
#include "cmdline.h"

int main(int argc, char* argv[])
{
    OptionType t = SYNC;
    printf("%d\n",argc);
    printf("%s\n",argv[0]);
    printf("%d\n",t);
}
