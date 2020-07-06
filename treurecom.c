#include <stdio.h>
#include <string.h>
#include <math.h>

int  main(void){
	int  a;
    while ((a = getchar()) != EOF){
            if(a==35){
                while(a!=10){
                    a=getchar();
                }
            }
			else{
                putchar(a);
			}
	}
}
