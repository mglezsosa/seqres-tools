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

#ifndef HICLURES_TOOLS_SEQ_DISTANCES_H
#define HICLURES_TOOLS_SEQ_DISTANCES_H

#include <math.h>

/**
 * Transform frequencies matrix into z-scored values.
 * @param GE frequencies matrix.
 * @param nCols number of columns.
 * @param nRows number of rows.
 */
void zscores(float **GE, int nCols, int nRows);

/**
 * Calculates de correlation distances over two frequencies vectors.
 * @param profile1 pointer to a z-scored frequencies array.
 * @param profile2 pointer to a z-scored frequencies array.
 * @param length length of the arrays.
 * @return correlation distance.
 */
float corr_distance(float *profile1, float *profile2, int length);

/**
 * Calculates de eucledian distance over two frequencies vectors.
 * @param profile1 pointer to a z-scored frequencies array.
 * @param profile2 pointer to a z-scored frequencies array.
 * @param n length of the arrays.
 * @return eucledian distance.
 */
float eucl_distance(float *profile1, float *profile2,int n);

/**
 * Computes correlation and euclidean distance for the given vectors of kmer frequencies.
 * @param filename1 Pointer to a vector.
 * @param filename2 Poiter to the other vector.
 * @param k length of the kmers.
 */
void compute_distances(char* filename1, char* filename2, int k);

#endif //HICLURES_TOOLS_SEQ_DISTANCES_H
