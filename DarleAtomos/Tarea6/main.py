import pylab
import numpy

PI= 3

# Definimos constantes


def normalize(v):

    return (lambda norm: [x/norm for x in v])(sum(x**2 for x in v) **0.5)

# Aqui tomaremos que psi = y1 y que  psi' = y2, luego definimos las derivadas de y1 y y2

def y1_prime(y2):

    return y2

def y2_prime(u,y1,y2,E,l):

    return -(2.0/u)*y2 -(E +(2.0/u)-l*(l+1)/u**2.0)*y1

def prob(u,r):
    uno=0.0
    uno = PI*(4*r*r*u*u)
    norm = numpy.trapz(prob(u,r),u)
    dos=uno/norm
    print dos
	

# Definimos el intervalo [a,b] donde queremos resolver nuestra ecuacion diferencial y definimos el paso h que vamos a tomar

a = 0.0
b = 20.0
h = 0.0001

n_points = int((b-a)/h)
u = [a+i*h for i in range(1,n_points+1)]

for n in range(1,5):
     E =-1.0/float(n**2)
     L = [l*(l+1) for l in range(n)]
     for l in range(len(L)):
          print 'solving for: n = '+str(n)+', l = '+str(l)
          y1 = []
          y2 = []
	  y3 = []
          if l == 0 :
               y1.append(1.0)
               y2.append(1.0)
          if l > 0 :
               y1.append(1.0)
               y2.append(0.0)

          for i in range(1,n_points):

               a2 = y1_prime(y2[i-1])

               a1 = y2_prime(u[i-1],y1[i-1],y2[i-1],E,L[l])
	       

               y1.append(h*a1+y1[i-1])
               y2.append(h*a2+y2[i-1]) 
	       a3 = prob(u[i-1],y1)
	       y3.append(a3)
          
          pylab.plot(u , y3, 'k')
          pylab.xlim([0,b])
          pylab.xlabel('$u$')
          pylab.ylabel('$Probabilidad$')
          pylab.title('n = '+str(n)+', l = '+str(l))
          pylab.savefig(str(n)+','+str(l)+'.png')
          pylab.close()
