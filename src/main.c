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
        compute_distances(filename1, filename2, k);
    } else {
        fprintf(stderr, "Unrecognized command '%s'.\n"
                        "See 'hiclures --help'.\n", argv[1]);
    }

    exit(EXIT_SUCCESS);
}
