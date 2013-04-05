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

char str[100000];

int main(int argc, char *args[])/*n,t,q,d,pk.txt(a0,a1),m*/
{
        bv_swhe_context_t *params;
        params = bv_swhe_init(params, args[1], args[2], args[3], args[4], 10);
        long n = fmpz_get_ui(params->n);
	fmpz *ctr;
        ctr = _fmpz_vec_init(n);
        
        fmpz_poly_t a0,a1,fx,m,c0,c1;
        fmpz_poly_init(a0);
        fmpz_poly_init(a1);
        fmpz_poly_init(fx);
        fmpz_poly_init(c0);
        fmpz_poly_init(c1);
        fmpz_poly_init(m);
        fmpz_poly_set_coeff_ui(fx, 0, 1);
        fmpz_poly_set_coeff_ui(fx, n, 1);
        FILE *fp;
        
        if((fp = fopen(args[5], "r")) == NULL)
        {
                printf("file read error\n");
                exit(0);
        }
        fgets(str, 100000, fp);
        fmpz_poly_set_str(a0, str);
        fgets(str, 100000, fp);
        fmpz_poly_set_str(a1, str);
        fclose(fp);
        fmpz_poly_set_str(m, args[6]);
	fmpz_poly_t u, f, g, tmp, tmp1;
	fmpz_poly_init(u);
	fmpz_poly_init(f);
	fmpz_poly_init(g);
	bv_swhe_guassian_poly(ctr, u, n);
	bv_swhe_guassian_poly(ctr, f, n);
	bv_swhe_guassian_poly(ctr, g, n);
        
	fmpz_poly_init(tmp);
	fmpz_poly_init(tmp1);
	fmpz_poly_mul(tmp, a0, u);
	fmpz_poly_scalar_mul_fmpz(tmp1, g, params->t);
	fmpz_poly_add(tmp, tmp, tmp1);
	fmpz_poly_add(tmp, tmp, m);
	fmpz_poly_rem_basecase(tmp, tmp, fx);
	fmpz_poly_scalar_smod_fmpz(c0, tmp, params->q);
        
	fmpz_poly_mul(tmp, a1, u);
	fmpz_poly_scalar_mul_fmpz(tmp1, f, params->t);
	fmpz_poly_add(tmp, tmp, tmp1);
	fmpz_poly_rem_basecase(tmp, tmp, fx);
	fmpz_poly_scalar_smod_fmpz(c1, tmp, params->q);
        
        char *ct1 = fmpz_poly_get_str(c1);
        char *ct0 = fmpz_poly_get_str(c0);
        printf("%s\n%s\n",ct0, ct1);
        
        fmpz_poly_clear(a0);
        fmpz_poly_clear(a1);
        fmpz_poly_clear(c0);
        fmpz_poly_clear(c1);
        fmpz_poly_clear(m);
	fmpz_poly_clear(u);
	fmpz_poly_clear(f);
	fmpz_poly_clear(g);
	fmpz_poly_clear(tmp);
	fmpz_poly_clear(tmp1);
        return 0;
}