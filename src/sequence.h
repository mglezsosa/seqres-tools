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

#ifndef PRACTICA_SEQUENCE_H
#define PRACTICA_SEQUENCE_H

#include <zconf.h>
#include <ctype.h>
#include <sys/stat.h>
#include <math.h>
#include <stdio.h>

#define MAXSID 100 /* Maximum length for a sequence id. */

/**
 * Sequence-related info in a memory-mapped file.
 */
typedef struct {
    char id[MAXSID]; /* Fasta sequence id. */
    off_t startAddress; /* Address where sequence starts. */
    off_t endAddress; /* Address where sequence ends. */
    int len; /* Number of bases of the sequence. */
} sequence_t;

/**
 * Loads the first sequence in a memory-mapped file.
 * @param addr address of memory-mapped file.
 * @param S sequence struct.
 * @param offset reading starting point.
 * @param size size of the file.
 * @return end of sequence offset.
 */
off_t loadseq(char *addr, sequence_t *S, off_t offset, off_t size);

/**
 * Translates {A, C, G, T} code in {0, 1, 2, 3} code.
 * @param c DNA base to be translated.
 * @return translated base.
 */
char base2num(char c);

/**
 * Translates a base-4 index to a base-10 index.
 * @param kmer base-4 represented kmer.
 * @param k length of the kmer.
 * @return base-10 kmer index.
 */
int kmer2num(char * kmer, int k);

/**
 * Translates a base-10 kmer index to a {A, C, G, T}-represented kmer.
 * @param buffer buffer to store the kmer.
 * @param hash base-10 kmer index.
 * @param k length of the kmer.
 */
void nucleotididx(char * buffer, unsigned long hash, int k);

/**
 * Translates a base-10 index to a base-4 index.
 * @param hash base-10 index.
 * @return base-4 index.
 */
unsigned long base4Index(unsigned long hash);

#endif //PRACTICA_SEQUENCE_H
