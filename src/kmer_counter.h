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

#ifndef HICLURES_TOOLS_KMER_COUNTER_H
#define HICLURES_TOOLS_KMER_COUNTER_H

#include <ctype.h>
#include "sequence.h"
#include "filehandle.h"

/**
 * Counts kmers of k length for the FASTA file with name 'filename'.
 * @param filename Path to FASTA file.
 * @param k Length of the kmers to be counted.
 */
void count_kmers(char* filename, int k);

#endif //HICLURES_TOOLS_KMER_COUNTER_H
