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

#include <math.h>
#include <stdio.h>

#include "bchi.h"
#include "egobch.h"

#define LOGTWO 0.693147
#define SETBIT(a) (7 - (int) (log((double) (a)) / LOGTWO))

void binaryo()
{
    int i, j;
    unsigned char vbit;
    unsigned char *curmem;
    for (i = -2; i <= 2; i++) {
        curmem = mptr + i;
        if (curmem < mem) continue;
        for (j = 7; j >= 0; j--) {
            vbit = 1 << j;
            if (i == 0 && vbit == membit)
                putchar('*');
            if (*curmem & vbit)
                putchar('1');
            else
                putchar('0');
        }
    }
    putchar('\n');
}

void bch_interpret()
{
    int input, shft;
    unsigned char toout;
    struct bchi *cur;
    
    while (1) {
        cur = prog + pptr;
        /*printf("%d %d %x\n", mptr - mem, SETBIT(membit), (unsigned int) *mptr);*/
        
        switch (cur->cmd) {
            case RTGL:
                /* 1) move right */
                membit >>= 1;
                if (membit == 0) {
                    membit = 0x80;
                    mptr++;
                }
                
                /* 2) check for I/O */
                if (mptr == mem && membit == 0x04) {
                    /* 2a) check whether to do input or output */
                    if (*mem & 0x01) {
                        /* 2ai) output */
                        putchar(mem[1]);
                        fflush(stdout);
                    } else {
                        /* 2aii) input */
                        input = getchar();
                        /* 2aiii) check for EOF */
                        if (input == EOF) {
                            /* mark it */
                            *mem |= 0x02;
                        } else {
                            mem[1] = (char) input;
                        }
                    }
                } else {
                    /* 3) toggle */
                    *mptr ^= membit;
                }
                pptr++;
                break;
                
            case LFT:
                /* move left */
                membit <<= 1;
                if (membit == 0) {
                    membit = 0x01;
                    mptr--;
                }
                pptr++;
                break;
                
            case LPO:
                /* loop opening */
                if (*mptr & membit) {
                    /* go into the loop */
                    pptr++;
                } else {
                    /* jump the loop */
                    pptr = cur->arg1 + 1;
                }
                break;
                
            case LPC:
                /* loop close, jump to the beginning */
                pptr = cur->arg1;
                break;
                
            case OUT:
                /* lazy_io output */
                shft = SETBIT(membit);
                toout = *mptr << shft;
                
                shft = 8 - shft;
                toout |= mptr[1] >> shft;
                
                putchar(toout);
                fflush(stdout);
                pptr++;
                break;
                
            case INP:
                /* lazy_io input */
                input = getchar();
                if (input == EOF) input = 0;
                toout = (char) input;
                
                /* shift it in */
                shft = SETBIT(membit);
                *mptr &= ~(0xFF >> shft);
                *mptr |= toout >> shft;
                
                shft = 8 - shft;
                mptr[1] &= ~(0xFF << shft);
                mptr[1] |= toout << shft;
                pptr++;
                break;

            case DBG:
                binaryo();
                pptr++;
                break;
                
            case FIN:
                return;
                
            default:
                pptr++;
        }
    }
}
