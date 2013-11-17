/*---------------------------------------------------------
codigo que evoluciona un archivo con condiciones iniciales
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const float G=4.86  *pow(10,-6); //Constante gravitacional en Kpc3/(mSolares *kyear2)
const float m=1; //Masa solar
const float h=10;//kyear


float func_prime_1(float x,float y_1,float x_1,float y_2,float *x_m,float *y_m,int *id,int a);
float func_prime_2(float x,float y_1,float x_1,float y_2,float *x_m ,float *y_m,int *id, int a);
float *RungeKutta(float x_old, float y1_old,float x_1, float y2_old,float *x_m,float *y_m,int *id,int a);



//Main

int main(int argc, char **argv){
  system("clear");
  int var, num_lineas,i;
  FILE *input;
  var=0;

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

//--------------------------------------------------------
    input=fopen(argv[1],"r");
    if(!input){
      printf("surgió un problema abriendo el archivo\n");
      exit(1);
    }

    input = fopen(argv[1], "r");
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
llama el archivo producido, convierte y coloca en distintos arrays cada columna
convierte a km y a km/Myrs
-----------------------------------------------------------*/  	
    float *x;
    float *y;
    float *V_x;
    float *V_y;
    int *ID;

    ID=malloc(num_lineas*sizeof(int));
    x= malloc(num_lineas*sizeof(float));
    y= malloc(num_lineas*sizeof(float));
    V_x= malloc(num_lineas*sizeof(float));
    V_y= malloc(num_lineas*sizeof(float));

    
    /*---------------------------------------------------------
Registro de Datos en los arrays
-----------------------------------------------------------*/
    rewind(input);
    int j;
    for(j=0;j<num_lineas;j++){
      fscanf(input, "%d %f %f %f %f\n",&ID[j], &x[j],&y[j],&V_x[j],&V_y[j]);//en kpc, km/s
      
      V_x[j]=V_x[j]*(3.1536*pow(10,10)/(3.0*pow(10,16)));//en kpc/kyr
      V_y[j]=V_y[j]*(3.1536*pow(10,10)/(3.0*pow(10,16)));
      
      // printf("%d %f %f %f %f\n",ID[j],x[j],y[j],V_x[j],V_y[j]);
      /*
      if(!ID[j]|| !x[j]||!y[j]||!V_x[j]||!V_y[j]){

	printf("Existe una linea vacia o hay un problema con la linea %d en el archivo\n",j);
	exit(1);
	} */
    }
    printf("Registro Hecho!\n");
/*---------------------------------------------------------
Usando RUNGEKUTTA:
se aplica a cada particula alrededor de la particula central el cambio de posicion y 
velocidades dado por la interaccion con cada particula central presente por cada cambio de tiempo 
-----------------------------------------------------------*/  
    int part,centros;

    //Conteo de todas las particulas centrales
    centros=0;
    for (j=0;j<num_lineas;j++){
      if( ID[j]==-1){
	centros++;
      }
    }
    printf("# de Centros de Galaxias: %d\n",centros);

    /*-----------------------------------------------------------------------------------------
    Crea una lista de la ubicacion y velocidades de los nuevos centros de masa
      --------------------------------------------------------------------------------------*/
    int *CID;
    float *Cx;
    float *Cy;
    float *CVx;
    float *CVy;
    i=0;

    CID=malloc(centros*sizeof(int));
    Cx=malloc(centros*sizeof(float));
    Cy=malloc(centros*sizeof(float));
    CVx=malloc(centros*sizeof(float));
    CVy=malloc(centros*sizeof(float));

    for (j=-1;j<num_lineas;j++){
      if( ID[j]==-1){
	CID[i]=i;
	Cx[i]=x[j];
	Cy[i]=y[j];
	CVx[i]=V_x[j];
	CVy[i]=V_y[j];
	i++;
	//printf("%d %f %f %f %f\n",CID[i],Cx[i],Cy[i],CV_x[i],CV_y[i]);
      }
    }
    
    /*-----------------------------------------------------------------------------------------
      Crea grupos de archivos de salida
      --------------------------------------------------------------------------------------*/

    int maximo=100000;
    int p;
    FILE *output1, *out;

    for (p=1;p<10;p++){
      
      char filename1[100];
      sprintf(filename1,"Datos%d.dat",p);
  

      out=fopen(filename1,"r");
      if (out){
	fclose(out);
      } 
      else{
	output1=fopen(filename1,"w");
	break;
      
      }
    }
    

   
    float *data;
    data=malloc(num_lineas*sizeof(float));
    int time=0;

    //Avanza en el tiempo
    while(time<200000){
      //printf("%d \n",time);
      //Por cada particula, avanza
      for(part=0;part<num_lineas;part++){
	if (time==100000) {
	  for(part=0;part<num_lineas;part++){
	    float lala1=V_x[part]*(3.0*pow(10,16))/(3.1536*pow(10,11));
	    float lala2=V_y[part]*(3.0*pow(10,16))/(3.1536*pow(10,11));
	    //printf("%d %f %f %f %f\n",part,x[part],y[part],lala1,lala2);
	    fprintf(output1,"%d %f %f %f %f\n",ID[part],x[part],y[part],lala1,lala2);
	  }
	}

	if(ID[part]==-1)
	  {
	    if(centros==1){
	      time+=h;
	      x[part]+=(V_x[part]*h);
	      y[part]+=(V_y[part]*h);
	      
	    }  
	    else{

	      data=RungeKutta(time,x[part],y[part],V_x[part],Cx,Cy,ID,1);
	      time+=h;
	      x[part]=data[1];
	      V_x[part]=data[2];
	      data=RungeKutta(time,y[part],x[part],V_y[part],Cy,Cx,ID,1);
	      y[part]=data[1];
	      V_y[part]=data[2];
	    }
	  }
      
 
	else //(ID[part]>-1)
	  {
	    data=RungeKutta(time,x[part],y[part],V_x[part],Cx,Cy,ID,0);
	    x[part]=data[1];
	    V_x[part]=data[2];
	    data=RungeKutta(time,y[part],x[part],V_y[part],Cy,Cx,ID,0);
	    y[part]=data[1];
	    V_y[part]=data[2];
	    time+=h;
	  }
      }
    }

    
    
    	

/*---------------------------------------------------------
exporta los datos de posicion y velocidades por cada particula en varios archivos que representan una ubicacion en el tiempo
-----------------------------------------------------------*/  

/*---------------------------------------------------------
FIN
-----------------------------------------------------------*/   
  return 0;
}









/*---------------------------------------------------------
FUNCIONES
-----------------------------------------------------------*/  
float func_prime_1(float x,float y_1,float x_1,float y_2,float *x_m,float *y_m,int *id,int a){
  return y_2;
}

float func_prime_2(float x,float y_1,float x_1,float y_2,float *x_m ,float *y_m,int *id, int a){
  float chapa1,chapa2;
  int ajiaco=sizeof(x_m)/sizeof(float);
  if (a != 1){
    
    float deltax,deltay;
    int i;
    
    for(i=0;i<ajiaco;i++){

    deltax=x_m[i]-y_1;
    deltay=y_m[i]-x_1;
    chapa1=pow(deltax,2)+pow(deltay,2);
    chapa2=-(G*m/pow(chapa1,(3/2)))*deltax;
    }
  }
  else{
    int i;

    for(i=0;i<ajiaco;i++){
      if(i==id[i]||id[i]==-1){
	continue;
      }
      float deltax=x_m[i]-y_1;
      float deltay=y_m[i]-x_1;
      chapa1=pow(deltax,2)+pow(deltay,2);
      chapa2=-(G*m/pow(chapa1,(3/2)))*deltax;
      }
  }
  return chapa2;
}

float *RungeKutta(float x_old, float y1_old,float x_1, float y2_old,float *x_m,float *y_m,int *id,int a){
  float k1= func_prime_1(x_old,y1_old,x_1,y2_old, x_m,y_m,id,a);
  float k11= func_prime_2(x_old,y1_old,x_1,y2_old, x_m, y_m,id,a);
  //Primer paso
  
  float x1=x_old + (h/2.0);
  float y1=y1_old + (h/2.0)*k1;
  float y11=y2_old + (h/2.0)*k11;

  float k2= func_prime_1(x1,y1,x_1,y11,x_m, y_m,id,a);
  float k21= func_prime_2(x1,y1,x_1,y11,x_m, y_m,id,a);

  //segundo paso
  
  float x2=x_old + (h/2.0);
  float y2=y1_old + (h/2.0)*k2;
  float y21=y2_old + (h/2.0)*k2;

  float k3= func_prime_1(x2,y2,x_1,y21,x_m, y_m,id,a);
  float k31= func_prime_2(x2,y2,x_1,y21,x_m, y_m,id,a);

  //tercer paso
  
  float x3=x_old + (h);
  float y3=y1_old + (h)*k3;
  float y31=y2_old + (h)*k31;

  float k4= func_prime_1(x3,y3,x_1,y31,x_m, y_m,id,a);
  float k41= func_prime_2(x3,y3,x_1,y31, x_m, y_m,id,a);

  //cuarto paso
  float prom_k1=(1.0/6.0)*(k1 + 2.0*k2+ 2.0*k3 + k4);
  float prom_k2=(1.0/6.0)*(k11 + 2.0*k21+ 2.0*k31 + k41);
  

  //entrega de datos
  float x_new =x_old + h;
  float y1_new=y1_old + h*prom_k1;
  float y2_new=y2_old + h*prom_k2;
  float *mojo = malloc(3*sizeof(float));
  mojo[0]=x_new;
  mojo[1]=y1_new;
  mojo[2]=y2_new;
  return mojo;
}
