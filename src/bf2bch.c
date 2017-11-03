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

/*
 * Thanks to the kind people of #esoteric and http://www.esolangs.org/wiki/
 * for making these translation tables.
 */

#include <stdio.h>

int main()
{
    int input;
    
    while ((input = getchar()) != EOF) {
        switch (input) {
            case '+':
                printf("}<}}<}}<}}<}}<}}<}}<}}<}[<]<}}<}[<}}<}]<<<<<<<<<[<}]\n");
                break;
                
            case '-':
                printf("<}}<}}<}}<}}<}}<}}<}}<}}[<<}]}<}[}<}]<<<<<<<<<[<}]\n");
                break;
                
            case '>':
                printf("}<}}<}}<}}<}}<}}<}}<}}<}}<}}<}\n");
                break;
                
            case '<':
                printf("<<<<<<<<<<\n");
                break;
                
            case '[':
                printf("<}[<} }<}}<}}<}}<}}<}}<}}<}}<}\n"
                       "[}<}<}<<<<<<<<<[<}]<}}<}}<}}<}}<}}<}}<}}<}}<}<}]}<}[<<}}<}<}]\n"
                       "<<[}<}}<}<}<<<<<<<<<[<}]<}}<}}<}}<}}<}}<}}<}}<}<}]}<}}<}[<<<}}<}}<}<}]\n"
                       "<<<[}<}}<}}<}<}<<<<<<<<<[<}]<}}<}}<}}<}}<}}<}}<}<}]}<}}<}}<}[<<<<}}<}}<}}<}<}]\n"
                       "<<<<[}<}}<}}<}}<}<}<<<<<<<<<[<}]<}}<}}<}}<}}<}}<}<}]}<}}<}}<}}<}[<<<<<}}<}}<}}<}\n"
                       "}<}<}]\n"
                       "<<<<<[}<}}<}}<}}<}}<}<}<<<<<<<<<[<}]<}}<}}<}}<}}<}<}]}<}}<}}<}}<}}<}[<<<<<<}}<}}\n"
                       "<}}<}}<}}<}<}]\n"
                       "<<<<<<[}<}}<}}<}}<}}<}}<}<}<<<<<<<<<[<}]<}}<}}<}}<}<}]}<}}<}}<}}<}}<}}<}[<<<<<<<\n"
                       "}}<}}<}}<}}<}}<}}<}<}]\n"
                       "<<<<<<<[}<}}<}}<}}<}}<}}<}}<}<}<<<<<<<<<[<}]<}}<}}<}<}]}<}}<}}<}}<}}<}}<}}<}[<<<\n"
                       "<<<<<}}<}}<}}<}}<}}<}}<}}<}<}]\n"
                       "<<<<<<<<[}<}}<}}<}}<}}<}}<}}<}}<}<}<<<<<<<<<[<}]<}}<}<}]}<}}<}}<}}<}}<}}<}}<}}<}\n"
                       "[<<<<<<<<<}}<}}<}}<}}<}}<}}<}}<}}<}<}] <<<<<<<<<[<}\n");
                break;
                
            case ']':
                printf("}<}}<}}<}}<}}<}}<}}<}}<}}<}<}<<<<<<<<<]}<}}<}}<}}<}}<}}<}}<}}<}}<}[<<<<<<<<<<}}<\n"
                       "}}<}}<}}<}}<}}<}}<}}<}}<}<}]<<<<<<<<<]\n");
                break;
                
            case '.':
                printf("}<}.<\n");
                break;
                
            case ',':
                printf("}<},<\n");
                break;

            case '#':
                printf("#\n");
                break;
        }
    }
    return 0;
}
