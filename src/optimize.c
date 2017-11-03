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

#include "egobch.h"
#include "optimize.h"

void optimize()
{
    /* optimize a segment of code */
    int a;
    struct bchi *cur;
    
    while (iprog[ipptr]) {
        cur = prog + pptr;
        
        switch (iprog[ipptr]) {
            case '}':
                cur->cmd = RTGL;
                ipptr++;
                pptr++;
                break;
                
            case '<':
                cur->cmd = LFT;
                ipptr++;
                pptr++;
                break;
                
            case '[':
                a = pptr;
                ipptr++;
                pptr++;
                
                /* run a suboptimize */
                optimize();
                
                cur->cmd = LPO;
                cur->arg1 = pptr;
                
                cur = prog + pptr;
                cur->cmd = LPC;
                cur->arg1 = a;
                
                ipptr++;
                pptr++;
                break;
                
            case ']':
                /* let the above run */
                return;
                
            case '.':
                if (lazy_io) {
                    cur->cmd = OUT;
                    pptr++;
                }
                ipptr++;
                break;
                
            case ',':
                if (lazy_io) {
                    cur->cmd = INP;
                    pptr++;
                }
                ipptr++;
                break;
                
            case '#':
                if (debug) {
                    cur->cmd = DBG;
                    pptr++;
                }
                ipptr++;
                break;
                
            default:
                ipptr++;
                break;
        }
    }
    
    /* we're done, make a fin */
    prog[pptr].cmd = FIN;
    pptr = 0;
}
