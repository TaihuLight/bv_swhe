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

int main(int argc, char *args[])/*n t q d ct1.txt ct2.txt hk.txt*/
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
        
        hk_node_t *head, *s, *r;
        head = (hk_node_t *)malloc(sizeof(hk_node_t));
	head->next = NULL;
	r = head;
        long i;
        fmpz_t hklen;
        fmpz_init(hklen);
        if((fp = fopen(args[7], "r")) == NULL)
        {
                printf("file read error\n");
                exit(0);
        }
        fgets(str, 10, fp);
        fmpz_set_str(hklen, str, 10);
        long len = fmpz_get_ui(hklen);
        for(i = 0 ; i < len ; i++) {
                s = (hk_node_t *)malloc(sizeof(hk_node_t));
		fmpz_poly_init(s->a);
                fgets(str, 100000, fp);
                fmpz_poly_set_str(s->a, str);
                fmpz_poly_init(s->b);
                fgets(str, 100000, fp);
                fmpz_poly_set_str(s->b, str);
                r->next = s;
		r = s;
        }
        r->next = NULL;
        fclose(fp);
	fmpz_poly_t tmp0, tmp1, tmp2, tmp;
	fmpz_poly_init(tmp0);
	fmpz_poly_mul(tmp0, c10, c20);
	fmpz_poly_rem_basecase(tmp0, tmp0, fx);
        fmpz_poly_scalar_smod_fmpz(tmp0, tmp0, params->q);
        
	fmpz_poly_init(tmp1);
	fmpz_poly_init(tmp);
	fmpz_poly_mul(tmp, c10, c21);
	fmpz_poly_mul(tmp1, c20, c11);
	fmpz_poly_add(tmp1, tmp1, tmp);
	fmpz_poly_rem_basecase(tmp1, tmp1, fx);
        fmpz_poly_scalar_smod_fmpz(tmp1, tmp1, params->q);
        
	fmpz_poly_init(tmp2);
	fmpz_poly_mul(tmp2, c11, c21);
	fmpz_poly_rem_basecase(tmp2, tmp2, fx);
	fmpz_poly_scalar_smod_fmpz(tmp2, tmp2, params->q);
        
	len = fmpz_clog(params->q, params->t);
        long ll = fmpz_poly_length(tmp2);
	long j;
	fmpz_t hold;
	fmpz_init(hold);
	fmpz_mat_t bits;
	fmpz_mat_init(bits, ll, len);
	fmpz_mat_zero(bits);
	for ( i = 0 ; i < ll ; ++i ) {
		fmpz_poly_get_coeff_fmpz(hold, tmp2, i);
		j = 0;
                if (fmpz_cmp_si(hold, 0)<0) {
                        fmpz_neg(hold, hold);
                        fmpz_t negval;
                        fmpz_init(negval);
                        while ( !fmpz_is_zero(hold) ) {
                                fmpz_mod(negval, hold, params->t);
                                fmpz_neg(fmpz_mat_entry(bits, i, j), negval);
                                fmpz_tdiv_q(hold, hold, params->t);
                                j++;
                        }
                        fmpz_clear(negval);
                }
                else {
                        while ( !fmpz_is_zero(hold) ) {
                                fmpz_mod(fmpz_mat_entry(bits, i, j), hold, params->t);
                                fmpz_tdiv_q(hold, hold, params->t);
                                j++;
                        }
                }
		
	}
        //  fmpz_mat_print_pretty(bits);
        
	fmpz_poly_t xtmp,multmp;
	fmpz_poly_init(multmp);
        fmpz_poly_init(xtmp);
        
	r = head->next;
	for( i = 0 ; i < len ; i++ ) {
                
		for( j = 0; j < ll ; ++j ) {
			fmpz_poly_set_coeff_fmpz(xtmp, j, fmpz_mat_entry(bits, j, i));
		}
                
		fmpz_poly_mul(multmp, xtmp, r->a);
		fmpz_poly_add(tmp1, tmp1, multmp);
                
		fmpz_poly_mul(multmp, xtmp, r->b);
		fmpz_poly_add(tmp0, tmp0, multmp);
                
                r = r->next;
	}
        
	fmpz_poly_rem_basecase(nc0, tmp0, fx);
	fmpz_poly_rem_basecase(nc1, tmp1, fx);
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
	fmpz_poly_clear(tmp);
	fmpz_poly_clear(tmp1);
	fmpz_poly_clear(tmp0);
	fmpz_poly_clear(tmp2);
        fmpz_poly_clear(xtmp);
        fmpz_clear(hklen);
	fmpz_poly_clear(multmp);
	fmpz_clear(hold);
	fmpz_mat_clear(bits);
        return 0;
}
