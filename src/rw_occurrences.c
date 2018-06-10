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
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "hits.h"
#include "globals.h"
#include "kmer_counter.h"
#include "rw_occurrences.h"

void
s_read(char * filename, int k)
{
    unsigned long kmer_num = 0;
    int kmer_idx;
    FILE * fp;
    fp = fopen(filename, "re");

    while (1) {
        fscanf(fp, "%lu\t%d\n", &kmer_num, &kmer_idx);
        fread(&kmer_num, sizeof(unsigned long), 1, fp);
        fread(&kmer_idx, sizeof(int), 1, fp);
        if(feof(fp)) {
            break;
        }
//        kmer_num = ntohll(kmer_num);
        char buffer[k + 1];
        buffer[k] = '\0';
        nucleotididx(buffer, kmer_num, k);
        printf("%s\t%d\n", buffer, kmer_idx);
    }
    fclose(fp);
}

void
s_write(char* infile, char* outfile, const int k)
{
    FILE* of;
    int fd;
    char* addr;
    off_t offset = 0, lastoffset;
    sequence_t S;
    struct stat sb;

    fd = open(infile, O_RDONLY | O_CLOEXEC);
    of = fopen(outfile, "we");

    if (fd == -1) {
        handle_error("open");
    }
    if (of == NULL) {
        handle_error("fopen");
    }
    if (fstat(fd, &sb) == -1) { /* To obtain file size. */
        handle_error("fstat");
    }

    addr = imppdfile(fd, sb.st_size, 0, 0); /* Memmory-mapped file address. */

    do {
        lastoffset = loadseq(addr, &S, offset, sb.st_size);
        int kmer_pos = 0;
        for (off_t i = S.startAddress; i < S.endAddress; ++i) {
            int j = 0, l = 0;
            char buffer[k + 1];
            buffer[k] = '\0';
            if (!isBase((char) toupper(addr[i]))) {
                if (!isLineBreak((char) toupper(addr[i]))) {
                    kmer_pos++;
                }
                continue;
            }
            while (j < k) { // K-mer construction.
                char next = (char) toupper(addr[i + l]);
                if (isBase(next)) {
                    buffer[j] = next;
                    j++;
                } else if (!isLineBreak(next)) {
                    break;
                }
                l++;
                if ((i + l) == S.endAddress + 1) {
                    break; /* If there are not any base else, end the construction. */
                }
            }
            if (j == k) { // completed kmer
                // fprintf(stderr, "%s\t%llu\n", buffer, kmer_pos);
//                unsigned long kmr = htonll(kmer2num(buffer, k));
//                fwrite(&kmr, sizeof(unsigned long), 1, of);
//                fwrite(&kmer_pos, sizeof(int), 1, of);
                fprintf(of, "%lu\t%d\n", (unsigned long) kmer2num(buffer, k), kmer_pos);
            }
            kmer_pos++;
        }
        offset = S.endAddress - 1;
    } while(lastoffset != sb.st_size);

    /* Close the file. */
    if (munmap(addr, (size_t) sb.st_size) == -1) {
        handle_error("munmap");
    }
    if (close(fd) == -1) {
        handle_error("close");
    }
    if (fclose(of) == EOF) {
        handle_error("fclose");
    }
}
