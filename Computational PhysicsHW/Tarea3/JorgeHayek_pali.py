import sys, codecs,string,os

REM = [' ', ',', '_', '.','(', ')',u'\n','#','"','[',']', '\r', u'\x0c',u'\u011d', u'\u2014', u'\u016d', u'\u0109', u'\u2123']

#Filtrado de lineas
def f_linea(texto):
    caracteres=[]
    inicio=[]
    fin=[]
    for letra in texto:
        caracteres.append(letra)

    #print caracteres
    for letra in REM:
        for chara in caracteres:
            try:
                caracteres.remove(letra)
            except:
                pass
    
    inicio=caracteres
    for a in caracteres:
        fin.insert(0,a)
    print inicio
    print fin
#Checkpoint
    n=0
    verdad= True
    while ((n<len(caracteres)) and verdad):
        if inicio[n]!=fin[n]:
            verdad= False
        n+=1
    return verdad
#Checkpoint^            
    
    

#Entrada
n_args=len(sys.argv)
if n_args>2:
    print "Existe mas de un argumento"
    sys.exit()
if n_args<2:
    print "Se necesita un argumento"
    sys.exit()

archivo =codecs.open(sys.argv[1],"r",u"utf8")
archivo_r= archivo.read()
num_caracteres=len(archivo_r)

#CHECKPOINT
#filtra, lentamente...... meh

l_archivo=archivo_r.lower()
archivos_1=l_archivo.replace(u'\xe1','a')
archivos_2=archivos_1.replace(u'\xe9','e')
archivos_3=archivos_2.replace(u'\xed','i')
archivos_4=archivos_3.replace(u'\xf3','o')
archi=archivos_4.replace(u'\xfa','u')
#Checkpoint


frases=[]
frases=archi.split(u'\n')

#filtrado por lineas
#print num
for linea in frases:
    rta=f_linea(linea)
    if linea=="":
        rta=""
    print rta

