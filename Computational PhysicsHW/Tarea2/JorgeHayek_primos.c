#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv){
  system("clear");
  int limite=10000000;
  int limiteinf=0;
  if(argc!=2){
    printf("Solo acepta un dato para intentar descomponer");
    exit(1);
  }
  int input=atoi(argv[1]);
  printf("El número introducido fue: %d\n",input);
  if (input>limite){
    printf("El número introducido es mayor a 10^6\n");
exit(1);
  }
 if (input<limiteinf){
    printf("El número introducido es menor a 0\n");
exit(1);
  }
/*------------------------------------------------------------------------
Checkpoint; input es el numero a descomponer
------------------------------------------------------------------------*/
char parla1[250];
	strcpy(parla1,"El número tiene más de dos factores, luego no es posible descomponerlo en solo dos factores primos. Al menos los tres primeros factores primos encontrados son:");  
char parla2[250];
	strcpy(parla2,"El número es primo, no es posible descomponerlo en dos factores primos.");
char parla3[250];
	strcpy(parla3,"La descomposicion entre números primos es posible, los números primos son:");
//printf("%s---- %s---- %s",parla1,parla2,parla3);


int i=2;
  float result;
  int num_factores=0;
 int factor[3];

  //  printf("numero de factores iniciales %d\n --> ",num_factores,factor1,factor2,factor3); CHECKPOINT

  while(input>1){
	result=input%i;
	if( (result)==0){
	  factor[num_factores]=i;
	  num_factores++;
	input=input/i;
	}   
	else{
	  i++;
	}
	if(num_factores>2)
	  printf("%s\n%d, %d, %d\n",parla1, factor[0],factor[1],factor[2]);
	  exit(1);
		}
  	}
  	if(num_factores<2){
   	 printf("%s\n",parla2);
    	exit(1);
}

	printf("%s\n\n%d,%d\n\n",parla3, factor[0],factor[1]);



//-------------------------------------------------------------------------
return 0;
}

