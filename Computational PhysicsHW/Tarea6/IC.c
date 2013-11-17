#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float const PI= 3.14159265;
const float G= 1.320153125 * pow(10,38); //Constante gravitacional en Km³/(mSolares * Myear²)
float magn_v(float m,float g, float r);

//-------------Main---------------
int main(int argc, char **argv){
  system("clear");


  if(argc!=5){
    printf("Se requieren 4 datos para introducir para el centro de masa; \n-posicion inicial en eje x\n-posicion inicial en eje y\n-velocidad inicial en el eje x\n-velocidad inicial en el eje y");
    exit(1);
  }
  //Entrada en kpc y km/s, pasarlo a km y a km/MYrs
  float xo=atof(argv[1])*(3.0*pow(10.0,16.0));
  float yo=atof(argv[2])*(3.0*pow(10.0,16.0));
  float V_xo=atof(argv[3])*(3.1536*pow(10,13));
  float V_yo=atof(argv[4])*(3.1536*pow(10,13));

  printf("Los datos introducidos fueron: \nX: %f\nY: %f\nV_X %f\nV_Y%f\n",xo,yo,V_xo,V_yo);
 
/*------------------------------------------------------------------------
Checkpoint; Los datos de posicion y velocidades fueron introducidos
--------------------------------------------------------------------------*/
/*------------------------------------------------------------------------
Variables
Numero de estrellas
Output
distancia de las orbitas
Masa
--------------------------------------------------------------------------*/
  int num_particles=120;
  FILE *output;
  float dist_orbi=10.0*3.0*pow(10.0,16.0); //en km
  float masa=pow(10.0,12.0); //masas solares
  char filename[100]="IC_output.dat";
  output=fopen(filename,"a");
/*---------------------------------------------------------
llama el archivo producido, convierte y coloca en distintos arrays cada columna
convierte a km y a km/Myrs
-----------------------------------------------------------*/  	
    float *x_axis;
    float *y_axis;
    float *Vx_axis;
    float *Vy_axis;

    x_axis= malloc(num_particles*sizeof(float));
    y_axis= malloc(num_particles*sizeof(float));
    Vx_axis= malloc(num_particles*sizeof(float));
    Vy_axis= malloc(num_particles*sizeof(float));

/*---------------------------------------------------------
se tiene la magnitud de la velocidad dependiente de radio, masa y la constante G
-----------------------------------------------------------*/

/*---------------------------------------------------------
se les da un valor espacial a las particulas en cada orbita
primera: 12
segunda: 18
tercera: 24
cuarta: 30
quinta: 36

es decir se divide 2PI entre el numero de particulas en cada orbita, teniendo el angulo, se le da una ubicacion en coordenadas cartesianas considerando el radio y se les suma la posicion de la masa central
-----------------------------------------------------------*/
  int (par_1)=12;
  int (par_2)=18;
  int (par_3)=24;
  int (par_4)=30;
  int (par_5)=36;

  float firstorb=2*PI/(par_1);
  float secondorb=2*PI/(par_2);
  float thirdorb=2*PI/(par_3);
  float fourthorb=2*PI/(par_4);
  float fifthorb=2*PI/(par_5);

  int alpha=0;
  int i=0;
  int k=0;

  //radio =10 kpc
  float radio1=10.0*3.0*pow(10.0,16.0);//en km

  for (i=0;i<par_1;i++){
    x_axis[i]=radio1*(cosf(firstorb*i))+xo;
    y_axis[i]=radio1*(sinf(firstorb*i))+yo;
  }
  k+=par_1;

  //radio =20 kpc
  float radio2 =20.0*3.0*pow(10.0,16.0);//km

  for (i=0;i<par_2;i++){
    x_axis[i+k]=radio2*cosf(secondorb*i)+xo;
    y_axis[i+k]=radio2*sinf(secondorb*i)+yo;
  }
  k+=par_2;

  //radio =30 kpc
  float radio3 =30.0*3.0*pow(10.0,16.0);//km

  for (i=0;i<par_3;i++){
    x_axis[i+k]=radio3*cosf(thirdorb*i)+xo;
    y_axis[i+k]=radio3*sinf(thirdorb*i)+yo;
  }
  k+=par_3;

  //radio =40 kpc
  float radio4 =40.0*3.0*pow(10.0,16.0);//km

  for (i=0;i<par_4;i++){
    x_axis[i+k]=radio4*cosf(fourthorb*i)+xo;
    y_axis[i+k]=radio4*sinf(fourthorb*i)+yo;
  }
  k+=par_4;

  //radio =50 kpc
  float radio5 =50.0*3.0*pow(10.0,16.0);//km

  for (i=0;i<par_5;i++){
    x_axis[i+k]=radio5*cosf(fifthorb*i)+xo;
    y_axis[i+k]=radio5*sinf(fifthorb*i)+yo;
  }



/*---------------------------------------------------------
luego se calcula la magnitud de la velocidad de cada particula y se separa la componente vertical de la horizontal y se guarda en los array de velocidades, luego se suma la velocidad de la particula central
-----------------------------------------------------------*/
  float V_orb_1;
  V_orb_1= magn_v(masa, G, radio1);
  float V_orb_2;
  V_orb_2= magn_v(masa, G, radio2);
  float V_orb_3;
  V_orb_3= magn_v(masa, G, radio3);
  float V_orb_4;
  V_orb_4= magn_v(masa, G, radio4);
  float V_orb_5;
  V_orb_5= magn_v(masa, G, radio5);
  k=0;
  for (i=0;i<par_1;i++){
    Vx_axis[i]=V_orb_1*cos((firstorb*i)-(PI/2))+V_xo;
    Vy_axis[i]=V_orb_1*sin((firstorb*i)-(PI/2))+V_yo;
  }
  k+=par_1;

 for (i=0;i<par_2;i++){
   Vx_axis[i+k]=V_orb_2*cos((secondorb*i)-PI/2)+V_xo;
   Vy_axis[i+k]=V_orb_2*sin((secondorb*i)-PI/2)+V_yo;
  }
  k+=par_2;

 for (i=0;i<par_3;i++){
   Vx_axis[i+k]=V_orb_3*cos((thirdorb*i)-PI/2)+V_xo;
   Vy_axis[i+k]=V_orb_3*sin((thirdorb*i)-PI/2)+V_yo;
  }
  k+=par_3;

 for (i=0;i<par_4;i++){
    Vx_axis[i+k]=V_orb_4*cos(fourthorb*i-PI/2)+V_xo;
    Vy_axis[i+k]=V_orb_4*sin(fourthorb*i-PI/2)+V_yo;
  }
  k+=par_4;


 for (i=0;i<par_5;i++){
    Vx_axis[i+k]=V_orb_5*cos(fifthorb*i-PI/2)+V_xo;
    Vy_axis[i+k]=V_orb_5*sin(fifthorb*i-PI/2)+V_yo;
  }
/*---------------------------------------------------------
se guarda la primera fila de datos introducidos en posicion -1 y se guarda tambien los arrays en orden de posiciones y velocidades de 0 hasta el numero de particulas
-----------------------------------------------------------*/
 fprintf(output,"-1 %f %f %f %f\n",xo/(3.0*pow(10.0,16.0)),yo/(3.0*pow(10.0,16.0)),V_xo/(3.1536*pow(10,13)),V_yo/(3.1536*pow(10,13)));
 float data1,data2,data3,data4;
 for(i=0;i<num_particles;i++){

   data1=x_axis[i]/(3.0*pow(10.0,16.0));
   data2=y_axis[i]/(3.0*pow(10.0,16.0));
   data3=Vx_axis[i]/(3.1536*pow(10,13));
   data4=Vy_axis[i]/(3.1536*pow(10,13));

   fprintf(output,"%d %f %f %f %f\n",i,data1,data2,data3,data4);
 }

/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/
 fclose(output);
 return 0;
}



/*---------------------------------------------------------
Funciones
-----------------------------------------------------------*/
//entran valores de masa, constante gravitacional y radio, devuelve la magnitud de la velocidad.
//Se requiere salida en terminos de km/s
float magn_v(float m,float g, float r){
  float dato=m*g/r;
  float dato2=sqrt(dato);
  return dato2;
}
