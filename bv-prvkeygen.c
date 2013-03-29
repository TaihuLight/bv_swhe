#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>
#include "flint/fmpz_vec.h"
#include "flint/fmpz_poly.h"
#include "flint/fmpz.h"
#include "flint/fmpz_mat.h"
#include "libswhe.h"

int main(int argc, char *args[])/*n t q d*/
{
        bv_swhe_context_t *params;
        params = bv_swhe_init(params, args[1], args[2], args[3], args[4], 10);
        long n = fmpz_get_ui(params->n);
        
        fmpz_poly_t sk;
        fmpz_poly_init(sk);
        fmpz *ctr;
        ctr = _fmpz_vec_init(n);
        bv_swhe_guassian_poly(ctr, sk, n);
        char *s = fmpz_poly_get_str(sk);
        printf("\"%s\"\n",s);
        fmpz_poly_clear(sk);
        _fmpz_vec_clear(ctr, n);
        return 0;
}