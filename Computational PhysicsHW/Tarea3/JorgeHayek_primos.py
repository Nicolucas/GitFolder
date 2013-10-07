import sys

#Argumentos
n_args=len(sys.argv)
if n_args>2:
    print "Existe mas de un argumento"
    sys.exit()
if n_args<2:
    print "Se necesita un argumento"
    sys.exit()

#Condiciones sobre el numero
num=int(sys.argv[1])

print num
lim_sup=10000000

if num < 0:
    print "el numero debe ser mayor a 0"
    sys.exit
if num > lim_sup:
    print "el numero debe ser menor que 10E6"
    sys.exit()

#Checkpoint
parla1="El numero tiene mas de dos factores, luego no es posible descomponerlo en solo dos factores primos. Al menos los tres primeros factores primos encontrados son:"

parla2="El numero es primo, no es posible descomponerlo en dos factores primos."

parla3="La descomposicion entre dos numeros primos es posible, los numeros primos son:"
#Checkpoint

result=0
i=2
factor=[]
valor=0
while ((num>1) and (len(factor)<3) and (i<(num+1))):
    result=num%i
    if(result==0):
        factor.append(i)
        num=num/i
    else:
        i+=1
if len(factor)>2:
    print(parla1+"\n"+str(factor[0])+" "+str(factor[1])+" "+str(factor[2]))
    sys.exit()
if len(factor)<2:
    print parla2
    sys.exit()
#print (len(factor))
print (parla3+"\n"+str(factor[0])+" "+str(factor[1]))
