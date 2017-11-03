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

#ifndef EGOBCH_H
#define EGOBCH_H

#include <stdint.h>

struct bchi {
    enum { NIL,
            RTGL,
            LFT,
            LPO,
            LPC,
            OUT,
            INP,
            DBG,
            FIN
    } cmd;
    int arg1;
};

extern char *iprog;
extern int ipptr;

extern struct bchi *prog;
extern int pptr;

extern unsigned char *mem;
extern unsigned char *mptr;
extern unsigned char membit;

/* options */
extern int lazy_io;
extern int debug;

#define ISBCH(a) ( \
    (a) == '}' || \
    (a) == '<' || \
    (a) == ']' || \
    (a) == '[' || \
    ((a) == '.' && lazy_io) || \
    ((a) == ',' && lazy_io) || \
    ((a) == '#' && debug))

#endif
