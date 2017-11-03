/*
 * Copyright (C) 2005  Gregor Richards
 *
 * This file is part of EgoBCh.
 * 
 * EgoBCh is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * EgoBCh is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with EgoBCh; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bchi.h"
#include "egobch.h"
#include "optimize.h"

char *iprog;
int ipptr;

struct bchi *prog;
int pptr;

unsigned char *mem;
unsigned char *mptr;
unsigned char membit;

int lazy_io = 0;
int debug = 0;

int main(int argc, char **argv)
{
    int i;
    FILE *bchin;
    char *bchins = NULL;
    
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (!strcmp(argv[i], "-lazy-io")) {
                i++;
                if (!strcmp(argv[i], "on"))
                    lazy_io = 1;
            } else if (!strcmp(argv[i], "-debug")) {
                debug = 1;
            } else if (!strcmp(argv[i], "--help") ||
                       !strcmp(argv[i], "-help") ||
                       !strcmp(argv[i], "-h")) {
                fprintf(stderr,
                        "Use: egobchi <options> <input file>\n"
                        "Options:\n"
                        " -lazy-io <on|off>\n"
                        "   allow the use of . and , for IO (not standard BitChanger) [default off]\n"
                        " -debug\n"
                        "   allow # debugging\n");
                exit(0);
            } else {
                fprintf(stderr, "Unrecognized option: %s\n", argv[i]);
                exit(1);
            }
        } else {
            bchins = argv[i];
        }
    }
    
    /* now allocate memory */
    iprog = (char *) malloc(30000);
    ipptr = 0;
    prog = (struct bchi *) malloc(30000 * sizeof(struct bchi));
    pptr = 0;
    mem = (unsigned char *) malloc(30000);
    memset(mem, 0, 30000);
    mptr = mem + 2;
    membit = 0x80;
    
    /* read the file */
    if (bchins) {
        bchin = fopen(bchins, "r");
        if (bchin == NULL) {
            perror(bchins);
            exit(1);
        }
    } else {
        bchin = stdin;
    }
    
    while (!feof(bchin) && !ferror(bchin)) {
        iprog[ipptr] = fgetc(bchin);
        if ISBCH(iprog[ipptr]) {
            ipptr++;
        }
    }
    iprog[ipptr] = '\0';
    
    /* "optimize" (which really just matches loops) */
    ipptr = 0;
    optimize();
    if (pptr != 0 && prog[0].cmd != FIN) {
        fprintf(stderr, "Unmatched loop!\n");
        exit(1);
    }
    
    /* interpret */
    pptr = 0;
    bch_interpret();
    
    return 0;
}
