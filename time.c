#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
        clock_t start1, finish1, start2, finish2, start3, finish3, start4, finish4, start5, finish5, start6, finish6, start7, finish7;
	double  dur1,dur2,dur3,dur4,dur5,dur6,dur7;
	start1=clock();
	system("./sk 1024 2 144115188076060673 2 > sk.txt");
	finish1=clock();
	dur1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;
	printf( "prvkeygen: %f seconds\n", dur1);
        
	start2=clock();
	system("./pk 1024 2 144115188076060673 2 sk.txt > pk.txt");
	finish2=clock();
	dur2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	printf( "pubkeygen: %f seconds\n", dur2);
        
	 start3=clock();
        system("./hk 1024 2 144115188076060673 2 sk.txt > hk.txt");
         finish3=clock();
         dur3 = (double)(finish3 - start3) / CLOCKS_PER_SEC;
         printf( "hkeygen: %f seconds\n", dur3);
         
         start4=clock();
         system("./enc 1024 2 144115188076060673 2 pk.txt \"3  1 0 1\" > ct.txt");
         finish4=clock();
         dur4 = (double)(finish4 - start4) / CLOCKS_PER_SEC;
         printf( "encrypt: %f seconds\n", dur4);
        
        start5=clock();
	system("./mul 1024 2 144115188076060673 2 ct.txt ct.txt hk.txt > nct.txt");
	finish5=clock();
	dur5 = (double)(finish5 - start5) / CLOCKS_PER_SEC;
	printf( "mul: %f seconds\n", dur5);
        
        start6=clock();
	system("./add 1024 2 144115188076060673 2 ct.txt ct.txt > nct1.txt");
	finish6=clock();
	dur6 = (double)(finish6 - start6) / CLOCKS_PER_SEC;
	printf( "add: %f seconds\n", dur6);
        
	start7=clock();
	system("./dec 1024 2 144115188076060673 2 ct.txt sk.txt");
	finish7=clock();
	dur7 = (double)(finish7 - start7) / CLOCKS_PER_SEC;
	printf( "decrypt: %f seconds\n", dur7);
        return 0;
}