/* 
 * File:   main.c
 * Author: Christopher Kruczek, Christopher Zell <zelldon91@googlemail.com>
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
