#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define H 0.05;

float fy_prime_1(float x,float y_1,float y_2);
float fy_prime_2(float x,float y_1,float y_2);



int main(int argc, char **argv)
{
  int n_point;
  float d_ini,d2_ini;
  int i;
/*---------------------------------------------------------
separa los datos de entrada y reviza si esta el numero de datos necesario
-----------------------------------------------------------*/
printf("Este programa se ejecutó con %d argumento(s):\n",argc-1);

for(i=1;i<argc;i++){
printf("%s\n", argv[i]);
}
if(argc!=4){
printf("se necesitan 3 argumentos además del nombre del ejecutable!\n EXIT!\n");
exit(1);
}

float num=argv[1];
float d_ini=atof(argv[2]);
float d2_ini=atof(argv[3]);
 
//Revizar
 int n_points=atoi((num+h)/h)
/*---------------------------------------------------------
separa los arrays
-----------------------------------------------------------*/
float *x;
float *y_1;
float *y_2;

x = malloc(n_point * sizeof(float));
y_1 = malloc(n_point * sizeof(float));
y_2 = malloc(n_point * sizeof(float));
/*---------------------------------------------------------
Coloca los valores iniciales
Recordar: n_points es el numero de datos
-----------------------------------------------------------*/
 y_1[0]=d_ini;
 y_2[0]=d2_ini;

/*---------------------------------------------------------
rungekuta 4to orden
-----------------------------------------------------------*/ 
  for(i=1;i<n_points;i++){

    float k1_1 = fy_prime_1(x[i-1],y_1[i-1],y_2[i-1]);
    
//first step
    float x1 = x[i-1] + (h/2.0);
    float y1_1 = y_1[i-1] + (h/2.0) * k1_1;
    float k2_1 = func_prime(x1, y1_1);
    float y1_2 = y_2[i-1] + (h/2.0) * k1_2;
    float k2_2 = func_prime(x1, y1_2);
    
      //second step
    float x2 = x[i-1] + (h/2.0);
    float y2_1 = y_1[i-1] + (h/2.0) * k2_1;
    float k3 = func_prime(x2, y2_1);
        
      //third step
    x3 = x[i-1] + h
    y3 = y_1[i-1] + h * k3
    k4 = func_prime(x3, y3)
    
      //fourth step
    average_k = (1.0/6.0)*(k1 + 2.0*k2 + 2.0*k3 + k4)
    
    x[i] = x[i-1] + h
    y[i] = y[i-1] + h * average_k
/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/   
    return 0;
}


/*---------------------------------------------------------
Funciones
-----------------------------------------------------------*/
float fy_prime_1(float x,float y_1,float y_2){
  return y_2;
}
float fy_prime_2(float x,float y_1,float y_2){
  float data=-4*(sin(y_1));
    return data;
}
