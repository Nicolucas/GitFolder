#########################################################################
###Autores:
###Juliana M. Ayala
###Jorge N. Hayek
###PYTHON!
#########################################################################
import pylab
import numpy
import sys, string, os
from StringIO import StringIO

def plots(Filename,i):
#Importa los archivos producidos por $evolve.c$
    input=numpy.loadtxt(Filename)
    t=input
    c1=t[:,1]
    c2=t[:,2]
#Grafica los datos
    pylab.plot(c1,c2,'k*')
    pylab.xlabel('$Kpc$')
    pylab.ylabel('$Kpc$')
    pylab.title('Grafica posicion de Galaxias')

#Guarda las graficas de los datos bajo el nombre del archivo importado con terminacion
#.png
    alfa='Grafica'+str(i)
    pylab.savefig(alfa)
    pylab.close()
    
for i in range (len(sys.argv)):
    if i != 0:
        name = str(sys.argv[i])
        plots(name, i)
