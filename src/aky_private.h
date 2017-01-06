/*
    This file is part of Akypuera

    Akypuera is free software: you can redistribute it and/or modify
    it under the terms of the GNU Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Akypuera is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Public License for more details.

    You should have received a copy of the GNU Public License
    along with Akypuera. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __AKY_PRIVATE_H_
#define __AKY_PRIVATE_H_
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <rastro.h>
#include <string.h>
#include <poti.h>
#include "aky.h"
#include "aky_config.h"
#include "aky_rastro.h"


int AKY_translate_rank(MPI_Comm comm, int rank);
void aky_insert(MPI_Request * req, void **root, int mark);
void aky_remove(MPI_Request * req, void **root);
int aky_check(MPI_Request * req, void **root);
void aky_insert_irecv(MPI_Request *req);
void aky_remove_irecv(MPI_Request *req);
int aky_check_irecv(MPI_Request *req);
void aky_insert_isend(MPI_Request *req, int mark);
void aky_remove_isend(MPI_Request *req);
int aky_check_isend(MPI_Request *req);

int aky_key_init(void);
void aky_key_free(void);
char *aky_put_key(const char *type, int src, int dst, char *key, int n);
char *aky_get_key(const char *type, int src, int dst, char *key, int n);
void aky_paje_hierarchy(void);
int aky_dump_version (const char *program, char **argv, int argc);
int aky_dump_comment_file (const char *program, const char *filename);
int aky_dump_comment (const char *program, const char *comment);

//prototypes for aky_names.c
void name_init (void);
char *name_get (u_int16_t id);

#define AKY_DEFAULT_STR_SIZE 200
#define AKY_INPUT_SIZE 10000
#define AKY_KEY_TABLE_SIZE 1000
#define AKY_KEY_PTP "ptp"
#define AKY_KEY_1TN "1tn"
#define AKY_KEY_NT1 "1tn"
#define AKY_KEY_1TA "1ta"
#define AKY_KEY_AT1 "at1"

#endif //__AKY_PRIVATE_H_
