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

#include <stdio.h>
#include "seq_distances.h"

void
zscores(float **GE, int nCols, int nRows)
{
    int j,i;
    float avg, d, DS, var;

    for (j=0;j<nCols;j++)
        for (i=0;i< nRows;i++)
            if (GE[j][i] !=0) {
                GE[j][i]=log2((double) GE[j][i]);
            }

    for (i=0;i< nCols; i++) {
        avg = 0;
        for (j=0; j < nRows; j++) avg += GE[i][j];
        avg /= nRows;
        var = 0;
        for (j=0; j < nRows; j++) {
            d = (GE[i][j] - avg);
            var += d * d;
        }
        DS = sqrt(var) / nRows;
        for (j=0; j < nRows; j++)
            GE[i][j] = (GE[i][j] - avg) / DS;
    }
}


float
corr_distance(const float *profile1, const float *profile2, int length)
{
    int 	a;
    float	distance;
    float	dx, dy;
    double Sxy, Sx, Sy;
    double x_mean, y_mean;

    x_mean = 0.0f;
    y_mean = 0.0f;
    Sxy = 0.0f;
    Sx = 0.0f;
    Sy = 0.0f;

    for (a=0; a<length; a++){
        x_mean += profile1[a];
        y_mean += profile2[a];
    }
    x_mean /= length;
    y_mean /= length;

    for (a=0; a<length; a++){
        dx = (profile1[a] - x_mean);
        Sx += dx*dx;

        dy = (profile2[a] - y_mean);
        Sy += dy*dy;

        Sxy += dx * dy;
    }
    if (Sx*Sy==0) return 0;

    distance = Sxy/(float)(sqrt(Sx*Sy));

    return distance;
}

float
eucl_distance(const float *profile1, const float *profile2,int n)
{
    float d=0,dd;
    int i;

    for (i=0;i<n;i++) {
        dd= profile1[i] - profile2[i];
        d+=dd*dd;
    }
    d=sqrt(d);
    return d;
}
