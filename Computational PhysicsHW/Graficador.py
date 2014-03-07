import pylab
import numpy


data = numpy.loadtxt("Tabla_datos")
y = data[:,1]
x = data[:,2]



pylab.plot(x, y, '.')
pylab.xlabel('x')
pylab.ylabel('y')
pylab.title(' x-y')
pylab.savefig('Grafica')
pylab.close()
	

	
print x
	
print "La grafica fue generada y guardada"
