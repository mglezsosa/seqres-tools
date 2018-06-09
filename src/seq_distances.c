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
#include <stdlib.h>
#include "seq_distances.h"

void
zscores(float **GE, int nCols, int nRows)
{
    int j,i;
    float avg = 0, d = 0, DS = 0, var = 0;

    for (j=0;j<nCols;j++) {
        for (i=0;i< nRows;i++) {
            if (GE[j][i] !=0) {
                GE[j][i]= (float) log2((double) GE[j][i]);
            }
        }
    }

    for (i=0;i< nCols; i++) {
        avg = 0;
        for (j=0; j < nRows; j++) {
            avg += GE[i][j];
        }
        avg /= nRows;
        var = 0;
        for (j=0; j < nRows; j++) {
            d = (GE[i][j] - avg);
            var += d * d;
        }
        DS = (sqrtf(var) / nRows);
        for (j=0; j < nRows; j++) {
            GE[i][j] = (GE[i][j] - avg) / DS;
        }
    }
}


float
corr_distance(float *profile1, float *profile2, int length)
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
        dx = (float) (profile1[a] - x_mean);
        Sx += dx*dx;

        dy = (float) (profile2[a] - y_mean);
        Sy += dy*dy;

        Sxy += dx * dy;
    }
    if (Sx*Sy==0) {
        return 0;
    }
    distance = (float) (Sxy / (sqrt(Sx * Sy)));

    return distance;
}

float
eucl_distance(float *profile1, float *profile2,int n)
{
    float d=0,dd;
    int i;

    for (i=0;i<n;i++) {
        dd= profile1[i] - profile2[i];
        d+=dd*dd;
    }
    d = sqrtf(d);
    return d;
}

void
compute_distances(char* filename1, char* filename2, int k)
{
    FILE *f1;
    FILE *f2;
    char* line = NULL;
    size_t len = 0;
    float freq;
    int cntr = 0;
    float *matrix[2];
    int mat_size = (int) pow(4, k);
    if (( matrix[0] = (float *) malloc(mat_size * sizeof(float)))==NULL) {
        fprintf(stderr,"run out of memory\n");
        exit(-1);
    }
    if (( matrix[1] = (float *) malloc(mat_size * sizeof(float)))==NULL) {
        fprintf(stderr,"run out of memory\n");
        exit(-1);
    }

    if ((f1 = fopen(filename1, "rte"))==NULL) { // open input file
        fprintf(stderr,"opening input file\n");
        exit(-1);
    }
    if ((f2 = fopen(filename2, "rte"))==NULL) { // open input file
        fprintf(stderr,"opening input file\n");
        exit(-1);
    }
    while (getline(&line, &len, f1) != -1) {
        sscanf(line, "%*s\t%f", &freq);
        matrix[0][cntr++] = freq;
    }
    line = NULL;
    len = 0;
    cntr = 0;
    while (getline(&line, &len, f2) != -1) {
        sscanf(line, "%*s\t%f", &freq);
        matrix[1][cntr++] = freq;
    }
    zscores(matrix, 2, mat_size);
    printf("z-scores:\n");
    for (int j = 0; j < mat_size; ++j) {
        printf("%f\t%f\n", matrix[0][j], matrix[1][j]);
    }

    printf("Correlation distance:\n");
    printf("%f\n", corr_distance(&matrix[0][0], &matrix[1][0], mat_size));
    printf("Eucledian distance:\n");
    printf("%f\n", eucl_distance(&matrix[0][0], &matrix[1][0], mat_size));

    fclose(f1);
    fclose(f2);
}