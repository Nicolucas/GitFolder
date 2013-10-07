import math
import matplotlib.pyplot as pyp
import pylab as pyl

#Definir Valores



E = 7
B = 135
W=1.0

MAX = 3.0

#LIM = 2.0
#LIMN = 0.0

def V(k):
    var=W*(k*k)
    return var

#Define el valor de la funcion en cada intervalo
def darF(n,phi):

    x=n
    Rta=0.0
#    if (x<LIM or x>LIMN):
#        Rta= -B*E*phi
#    if (x==LIM or x==LIMN):
#        Rta= -B*(E-V(x)*0.5)*phi
#    if (x>LIM or x<LIMN):

    Rta= -B*(E-V(x))*phi
    return Rta

#valores de la funcion segun derivadas y valores de los cambios de la variable
psi_r=0.0
dpsi=1.0
u_r=0.0
du=0.01


#el main
u=u_r
psi=psi_r
dp=dpsi
F=darF(u,psi)
dp=dp+0.5*F*du
psi=psi + dp*du

listu=[]
listpsi=[]

#El desgraciado Euler
nova=0
while u < MAX:
    u = u + du
    dp = dp + F*du
    psi = psi + dp*du

    F=darF(u, psi)
    
    listu.append(u)
    listpsi.append(psi)


#calcular?
pyp.scatter(listu,listpsi)
pyp.ylabel("psi")
pyp.xlabel("x")
pyp.title("Valores: "+ "E = "+str (E))
pyp.show()
