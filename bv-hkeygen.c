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

int main(int argc, char *args[])  /* n, t,q,d,sk.txt*/
{
        bv_swhe_context_t *params;
        params = bv_swhe_init(params, args[1], args[2], args[3], args[4], 10);
        long n = fmpz_get_ui(params->n);
	fmpz *ctr;
        ctr = _fmpz_vec_init(n);
        
	fmpz_poly_t e, sk, sk2, tmp, fx;
	fmpz_poly_init(e);
        fmpz_poly_init(sk);
        fmpz_poly_init(sk2);
        fmpz_poly_init(tmp);
        fmpz_poly_init(fx);
        fmpz_poly_set_coeff_ui(fx, 0, 1);
        fmpz_poly_set_coeff_ui(fx, n, 1);
        FILE *fp;
        if((fp = fopen(args[5], "r")) == NULL) {
                printf("file open error\n");
                exit(0);
        }
        fgets(str, 100000, fp);
        fmpz_poly_set_str(sk, str);
        fclose(fp);
        
        fmpz_poly_mul(sk2, sk, sk);
        fmpz_poly_rem_basecase(sk2, sk2, fx);
        fmpz_poly_scalar_smod_fmpz(sk2, sk2, params->q);
        
        hk_node_t *head, *s, *r;
	fmpz_t ti;
	fmpz_init(ti);
	fmpz_set_ui(ti, 1);
	long len = fmpz_clog(params->q, params->t), i;
	head = (hk_node_t *)malloc(sizeof(hk_node_t));
	head->next = NULL;
	r = head;
        char *hk1, *hk2;
        printf("%ld\n", len);
	for( i = 0 ; i < len ; i++ ) {
		s = (hk_node_t *)malloc(sizeof(hk_node_t));
		fmpz_poly_init(s->a);
		bv_swhe_unif_poly(s->a, n, params->q);
		bv_swhe_guassian_poly(ctr, e, n);
		fmpz_poly_init(s->b);
		fmpz_poly_mul(tmp, s->a, sk);
		fmpz_poly_scalar_addmul_fmpz(tmp, e, params->t);
		fmpz_poly_neg(s->b, tmp);
		fmpz_poly_scalar_addmul_fmpz(s->b, sk2, ti);
		fmpz_poly_rem_basecase(s->b, s->b, fx);
                fmpz_poly_scalar_smod_fmpz(s->b, s->b, params->q);
                
                hk1 = fmpz_poly_get_str(s->a);
                hk2 = fmpz_poly_get_str(s->b);
                
                printf("%s\n%s\n", hk1, hk2);
		fmpz_mul(ti, ti, params->t);
		r->next = s;
		r = s;
	}
	r->next = NULL;

	fmpz_poly_clear(sk2);
	fmpz_poly_clear(e);
	fmpz_poly_clear(tmp);
        fmpz_poly_clear(sk);
        fmpz_poly_clear(fx);
        _fmpz_vec_clear(ctr, n);
        fmpz_clear(ti);
        return 0;
}
