#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
  FILE *input;
  int j;
  int var;
  char letra;
/*---------------------------------------------------------
Verifica cuales archivos fueron usados como input y se asegura de que solo haya cargado uno.
-----------------------------------------------------------*/
  printf("Este programa se ejecutó con %d argumento(s):\n",argc-1);
  for(j=1;j<argc;j++){
    printf("%s\n", argv[j]);
  }
  if(argc!=2){
    printf("se necesita solo un argumento además del nombre del ejecutable!\n EXIT!\n");
    exit(1);
    }
    else{
      printf("El archivo a usar es %s\n", argv[1]);
    }
//--------------------------------------------------------
    input=fopen(argv[1],"r");
    if(!input){
      printf("surgió un problema abriendo el archivo\n");
      exit(1);
    }
/*-----------------------------------------------------------------------
Cuenta cada letra del archivo
----------------------------------------------------------------------*/
    int a=0,e=0,i=0,o=0,u=0;
    while ((var = fgetc(input)) != EOF){
      if (var =='a'||var=='A'){
	a++;
      }
      if (var =='e'||var=='E'){
	e++;
      }
      if (var =='i'||var=='I'){
	i++;
      }
      if (var =='o'||var=='O'){
	o++;
      }
      if (var =='u'||var=='U'){
	u++;
      }
    }
    printf("a = %d\ne = %d\ni = %d\no = %d\nu = %d\n",a,e,i,o,u);
/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/   
    fclose(input);

    return 0;
}
