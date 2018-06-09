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
#include "rw_occurrences.h"
#include "hits.h"
#include "globals.h"

int
main(int argc, char *argv[])
{
    if (!strcmp(argv[1], "kmf")) {
        char* filename = argv[2];
        int k = atoi(argv[3]);
        count_kmers(filename, k);
    }
    else if (!strcmp(argv[1], "dst")) {
        char *filename1 = argv[2];
        char *filename2 = argv[3];
        int k = atoi(argv[4]);
        compute_distances(filename1, filename2, k);
    }
    else if (!strcmp(argv[1], "reado")) {
            s_read(argv[2], atoi(argv[3]));
    }
    else if (!strcmp(argv[1], "collapse")) {
        FILE* fp1 = fopen(argv[2], "re");
        char buffer[50];
        sprintf(buffer, "%s_collapse", argv[2]);
        FILE* fc1 = fopen(buffer, "we");
        collapse_occurrences(fp1, fc1);
        fclose(fp1);
        fclose(fc1);
    }
    else if (!strcmp(argv[1], "writeo")) {
        s_write(argv[3], argv[4], atoi(argv[2]));
    }
    else if (!strcmp(argv[1], "hits")) {
        char* profile1 = argv[2];
        char* profile2 = argv[3];
        char* outfile = argv[4];

        FILE* f1 = fopen(profile1, "r+");
        if (f1 == NULL) {
            handle_error("open");
        }

        FILE* f2 = fopen(profile2, "r+");
        if (f2 == NULL) {
            handle_error("open");
        }

        FILE* out = fopen(outfile, "w");
        if (out == NULL) {
            handle_error("open");
        }

        hits(f1, f2, out);

        fclose(out);
        fclose(f1);
        fclose(f2);
    }
    else {
        fprintf(stderr, "Unrecognized command '%s'.\n"
                        "See 'hiclures --help'.\n", argv[1]);
    }

    exit(EXIT_SUCCESS);
}
