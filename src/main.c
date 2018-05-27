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

#include <memory.h>
#include "kmer_counter.h"
#include "seq_distances.h"

int
main(int argc, char *argv[])
{
    if (!strcmp(argv[1], "kmf")) {
        char* filename = argv[2];
        int k = atoi(argv[3]);
        count_kmers(filename, k);
    } else if (!strcmp(argv[1], "dst")) {
        char* filename1 = argv[2];
        char* filename2 = argv[3];
        int k = atoi(argv[4]);
        FILE *f1;
        FILE *f2;
        char* line = NULL;
        ssize_t nread = 0;
        size_t len = 0;
        float freq;
        int cntr = 0;
        float *matrix[2];
        if (( matrix[0] = (float *) malloc(pow(k, 4) * sizeof(float)))==NULL) {
            fprintf(stderr,"run out of memory\n");
            exit(-1);
        }
        if (( matrix[1] = (float *) malloc(pow(k, 4) * sizeof(float)))==NULL) {
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
        while ((nread = getline(&line, &len, f1)) != -1) {
            sscanf(line, "%*s\t%f", &freq);
            matrix[0][cntr++] = freq;
        }
        line = NULL;
        nread = 0;
        len = 0;
        cntr = 0;
        while ((nread = getline(&line, &len, f2)) != -1) {
            sscanf(line, "%*s\t%f", &freq);
            matrix[1][cntr++] = freq;
        }
        zscores(matrix, 2, (int)pow(k, 4));
        printf("z-scores:\n");
        for (int j = 0; j < pow(k, 4); ++j) {
            printf("%f\t%f\n", matrix[0][j], matrix[1][j]);
        }

        printf("Correlation distance:\n");
        printf("%f\n", corr_distance(matrix[0], matrix[1], 16));
        printf("Eucledian distance:\n");
        printf("%f\n", eucl_distance(matrix[0], matrix[1], 16));

        fclose(f1);
        fclose(f2);
    } else {
        fprintf(stderr, "Unrecognized command '%s'.\n"
                        "See 'hiclures --help'.\n", argv[1]);
    }

    exit(EXIT_SUCCESS);
}
