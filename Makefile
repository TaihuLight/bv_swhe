sk:
	gcc -o sk local.c bv-skeygen.c -lflint -lgmp -lmpfr -lpthread -lm
pk:
	gcc -o pk local.c bv-pkeygen.c -lflint -lgmp -lmpfr -lpthread -lm
hk:
	gcc -o hk local.c bv-hkeygen.c -lflint -lgmp -lmpfr -lpthread -lm
enc:
	gcc -o enc local.c bv-enc.c -lflint -lgmp -lmpfr -lpthread -lm
dec:
	gcc -o dec local.c bv-dec.c -lflint -lgmp -lmpfr -lpthread -lm
mul:
	gcc -o mul local.c bv-mul.c -lflint -lgmp -lmpfr -lpthread -lm
add:
	gcc -o add local.c bv-add.c -lflint -lgmp -lmpfr -lpthread -lm
clear:
	rm sk && rm pk && rm hk && rm enc && rm dec && rm mul && rm add
all:
	make sk && make pk && make hk && make enc && make dec && make mul && make add
