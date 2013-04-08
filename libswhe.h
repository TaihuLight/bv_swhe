#ifndef LIBSWHE_H
#define LIBSWHE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>
#include "flint/fmpz_vec.h"
#include "flint/fmpz_poly.h"
#include "flint/fmpz.h"
#include "flint/fmpz_mat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hk_node_t{
	fmpz_poly_t a,b;
	struct hk_node_t *next;
} hk_node_t;

typedef struct bv_swhe_context_t {
        fmpz_t q;
        fmpz_t t;
        fmpz_t d;
        fmpz_t n;
} bv_swhe_context_t;

static const double pi = 3.1415926;
static double dvn = 1.01; /* standard deviation of Guassian distribution*/
static long chrnd = 0;

bv_swhe_context_t *bv_swhe_init(bv_swhe_context_t *ctx, char *nn, char *tt, char *qq, char *dd, int b);
double bv_swhe_get_dvn();
void hcrypt_random(mpz_t r);
fmpz *bv_swhe_samplez(fmpz *vec, long n);
void bv_swhe_guassian_poly(fmpz *c, fmpz_poly_t poly, long n);
void bv_swhe_unif_poly(fmpz_poly_t poly, long n, fmpz_t q);
        
#ifdef __cplusplus
}
#endif
#endif