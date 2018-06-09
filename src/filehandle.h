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

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PRACTICA_FILEHANDLE_H
#define PRACTICA_FILEHANDLE_H

/**
 * Initializes file memory-mapping using mmap.
 * @param fd file descriptor.
 * @param size file size.
 * @param offset reading starting point.
 * @param length number of bytes to be read. If it is 0, it will be read until the end of file.
 * @return address of the mapping
 */
char* imppdfile(int fd, off_t size, off_t offset, size_t length);


#endif //PRACTICA_FILEHANDLE_H
