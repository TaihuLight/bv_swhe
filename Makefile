prv:
	gcc -o prv bv_swhe.c bv-prvkeygen.c -lflint -lgmp -lmpfr -lpthread -lm
pub:
	gcc -o pub bv_swhe.c bv-pubkeygen.c -lflint -lgmp -lmpfr -lpthread -lm
hk:
	gcc -o hk bv_swhe.c bv-hkeygen.c -lflint -lgmp -lmpfr -lpthread -lm
enc:
	gcc -o enc bv_swhe.c bv-enc.c -lflint -lgmp -lmpfr -lpthread -lm
dec:
	gcc -o dec bv_swhe.c bv-dec.c -lflint -lgmp -lmpfr -lpthread -lm
pro:
	gcc -o pro bv_swhe.c bv-product.c -lflint -lgmp -lmpfr -lpthread -lm
sum:
	gcc -o sum bv_swhe.c bv-sum.c -lflint -lgmp -lmpfr -lpthread -lm
