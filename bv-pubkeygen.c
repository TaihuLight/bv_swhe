#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>
#include "flint/fmpz_vec.h"
#include "flint/fmpz_poly.h"
#include "flint/fmpz.h"
#include "flint/fmpz_mat.h"
#include <libswhe.h>

int main(int argc, char *args[]) /* n t q d sk*/
{
        bv_swhe_context_t *params;
        params = bv_swhe_init(params, args[1], args[2], args[3], args[4], 10);
        long n = fmpz_get_ui(params->n);
        
        fmpz_poly_t sk,fx;
        fmpz_poly_init(sk);
        fmpz_poly_init(fx);
        fmpz_poly_set_coeff_ui(fx, 0, 1);
        fmpz_poly_set_coeff_ui(fx, n, 1);
        fmpz_poly_set_str(sk, args[5]);
	fmpz *ctr;
        ctr = _fmpz_vec_init(n);
        
	fmpz_poly_t e, a0, a1;
	fmpz_poly_init(e);
        fmpz_poly_init(a0);
        fmpz_poly_init(a1);
	bv_swhe_guassian_poly(ctr, e, n);
        
	bv_swhe_unif_poly(a1, n, params->q);
        
	fmpz_poly_t tmp, tmp1, tmp2;
	fmpz_poly_init(tmp);
	fmpz_poly_init(tmp1);
	fmpz_poly_init(tmp2);
	        
	fmpz_poly_mul(tmp, a1, sk);
	fmpz_poly_scalar_mul_fmpz(tmp1, e, params->t);
	fmpz_poly_add(tmp2, tmp1, tmp);
	fmpz_poly_rem_basecase(tmp2, tmp2, fx);
        fmpz_poly_scalar_smod_fmpz(tmp2, tmp2, params->q);
        
	fmpz_poly_neg(a0, tmp2);
        
        char *pk1 = fmpz_poly_get_str(a1);
        char *pk0 = fmpz_poly_get_str(a0);
        printf("\"%s\" \"%s\"\n",pk0, pk1);

        fmpz_poly_clear(e);
	fmpz_poly_clear(tmp);
	fmpz_poly_clear(tmp1);
	fmpz_poly_clear(tmp2);
        fmpz_poly_clear(a0);
        fmpz_poly_clear(a1);
        _fmpz_vec_clear(ctr, n);
        return 0;
}
