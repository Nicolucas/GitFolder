import numpy, pylab


def R10 (u):

    return 2.0 * numpy.exp(-u)

def R20 (u):

    return 2.0*(0.5**1.5)*(1-(u/2.0))*numpy.exp(-u/2.0)

def R21 (u):

    return (1.0/numpy.sqrt(3))*(0.5**1.5)*u*numpy.exp(-u/2.0)

def R30 (u):

    return 2.0*(3.0**(-1.5))*(1-(2.0*u/3.0)+((2.0/27.0)*u**2.0))*numpy.exp(-u/3.0)

def R31 (u):

    return (4.0*numpy.sqrt(2.0)/3.0)*(3.0**(-1.5))*u*(1-u/6.0)*numpy.exp(-u/3.0)

def R32 (u):

    return (2.0*numpy.sqrt(2.0)/(27.0*numpy.sqrt(5.0)))*(3.0**(-1.5))*(u**2.0)*numpy.exp(-u/3.0)

def prob(u,wave):
    return 4.0*numpy.pi*(u**2.0)*(wave(u)**2.0)


def getmax(vect):
    
    answer=[]
    for i in range(1,len(vect)-1):
        if (vect[i] > vect[i-1] and vect[i] > vect[i+1] and vect[i] > 0.0001):
            answer.append(i)
    return answer

f = R32
u = numpy.arange(0,5000,0.1)
norm = numpy.trapz(prob(u,f),u)
expect = numpy.trapz(prob(u,f)*u,u)/norm
maximum = numpy.argmax(prob(u,f) == numpy.amax(prob(u,f)))
"""
print 'Expected value in '+str(expect)
print 'Global Maximum in ' +str(u[maximum])
"""
"""
pylab.plot(u,prob(u,f)/(norm**2),'k')
"""
pylab.scatter(u,prob(u,f)/(norm**2))

"""pylab.plot(u[getmax(prob(u,f))[0]],prob(u[getmax(prob(u,f))[0]],f) /(norm**2),'.r',label='Maximum')
"""

for i in getmax(prob(u,f)):
    print 'Local Maximum in ' +str(u[i])
    """
    pylab.plot(u[i],prob(u[i],f) /(norm**2),'.r')
    """
    """
    pylab.plot(expect,(prob(expect,f)/(norm**2)),'.b',label='Expected Value')
    """
n=0
if f==R30 or f==R31 or f==R32:
    n=3
if f==R20 or f==R21:
    n=2
if f==R10:
    n=1
l=0
if f==R30 or f==R20 or f==R10:
    l=0
if f==R31 or f==R21:
    l=1
if f==R32:
    l=2


pylab.title('n:'+str(n)+', $l$: ' +str(l)+ " Maximo: "+ str(u[maximum])+ " ValorMasProb: "+ str(expect) )
pylab.xlim([0,25])
pylab.ylim([0,1.2*prob(u[maximum],f)/(norm**2)])
pylab.xlabel('$u$')
pylab.ylabel('$Probabilidad$')
"""
pylab.legend(loc=4, borderaxespad=0.5)
"""
pylab.show()
