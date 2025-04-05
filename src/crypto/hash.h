// Copyright (c) 2014-2024, The Zone Project (forked from The Monero Project)
// All rights reserved under the same license terms as the Monero Project.

#pragma once

#include <stddef.h>

#define HASH_SIZE 32
#define HASH_DATA_AREA 136

typedef struct {
    unsigned char h[HASH_SIZE];
} hash_state;

void hash_process(hash_state *state, const unsigned char *buf, size_t count);
void hash_permutation(hash_state *state);
void hash_tree(const unsigned char *data, size_t count, unsigned char *hash);

void hash_extra_blake(const void *data, size_t length, unsigned char *hash);
void hash_extra_groestl(const void *data, size_t length, unsigned char *hash);
void hash_extra_jh(const void *data, size_t length, unsigned char *hash);
void hash_extra_skein(const void *data, size_t length, unsigned char *hash);
