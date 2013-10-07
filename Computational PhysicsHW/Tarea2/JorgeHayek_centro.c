#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float calc_pot(float a,float b,float c,float d,float e,float f);
//Main------------------------------------------------------------------


int main(int argc, char **argv)
{
  FILE *input;
  int num_lineas;
  int h,i,j,k,l;
  int var;
  int index;
  float El_mayor;
/*---------------------------------------------------------
Verifica cuales archivos fueron usados como input y se asegura de que solo haya cargado uno.
-----------------------------------------------------------*/
  printf("Este programa se ejecutó con %d argumento(s):\n",argc-1);
  for(i=1;i<argc;i++){
    printf("%s\n", argv[i]);
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
/*---------------------------------------------------------
toma como archivo base el primer argumento y cuenta sus lineas
-----------------------------------------------------------*/
    num_lineas=0;
    while ((var = fgetc(input)) != EOF){
      if (var =='\n')
	++num_lineas;
    }

    printf("Número de lineas del archivo:\n -->%d\n",num_lineas); 

/*---------------------------------------------------------
Data allocation
-----------------------------------------------------------*/ 
    float *x_axis;
    float *y_axis;
    float *z_axis;
   
    x_axis = malloc(num_lineas * sizeof(float));
    y_axis = malloc(num_lineas * sizeof(float));
    z_axis = malloc(num_lineas * sizeof(float));

    /*   if(!x_axis||!y_axis||!z_axis){
      printf("Algo salió mal con la reserva de espacio para los arrays x, y o z\n");
      exit(1);
      }*/
/*---------------------------------------------------------
Registro de Datos en los arrays
-----------------------------------------------------------*/
    rewind(input);
    for(j=0;j<num_lineas;j++){
      fscanf(input, "%f %f %f",&x_axis[j],&y_axis[j],&z_axis[j]);


      if(!x_axis[j]||!y_axis[j]||!z_axis[j]){
	printf("Existe una linea vacia o hay un problema con la linea %d en el archivo\n",j);
	exit(1);
     } 
    }
    
    /*    
    for(j=0;j<num_lineas;j++){
      printf("%f %f %f\n",x_axis[j], y_axis[j], z_axis[j]);
    }

    */
//Checkpoint 
/*---------------------------------------------------------
Calculo de potencial, filtro
-------------------------------------------------*/   
    float datum;
    float phi[num_lineas];
    index =-1;
    float a,b,c,d,e,f;

    for(k=0;k<num_lineas;k++){
      datum=0.0;
      phi[k]=0.0;
      a=x_axis[k];
      b=y_axis[k];
      c=z_axis[k];
      for(l=0;l<num_lineas;l++){
      d=x_axis[l];
      e=y_axis[l];
      f=z_axis[l];
	if (l!=k){
	 datum+=calc_pot(a,b,c,d,e,f);
	}
      }
      phi[k]=datum;

      if(El_mayor<phi[k]){
	El_mayor=phi[k];
	index=k;
      }
      
/* 
    if(El_mayor==phi[k]){
	printf("Existen dos potenciales iguales\n");
      }
*/

    }
    
    
  //--------------------------------------------------------

    if(index==-1){
      printf("index has not evolved\n");    
    }



/*---------------------------------------------------------
Entrega de datos
-----------------------------------------------------------*/
    printf("---------------------\nLa posicion del minimo de potencial es:\n\n%f %f %f\n\n",x_axis[index], y_axis[index], z_axis[index]);
/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/   
    fclose(input);

    return 0;
}



/*---------------------------------------------------------
Funciones
-----------------------------------------------------------*/  
float calc_pot(float a,float b,float c,float d,float e,float f){
    float resultado;
    float delta_x,delta_y,delta_z,potx,poty,potz,denominador,raiz,den_comp;
	  resultado=0.0;
	  delta_x=0.0;
	  delta_y=0.0;
	  delta_z=0.0;
	  potx=0.0;
	  poty=0.0;
	  potz=0.0;
	  denominador=0.0;
          raiz=0.0;
	  den_comp=0.0;

	 delta_x=a-d;
	 delta_y=b-e;
	 delta_z=c-f;

	 potx = delta_x * delta_x;
	 poty = delta_y * delta_y;
	 potz = delta_z * delta_z;

	 denominador=potx+poty+potz;
	 den_comp=sqrt(denominador);

	 resultado=1/(den_comp);
	 return resultado;
}



