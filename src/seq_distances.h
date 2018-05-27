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
 *
 * @param GE
 * @param nCols
 * @param nRows
 */
void zscores(float **GE, int nCols, int nRows);

/**
 *
 * @param profile1
 * @param profile2
 * @param length
 * @return
 */
float corr_distance(const float *profile1, const float *profile2, int length);

/**
 *
 * @param profile1
 * @param profile2
 * @param n
 * @return
 */
float eucl_distance(const float *profile1, const float *profile2,int n);

#endif //HICLURES_TOOLS_SEQ_DISTANCES_H
