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

int main(int argc, char *args[])/* n,t,q,d,co,c1,sk*/
{
        bv_swhe_context_t *params;
        params = bv_swhe_init(params, args[1], args[2], args[3], args[4], 10);
        long n = fmpz_get_ui(params->n);
	fmpz *ctr;
        ctr = _fmpz_vec_init(n);

        fmpz_poly_t fx,m,c0,c1,sk;
        fmpz_poly_init(sk);
        fmpz_poly_init(fx);
        fmpz_poly_init(c0);
        fmpz_poly_init(c1);
        fmpz_poly_init(m);
        fmpz_poly_set_coeff_ui(fx, 0, 1);
        fmpz_poly_set_coeff_ui(fx, n, 1);
        fmpz_poly_set_str(c0, args[5]);
        fmpz_poly_set_str(c1, args[6]);
        fmpz_poly_set_str(sk, args[7]);
        
	fmpz_poly_t tmp;
	fmpz_poly_init(tmp);
	fmpz_poly_mul(tmp, c1, sk);
	fmpz_poly_rem_basecase(tmp, tmp, fx);
        fmpz_poly_scalar_smod_fmpz(tmp, tmp, params->q);
        
	fmpz_poly_add(tmp, tmp, c0);
        fmpz_poly_rem_basecase(tmp, tmp, fx);
        
	fmpz_poly_scalar_smod_fmpz(tmp, tmp, params->q);
	fmpz_poly_scalar_smod_fmpz(m, tmp, params->t);
        
        char *ms = fmpz_poly_get_str(m);
        printf("\"%s\"\n", ms);
        
        fmpz_poly_clear(sk);
        fmpz_poly_clear(c0);
        fmpz_poly_clear(c1);
        fmpz_poly_clear(m);
	fmpz_poly_clear(fx);

	fmpz_poly_clear(tmp);
        return 0;
}