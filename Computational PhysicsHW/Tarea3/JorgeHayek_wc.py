import glob, sys
lista_arc=[]
lista_arc=glob.glob('*')

for dunite in lista_arc:
    try:
        websterite=open(dunite,'r')
        lherzelite=websterite.read()
        harzburguite=lherzelite.splitlines()
        num=len(harzburguite)
        print dunite+" --->  "+str(num)
    except:
        print "["+ dunite+"]"+" no puede ser leido"

   
