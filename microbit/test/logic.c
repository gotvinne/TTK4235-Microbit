#include "logic.h"



void bin(unsigned n) 
{ 
    /* step 1 */
    if (n > 1) 
        bin(n/2); //rekursivt kall
  
    /* step 2 */
    printf("%d", n % 2); 
} 

void test_logic(){

    unsigned int a = 0xe000; 
    unsigned int b = 0x1ff0; 

    unsigned int c = a | b; 

    printf("Binærtall til a\n"); 
    bin(a); 
    printf("\nBinærtall til b\n"); 
    bin(b);
    printf("\nResultat c\n");
    bin(c);
    printf("\n");



}

