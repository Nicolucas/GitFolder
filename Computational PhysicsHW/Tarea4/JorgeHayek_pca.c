#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_eigen.h>


//Main------------------------------------------------------------------

int main(int argc, char **argv)
{
  gsl_matrix *Original;
  gsl_matrix *Mtr_Cov;


  FILE *input;
  int num_lineas;
  int i,j,k;
  double var;

/*---------------------------------------------------------
Verifica cuales archivos fueron usados como input y se asegura de que solo haya cargado uno.
-----------------------------------------------------------*/
  printf("Este programa se ejecutó con %d argumento(s):\n",argc-1);
  for(i=1;i<argc;i++){
    printf("%s\n", argv[i]);
  }
  if(argc!=2){
    printf("se necesita 1 argumento además del nombre del ejecutable!,\n  EXIT!\n");
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

    //printf("Número de lineas del archivo:\n -->%d\n",num_lineas); 

/*---------------------------------------------------------
Data allocation
-----------------------------------------------------------*/ 
    rewind(input);
    Original=gsl_matrix_alloc((num_lineas),24);
    // printf("\nOriginal\n");
    gsl_matrix_fscanf(input,Original);
    //gsl_matrix_fprintf (stdout, Original, "%g");
    //CheckPoint
    //printf("matriz escaneada\n");
/*---------------------------------------------------------
Promedio
-----------------------------------------------------------*/ 
    float *prom;
    int y;
    
    prom=malloc((num_lineas) * sizeof(float));
    //printf("...\n");
    for(k=0;k<num_lineas;k++){
      float suma=0.0;
      for(y=0;y<24;y++){
	suma+=gsl_matrix_get(Original,k,y);
      }
      prom[k]=suma/24.0;
    }
    printf("Checkpoint... Promedios\n");

/*---------------------------------------------------------
Efectos en la matriz
-----------------------------------------------------------*/ 
    Mtr_Cov=gsl_matrix_alloc(num_lineas,num_lineas);
    //printf("...\n");
    int l,n,m;
    double sprite=0;
    for(l=0;l<num_lineas;l++){
      for(m=0;m<num_lineas;m++){
	for(n=1;n<24;n++){
	  double flan=gsl_matrix_get(Original,m,n);
	  double agua=prom[m];
	  double frutino=gsl_matrix_get(Original,l,n);
	  double tang=prom[l];
	  double jarra1=(flan-agua);
	  double jarra2=(frutino-tang);
	  //printf("%g  %g\n",jarra1,jarra2);
	  sprite=sprite+(jarra1*jarra2)/24;
	}
	
	gsl_matrix_set(Mtr_Cov,m,l,sprite);
	sprite=0;
      }}
    
/*---------------------------------------------------------
Matriz de covarianza creada;
sacar vectores y valores propios de la matriz.
-----------------------------------------------------------*/
/*
    int pa,po;
    double can;
    for(pa=0;pa<num_lineas;pa++){
      for(po=0;po<num_lineas;po++){
	can=gsl_matrix_get(Mtr_Cov,po,pa);
	printf("%f ",can);
      }
      printf("\n");
    }
*/




    gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (num_lineas);
    gsl_vector *eval = gsl_vector_alloc (num_lineas);
    gsl_matrix *evec = gsl_matrix_alloc (num_lineas,num_lineas);
  
    gsl_eigen_symmv (Mtr_Cov, eval, evec, w);   
    gsl_eigen_symmv_sort (eval, evec,GSL_EIGEN_SORT_ABS_ASC);
/*---------------------------------------------------------
PON ESA COSA HORROROSA AHI O VERAS!!!
-----------------------------------------------------------*/
    FILE *Out1;
    FILE *Out2;
    
    Out1 = fopen("JorgeHayek_eigenvalues.dat", "w");
    Out2 = fopen("JorgeHayek_eigenvectors.dat", "w");
    
    fprintf(Out1,"EigenValues:\n");
    fprintf(Out2,"EigenVectors:\n");



    for (i = 0; i < num_lineas; i++)
      {
	double eval_i  = gsl_vector_get (eval, i);

	fprintf (Out1,"%g\n", eval_i);
      }

     for (i = 0; i < 11; i++)
      {fprintf(Out2,"--------------------------------------------\nVector %d\n--------------------------------------------\n",i);
	gsl_vector_view evec_i 
	  = gsl_matrix_column (evec, i);

	gsl_vector_fprintf (Out2, 
			    &evec_i.vector, "%g");
	 
      }
     
  





/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/  
    gsl_vector_free (eval);
    gsl_matrix_free (evec);
    gsl_matrix_free(Original);
    fclose(input);
    return 0;
}
