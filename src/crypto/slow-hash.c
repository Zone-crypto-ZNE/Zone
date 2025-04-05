// Copyright (c) 2014-2024, The Zone Project (forked from The Monero Project)
// All rights reserved under the same license terms as the Monero Project.

#include <stdint.h>
#include <string.h>
#include <stdio.h>

// SHA-256 Constants
static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// SHA-256 Functions
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SHR(x, n) ((x) >> (n))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIG1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define sig0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define sig1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

// SHA-256 Context Structure
typedef struct {
    uint32_t state[8];
    uint64_t count;
    uint8_t buffer[64];
} SHA256_CTX;

// Initialize SHA-256 context
static void sha256_init(SHA256_CTX *ctx) {
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
    ctx->count = 0;
}

// SHA-256 Transform Function
static void sha256_transform(SHA256_CTX *ctx, const uint8_t *data) {
    uint32_t a, b, c, d, e, f, g, h, t1, t2, w[64];
    int j;

    for (j = 0; j < 16; j++) {
        w[j] = (uint32_t)data[4 * j] << 24 | (uint32_t)data[4 * j + 1] << 16 |
               (uint32_t)data[4 * j + 2] << 8 | (uint32_t)data[4 * j + 3];
    }
    for (; j < 64; j++) {
        w[j] = sig1(w[j - 2]) + w[j - 7] + sig0(w[j - 15]) + w[j - 16];
    }

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (j = 0; j < 64; j++) {
        t1 = h + SIG1(e) + CH(e, f, g) + K[j] + w[j];
        t2 = SIG0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

// Update SHA-256 context with more data
static void sha256_update(SHA256_CTX *ctx, const uint8_t *data, size_t len) {
    size_t i;
    uint32_t j;

    j = (ctx->count >> 3) & 63;
    ctx->count += len << 3;

    if ((j + len) > 63) {
        memcpy(&ctx->buffer[j], data, (i = 64 - j));
        sha256_transform(ctx, ctx->buffer);
        for (; i + 63 < len; i += 64) {
            sha256_transform(ctx, &data[i]);
        }
        j = 0;
    } else {
        i = 0;
    }
    memcpy(&ctx->buffer[j], &data[i], len - i);
}

// Finalize SHA-256 and produce the hash
static void sha256_final(SHA256_CTX *ctx, uint8_t *hash) {
    uint32_t i;
    uint64_t count;

    count = ctx->count;
    i = (count >> 3) & 63;

    ctx->buffer[i++] = 0x80;
    if (i > 56) {
        memset(&ctx->buffer[i], 0, 64 - i);
        sha256_transform(ctx, ctx->buffer);
        memset(ctx->buffer, 0, 56);
    } else {
        memset(&ctx->buffer[i], 0, 56 - i);
    }

    ctx->buffer[56] = count >> 56;
    ctx->buffer[57] = count >> 48;
    ctx->buffer[58] = count >> 40;
    ctx->buffer[59] = count >> 32;
    ctx->buffer[60] = count >> 24;
    ctx->buffer[61] = count >> 16;
    ctx->buffer[62] = count >> 8;
    ctx->buffer[63] = count;

    sha256_transform(ctx, ctx->buffer);

    for (i = 0; i < 8; i++) {
        hash[i * 4] = ctx->state[i] >> 24;
        hash[i * 4 + 1] = ctx->state[i] >> 16;
        hash[i * 4 + 2] = ctx->state[i] >> 8;
        hash[i * 4 + 3] = ctx->state[i];
    }
}

// Zone's SHA-256-based hash function
void zone_slow_hash(const void *data, size_t length, char *hash) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, data, length);
    sha256_final(&ctx, (uint8_t *)hash);
}

// Dummy allocation/free functions (no longer needed for SHA-256)
void slow_hash_allocate_state(void) {
    // No memory allocation needed for SHA-256
}

void slow_hash_free_state(void) {
    // No memory to free for SHA-256
}
