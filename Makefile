libswhe.a: bv_swhe.o
	ar rcs libswhe.a bv_swhe.o

bv_swhe.o: bv_swhe.c
	gcc -c bv_swhe.c

install: 
	cp libswhe.a /usr/local/lib
	cp libswhe.h /usr/local/include
clean:
	rm /usr/local/lib/libswhe.a
	rm /usr/local/include/libswhe.h

compile:
	gcc -o prv bv-prvkeygen.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe
	gcc -o pub bv-pubkeygen.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe
	gcc -o hkey bv-hkeygen.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe
	gcc -o enc bv-enc.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe
	gcc -o dec bv-dec.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe
	gcc -o sum bv-sum.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe
	gcc -o pro bv-product.c -lflint -lgmp -lmpfr -lpthread -lm -lswhe