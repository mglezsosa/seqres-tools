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

#include <stdlib.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include "sequence.h"
#include "hits.h"

void
collapse_occurrences(FILE* fp1, FILE* fc1)
{
    unsigned long kmer_num;
    unsigned long last_kmer_num;
    unsigned int kmer_idx;
    int first = 1;

    Array a1;
    initArray(&a1, 50);

    while (1) {
        fscanf(fp1, "%lu\t%d\n", &kmer_num, &kmer_idx);
        if (feof(fp1)) {
            fprintf(fc1, "\t%lu", a1.used);
            for (int i = 0; i < a1.used; ++i) {
                fprintf(fc1, "\t%d", a1.array[i]);
            }
            break;
        }
        if (last_kmer_num == kmer_num) {
            insertArray(&a1, kmer_idx);
        } else {
            last_kmer_num = kmer_num;
            if (first) {
                fprintf(fc1, "%lu", last_kmer_num);
                insertArray(&a1, kmer_idx);
                first = 0;
                continue;
            }
            fprintf(fc1, "\t%lu", a1.used);
            for (int i = 0; i < a1.used; ++i) {
                fprintf(fc1, "\t%d", a1.array[i]);
            }
            fprintf(fc1, "\n%lu", last_kmer_num);
            freeArray(&a1);
            initArray(&a1, 50);
            insertArray(&a1, kmer_idx);
            last_kmer_num = kmer_num;
        }
    }
}

void
hits(FILE* fc1, FILE* fc2, FILE* out)
{
    static char line1[10000000];
    static char line2[10000000];
    while (fgets(line1, sizeof line1, fc1) && fgets(line2, sizeof line2, fc2)) {
        char* str1 = line1;
        char* str2 = line2;
        int kmer_num1, kmer_num2;

        int num1 = sscanf(str1, "%d", &kmer_num1);
        int num2 = sscanf(str2, "%d", &kmer_num2);
        while (kmer_num1 < kmer_num2) {
            if (!fgets(line1, sizeof line1, fc1)) return;
            str1 = line1;
            num1 = sscanf(line1, "%d", &kmer_num1);
        }
        while (kmer_num2 < kmer_num1) {
            if (!fgets(line2, sizeof line2, fc2)) return;
            str2 = line2;
            num2 = sscanf(line2, "%d", &kmer_num2);
        }

        while (*str1 != '\t') str1++;
        str1++;
        int num_occ1;
        num1 = sscanf(str1, "%d", &num_occ1);
        int occs1[num_occ1];
        for (int i = 0; i < num_occ1; ++i) {
            while (*str1 != '\t') str1++;
            str1++;
            num1 = sscanf(str1, "%d", &occs1[i]);
        }

        while (*str2 != '\t') str2++;
        str2++;
        int num_occ2;
        num2 = sscanf(str2, "%d", &num_occ2);
        int occs2[num_occ2];
        for (int i = 0; i < num_occ2; ++i) {
            while (*str2 != '\t') str2++;
            str2++;
            num2 = sscanf(str2, "%d", &occs2[i]);
        }

        fprintf(out, "%d", kmer_num1);
        for (int j = 0; j < num_occ1; ++j) {
            for (int i = 0; i < num_occ2; ++i) {
                fprintf(out, "\t%d,%d", occs1[j], occs2[i]);
            }
        }
        fprintf(out, "\n");
    }
}
