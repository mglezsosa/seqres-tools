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
#ifndef HICLURES_TOOLS_HITS_H
#define HICLURES_TOOLS_HITS_H
#include <stdint.h>
#include "dynamic_array.h"

/**
 * Collapse same kmer occurences into same line on ordered kmer occurrences file.
 * @param fp1 Ordered kmer occurrences file.
 * @param fc1 Name of the output file.
 */
void collapse_occurrences(FILE* fp1, FILE* fc1);

/**
 * Create a file with kmer hits in two collapsed kmer occurrences files.
 * @param profile1 Name of the first file.
 * @param profile2 Name of the second file.
 * @param outfile Name of the output file.
 * @return
 */
void hits(FILE* fc1, FILE* fc2, FILE* out);

#endif //HICLURES_TOOLS_HITS_H
