#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>

//Main------------------------------------------------------------------

int main(int argc, char **argv)
{
  gsl_matrix *Original;
  gsl_matrix *Ggsl;
  gsl_vector *GTgsl;
  gsl_matrix *GtimeGTgsl;
  gsl_matrix *inverse;
  gsl_vector *Vgsl;
  gsl_vector *posYgsl;


  FILE *input;
  double num_lineas;
  int i,j;
  double var;
  double grado;

/*---------------------------------------------------------
Verifica cuales archivos fueron usados como input y se asegura de que solo haya cargado uno.
-----------------------------------------------------------*/
  printf("Este programa se ejecutó con %d argumento(s):\n",argc-1);
  for(i=1;i<argc;i++){
    printf("%s\n", argv[i]);
  }
  if(argc!=3){
    printf("se necesitan dos argumentos además del nombre del ejecutable!,\n el archivo y el grado del polinomio.\n EXIT!\n");
    exit(1);
    }
    else{
      printf("El archivo a usar es %s\n", argv[1]);
      grado=atoi(argv[2]);
      printf("El grado del polinomio a ajustar es %f\n", grado);
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
    num_lineas=0.0;
    while ((var = fgetc(input)) != EOF){
      if (var =='\n')
	++num_lineas;
    }

    printf("Número de lineas del archivo:\n -->%f\n",num_lineas); 

/*---------------------------------------------------------
Data allocation
-----------------------------------------------------------*/ 
    float *x;
    float *d;
 
   
    x = malloc(num_lineas * sizeof(float));
    d = malloc(num_lineas * sizeof(float));
 

    /*   if(!x||!d){
      printf("Algo salió mal con la reserva de espacio para los arrays x o y\n");
      exit(1);
      }*/
/*---------------------------------------------------------
Registro de Datos en los arrays
-----------------------------------------------------------*/
    rewind(input);
    for(j=0;j<num_lineas;j++){
      fscanf(input, "%f %f",&x[j],&d[j]);


      if(!x[j]||!d[j]){
	printf("Existe una linea vacia o hay un problema con la linea %d en el archivo\n",j);
	exit(1);
     } 
    }





//Checkpoint 
/*---------------------------------------------------------
Data allocation de las matrices:
|y| =|G| |a|
-----------------------------------------------------------*/ 

    float n_x=grado+1;
    float n_y=num_lineas;
    int k,l,m,n;
    int pos;
	
    float *a;
    float *G;
    //float *GT;
    //float *y;

    a = malloc(n_x *  sizeof(float));
    G = malloc(n_y * n_x * sizeof(float));

    /*GT = malloc(n_y * n_x * sizeof(float));
     y = malloc(n_y *  sizeof(float));

    for(n=0;n<=n_x;n++){
     	y[n]=d[n];
    }*/

/*---------------------------------------------------------
Creacion de la matriz G como lista:
1,x,x².....x^grado
1,x2,x2²...x2^grado
.
.
.

-----------------------------------------------------------*/
    for (k=0;k<n_y;k++){
      for(l=0;l<n_x;l++){
	float entrada=1.0;
	pos=l+(n_x*k);
	if(l!=0){
	  float numbuh=x[k];
	  for(m=0;m<l;m++){
	    entrada=entrada*numbuh;
	  }
	}
	G[pos]=entrada;
	//GT[pos]=entrada;
	printf("%f  ",G[pos]);
      }
       printf("\n");
    }



//Checkpoint - hay matriz dependiente del grado
/*---------------------------------------------------------
pasarlo todo a matrices en gsl
A=BC
-----------------------------------------------------------*/
    for (k=0;k<n_x;k++){
      a[k]=0.0;
    }
 
/* 	Tengo:
    gsl_matrix *Original;
    gsl_matrix *Ggsl;
    gsl_matrix *GTgsl;
    gsl_matrix *GtimeGTgsl;
    gsl_matrix *inverse;
    gsl_vector *Vgsl;
    gsl_vector *posYgsl;
*/

    Original=gsl_matrix_alloc(n_y,n_x);
	printf("Original..");
    posYgsl=gsl_vector_alloc(n_y);
	printf("posYgsl..");
    inverse=gsl_matrix_alloc(n_x,n_x);
	printf("inverse..");
    GtimeGTgsl=gsl_matrix_alloc(n_x,n_x);
	printf("GtimeGTgsl..");
    Ggsl=gsl_matrix_alloc(n_x,n_y);
	printf("Ggsl..");
    Vgsl=gsl_vector_alloc(n_x);
	printf("Vgsl..");

    GTgsl=gsl_vector_alloc(n_y);
	printf("GTgsl..");	

    printf("Checkpoint 1\n");

    
    pos=0;
    double num,num2;

    for (k=0;k<n_y;k++){
      for(l=0;l<n_x;l++){
	pos=l+(n_x*k);
	num=G[pos];
	gsl_matrix_set (Original,k,l,num);
      }
    }
    printf("...\n");

    for(l=0;l<n_y;l++){
	num2=d[l];
	gsl_vector_set (posYgsl,l,num2);
      }
	/* Compute C = A B */

    gsl_blas_dgemm (CblasTrans, CblasNoTrans,
                  1.0, Original, Original,
                  0.0, GtimeGTgsl);

    printf("Checkpoint 2\n");
/*
	printf("\nOriginal\n");
    gsl_matrix_fprintf (stdout, Original, "%g");
	printf("\nposYgsl\n");
    gsl_vector_fprintf (stdout, posYgsl, "%g");
	printf("\nG times GT gsl\n");
    gsl_matrix_fprintf (stdout, GtimeGTgsl, "%g");
*/
    int s;

    gsl_permutation * perm = gsl_permutation_alloc (n_x);
// Make LU decomposition of matrix m
    gsl_linalg_LU_decomp (GtimeGTgsl, perm, &s);
// Invert the matrix m
    gsl_linalg_LU_invert (GtimeGTgsl, perm, inverse);


    gsl_blas_dgemm (CblasNoTrans, CblasTrans,
                  1.0, inverse, Original,
                  0.0, Ggsl); 
    gsl_blas_dgemv (CblasNoTrans, 
                  1.0, Ggsl, posYgsl,
                  0.0, Vgsl); 
    
        
    //gsl_vector_fprintf (stdout, Vgsl, "%g");
    int lugar=0;
    for(lugar=0;lugar<n_x;lugar++){
      double numero=gsl_vector_get(Vgsl,lugar);
      printf("a_%d --> %g\n",lugar,numero);
    }
    gsl_blas_dgemv (CblasNoTrans, 
                  1.0, Original, Vgsl,
                  0.0, GTgsl); 
    double Sumatoria=0.0;
    int loc;
    double chi;
    for(loc=0;loc<n_y;loc++){
      double dato=(d[loc]-gsl_vector_get(GTgsl,loc))*(d[loc]-gsl_vector_get(GTgsl,loc));
      Sumatoria+=dato;
      chi=Sumatoria/n_y;
    }
    printf("CHI_2 = %g\n",chi);

/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/  
 /* 	Tengo:
    gsl_matrix *Original;
    gsl_matrix *Ggsl;
    gsl_vector *GTgsl;
    gsl_matrix *GtimeGTgsl;
    gsl_matrix *inverse;
    gsl_vector *Vgsl;
    gsl_vector *posYgsl;
*/
    gsl_matrix_free(Original);
    gsl_matrix_free(Ggsl);
    gsl_matrix_free(GtimeGTgsl);
    gsl_matrix_free(inverse);
    gsl_vector_free(GTgsl);
    gsl_vector_free(Vgsl);
    gsl_vector_free(posYgsl);
    fclose(input);
    return 0;
}
