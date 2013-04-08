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

int main(int argc, char *args[])/* n,t,q,d,ct1.txt,ct2.txt*/
{
        bv_swhe_context_t *params;
        params = bv_swhe_init(params, args[1], args[2], args[3], args[4], 10);
        long n = fmpz_get_ui(params->n);
        
        fmpz_poly_t c10, c11,fx,nc0, nc1 ,c20,c21;
        fmpz_poly_init(c10);
        fmpz_poly_init(c11);
        fmpz_poly_init(fx);
        fmpz_poly_init(c20);
        fmpz_poly_init(c21);
        fmpz_poly_init(nc1);
        fmpz_poly_init(nc0);

        fmpz_poly_set_coeff_ui(fx, 0, 1);
        fmpz_poly_set_coeff_ui(fx, n, 1);
        
        FILE *fp;
        
        if((fp = fopen(args[5], "r")) == NULL)
        {
                printf("file read error\n");
                exit(0);
        }
        fgets(str, 100000, fp);
        fmpz_poly_set_str(c10, str);
        fgets(str, 100000, fp);
        fmpz_poly_set_str(c11, str);
        fclose(fp);
        
        if((fp = fopen(args[6], "r")) == NULL)
        {
                printf("file read error\n");
                exit(0);
        }
        fgets(str, 100000, fp);
        fmpz_poly_set_str(c20, str);
        fgets(str, 100000, fp);
        fmpz_poly_set_str(c21, str);
        fclose(fp);

        
	fmpz_poly_add(nc0, c10, c20);
	fmpz_poly_add(nc1, c11, c21);
        fmpz_poly_rem_basecase(nc0, nc0, fx);
	fmpz_poly_rem_basecase(nc1, nc1, fx);
	fmpz_poly_scalar_smod_fmpz(nc0, nc0, params->q);
	fmpz_poly_scalar_smod_fmpz(nc1, nc1, params->q);
        
        char *ct1 = fmpz_poly_get_str(nc1);
        char *ct0 = fmpz_poly_get_str(nc0);
        printf("%s\n%s\n",ct0, ct1);

        
        fmpz_poly_clear(c10);
        fmpz_poly_clear(c11);
        fmpz_poly_clear(c20);
        fmpz_poly_clear(c21);
        fmpz_poly_clear(fx);
	fmpz_poly_clear(nc0);
        fmpz_poly_clear(nc1);
        
        return 0;

}