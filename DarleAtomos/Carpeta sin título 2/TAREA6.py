from pylab import ∗
from scipy.integrate import odeint
from scipy.optimize import brentq
import sys
b=2.0
Vo=20.0
steps=100
E=0.0

def V(x):
    if (x<1.0):
        return 0
    else:
        return Vo

def SE(y,x):
    go=y[1]
    g1=2.0*(V(x)-E)*y[0]
    return array([go,g1])

def Final_Value(energy):
    global y
    global E
    E = energy
    y =odeint(SE,yo,x)
    return y[−1,0]


def y1_prime(y2):

    return y2

def y2_prime(u,y1,y2,E,l):

     return -(2.0/u)*y2 -(2.0*E +(2.0/u)-l*(l+1)/u**2.0)*y1

# Definimos el intervalo [a,b] donde queremos resolver nuestra ecuacion diferencial y definimos el paso h que vamos a tomar

a = 0.0
b = 10.0
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
          if l == 0 :
               y1.append(1.0)
               y2.append(1.0)
          if l > 0 :
               y1.append(1.0)
               y2.append(1.0)

          for i in range(1,n_points):

               a1 = y1_prime(y2[i-1])
               a2 = y2_prime(u[i-1],y1[i-1],y2[i-1],E,L[l])

               y1.append(h*a1+y1[i-1])
               y2.append(h*a2+y2[i-1]) 
          
          pylab.plot(u , y1, 'k')
          pylab.xlim([0,b])
          pylab.xlabel('$u$')
          pylab.ylabel('$\psi$')
          pylab.title('n= '+str(n)+' l= '+str(l))
          pylab.savefig(str(n)+','+str(l)+'.png')
          pylab.close()
