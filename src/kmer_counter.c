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

#include "kmer_counter.h"

void
count_kmers(char* filename, int k)
{
    int fd;
    char* addr;
    off_t offset = 0, lastoffset;
    sequence_t S;
    struct stat sb;

    const int freqSize = (int) pow(4, k);
    int* frequencies = malloc(freqSize * sizeof(int));
    for(int n = 0; n < freqSize; n++) {
        frequencies[n] = 0;
    }

    fd = open(filename, O_RDONLY);

    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1) /* To obtain file size. */
        handle_error("fstat");

    addr = imppdfile(fd, sb.st_size, 0, 0); /* Memmory-mapped file address. */

    do {
        lastoffset = loadseq(addr, &S, offset, sb.st_size);
        #pragma omp parallel for /* Parallelized loop. */
        for (off_t i = S.startAddress; i < S.endAddress; ++i) {
            int j = 0, l = 0;
            char buffer[k + 1];
            buffer[k] = '\0';
            while (j < k) { // K-mer construction.
                char next = (char) toupper(addr[i + l]);
                if (next == 'A' ||
                    next == 'C' ||
                    next == 'G' ||
                    next == 'T') {
                    buffer[j] = next;
                    j++;
                }
                l++;
                if ((i + l) == S.endAddress + 1) break; /* If there are not any base else, end the construction. */
            }
            if (j == k) { // completed kmer
                #pragma omp atomic
                frequencies[kmer2num(buffer, k)]++;
            }
        }

        char buffer[k + 1];
        buffer[k] = '\0';
        for (int m = 0; m < freqSize; ++m) { // Print frequencies.
            nucleotididx(buffer, m, k);
            printf("%s\t%d\n", buffer, frequencies[m]);
        }
        offset = S.endAddress - 1;
    }  while(lastoffset != sb.st_size);

    /* Close the file. */
    if (munmap(addr, (size_t) sb.st_size) == -1)
        handle_error("munmap");
    if (close(fd) == -1)
        handle_error("close");
}