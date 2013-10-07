#include <stdio.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include<gsl/gsl_blas.h> 
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>
void main (int argc,char **argv){
  // para correr -lm -lgsl -lgslcblas

  FILE *file;
  int columnas=24;
  printf("iniciando programa...\n");
  if(argc<1){
    printf("ingrese un archivo para comenzar\n");
    exit(1);}

  file=fopen(argv[1],"r");
  int i,j,k;
  int filas=0;
  int fg=0;
  printf("corre1?\n");

  do{
    fg=fgetc(file);
    if(fg=='\n'){
      filas++;
    }
  }while(fg!=EOF);
  rewind(file);
  printf("el numero de filas es %d \n", filas);

  //se tiene el numero de columnas y filas del archivo, con la restriccion de qu   e el archivo siempre tendra 24 columnas

  gsl_matrix * vectores=gsl_matrix_alloc(filas,columnas);

  printf("se guardaran los datos en la matriz vectores...\n");

  gsl_matrix_fscanf(file,vectores);

  printf("datos guardados...\n");

  //imprime los datos

  // for(i=0;i<columnas;i++){
  // for(j=0;j<filas;j++){
  //   printf("%lf ",gsl_matrix_get(vectores,j,i));}
  // printf("\n");
  // }


  gsl_matrix *co= gsl_matrix_alloc(filas,filas);

  //gsl_matrix_get(FuncionXi, i, 0))
  // matriz de covarianzas
  
  double *pro;
  pro=malloc(sizeof(double)*columnas);
  

  //promedio de cada fila
  double promedio=0;

  for(i=0;i<filas;i++){
   double total=0;

    for(j=0;j<columnas;j++){

    total=total+gsl_matrix_get(vectores,i,j)/columnas;
    }
    pro[i]=total;
  }

  //se creara la matriz de covarianza
 
  for(i=0;i<filas;i++){
   
    for(j=0;j<filas;j++){
      double suma;
      for(k=0;k<columnas;k++){
	suma=suma+(gsl_matrix_get(vectores,i,k)-pro[i])*(gsl_matrix_get(vectores,j,k)-pro[j])/(columnas-1);
      
      }
      gsl_matrix_set(co,i,j,suma);
      suma=0;
    }
  }


  //se imprime la matriz de covarianza----------------------

  /**  printf("matriz de covarianza \n");
  for(i=0;i<filas;i++){

    for(j=0;j<filas;j++){

      printf("%lf  " ,gsl_matrix_get(co,i,j));
    }
    printf("\n");
    }*/
  
  //  gsl_matrix * vectores=gsl_matrix_alloc(filas,columnas);  printf("se creo la matriz de covarianza\n");

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
  gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (filas);
  printf("funciona w?\n");

  gsl_vector *eval = gsl_vector_alloc (filas);
  printf("funciona eval?\n");

  //problema????????????????????????????????????????
  gsl_matrix *evec = gsl_matrix_alloc (filas,filas);
  printf("funciona evec?\n");
  
  gsl_eigen_symmv (co, eval, evec, w);
       
   
//  gsl_eigen_symmv_sort (eval, evec,GSL_EIGEN_SORT_ABS_DESC);

//Organizar en una matriz los 10 vectores propios correspondientes a los 10 valores propios más grandes
    

//   gsl_matrix_view    ev = gsl_matrix_submatrix (evec,0, 0, filas, 10);
//gsl_matrix *VectoresPropios = &ev.matrix;
    
//Escribir en un archivo los 10 vectores propios y en otro archivo todos los valores propios FALTA DETERMINAR FORMATO PARA VALORES PROPIOS

    FILE *out;
    FILE *out1;
    FILE *out2;
    out = fopen("DanielLozano_eigenVectors.dat","w");

    //se imprimen los vectores propios

    for(i=0;i<filas;i++)
    {
        for(j=0;j<10;j++)
        {
            fprintf(out,"%lf  ",gsl_matrix_get(evec,i,j));
        }
        fprintf(out,"\n");
    }


    out1 = fopen("DanielLozano_eigenValues.dat","w");

    //Se imprimen los valores propios 

    for(i=0;i<filas;i++){
      fprintf(out1,"%lf ",gsl_vector_get (eval, i));
      
    }
    //recosntruccion--------------------------------------------------------------------------matriz vectores escrita con los primeros 10 primeros //vectores propios

 //imprime la descomposicion de todas las señales en el producton punto de los vectores con los vectores propios
    
    out2 = fopen("DanielLozano_pca_chisquare.dat ","w");
    
    gsl_matrix *As=gsl_matrix_alloc(10,columnas);
    gsl_matrix *se=gsl_matrix_alloc(filas,10);
    gsl_matrix *reconstruccion=gsl_matrix_alloc(filas,columnas);

    //se crea el arreglo de las 10 primeras señales
    
    for(i=0;i<10;i++){
      for(j=0;j<filas;j++){
	gsl_matrix_set(se,i,j,gsl_matrix_get(evec,i,j));}
	}
    

    //se crea la matriz de los 10 primeros vectores propios
    
      for(i=0;i<columnas;i++){
	//recorre los vectores propios
     
	
	for(j=0;j<10;j++){
	//recorre las señales inciales
	  double suma=0;
	  fprintf(out2,"evec%d, vect%d:\n ",j,i);

	  //producto punto
	  for(k=0;k<filas;k++){
	    suma=suma+gsl_matrix_get(vectores,k,j)*gsl_matrix_get(evec,k,i);
	  }
	  
	  //guarda los A en la matriz As
	  gsl_matrix_set(As,i,j,suma);
	  fprintf(out2,"%lf  ",suma);

    	  suma=0;
	}
	fprintf(out2,"\n");
      }
      
      //se crea la matriz de recontruccion

      gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, se, As, 0.0, reconstruccion);

      printf("se ha hallado X²\n");

 //calcular X²-----------------------------------------------------
 // gsl_matrix *As=gsl_matrix_alloc(columnas,10);

 //se crea una matriz que tenga la reconstruccion de las señales con los As correspondientes

 printf("hallando los X²...\n");

 //se halla chi para cad par de vectores recontruccion-real

 for(i=0;i<columnas;i++){

   double suma=0;
   fprintf(out2,"x² de vector %d con su recontrusccion:\n",i);
   for(j=0;j<filas;j++){
     
     suma=suma+pow(gsl_matrix_get(vectores,j,i)-gsl_matrix_get(reconstruccion,j,i),2)/(filas);
     
   }
   fprintf(out2,"%lf",suma);
   suma=0;
 }
 




 gsl_vector_free (eval);
 gsl_matrix_free (evec);
    
     




}
