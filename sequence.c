/**
 * Copyright (C) 2018 Miguel González <sosa@uma.es>
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
 */

#include "sequence.h"

off_t
loadseq(char *addr, sequence_t *S, off_t offset, off_t size)
{
    char c;
    int i = 0, len = 0;

    while((c = addr[offset]) != '>' && offset != size) {
        printf("%c\n", c);
        offset++;
    }

    if (offset == size) return size;

    while(addr[++offset] == ' ');

    while(c != '\n' && c != ' ') {
        S->id[i++] = c;
        c = addr[offset++];
    }

    S->id[i]=0x00;

    while(c!='\n') c=addr[offset++]; // skip the rest of line

    c = addr[++offset]; // Sequence starts inmediately after the line break
    S->startAddress = offset;
    S->endAddress = offset;

    while(c != '>' && S->endAddress != size) {
        c = (char) toupper(addr[S->endAddress]);
        S->endAddress++;
        if (c >= 'A' && c <= 'Z') len++;
    }

    S->len=len;

    return S->endAddress;
}

char
base2num(char c)
{
    switch(c){
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
    }
    return 4;
}

int
kmer2num(char *kmer, int k)
{
    int result = 0;
    for (char i = 0; i < k; ++i) {
        result += base2num(kmer[i]) * pow(4, k-i-1);
    }
    return result;
}

unsigned long
base4idx(unsigned long hash)
{
    unsigned long decimal = 1;
    unsigned long quotient = hash;
    unsigned long base4 = 0;
    while (quotient >= 4) { /* Compiler optimized using bit level operations? */
        base4 += decimal*(quotient%4);
        quotient /= 4;
        decimal *= 10;
    }
    base4 += decimal*quotient;
    return base4;
}

void
nucleotididx(char *buffer, unsigned long hash, int k)
{
    unsigned long index = base4idx(hash);
    for (int i = 0; i < k; ++i) {
        unsigned long c = index%10;
        switch (c) {
            case 0:
                buffer[k-i-1] = 'A';
                break;
            case 1:
                buffer[k-i-1] = 'C';
                break;
            case 2:
                buffer[k-i-1] = 'G';
                break;
            case 3:
                buffer[k-i-1] = 'T';
                break;
	}
        index /= 10;
    }
}
