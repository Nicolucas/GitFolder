mkdir Tarea1
cd Tarea1
mkdir parteB
cd parteB

wget https://raw.github.com/forero/ComputationalPhysicsUniandes/master/hands_on/unix/random_3D.dat

echo "Numero de 0:"
grep -o 0 random_3D.dat | wc -l

echo "Numero de 1:"
grep -o 1 random_3D.dat | wc -l

echo "Numero de 2:"
grep -o 2 random_3D.dat | wc -l

echo "Numero de 3:"
grep -o 3 random_3D.dat | wc -l

echo "Numero de 4:"
grep -o 4 random_3D.dat | wc -l

echo "Numero de 5:"
grep -o 5 random_3D.dat | wc -l

echo "Numero de 6:"
grep -o 6 random_3D.dat | wc -l

echo "Numero de 7:"
grep -o 7 random_3D.dat | wc -l

echo "Numero de 8:"
grep -o 8 random_3D.dat | wc -l

echo "Numero de 9:"
grep -o 9 random_3D.dat | wc -l

rm random_3D.dat
cd ..
rmdir parteB
cd ..
rmdir Tarea1
echo "------------Datos borrados exitosamente------------"
echo .
echo .
echo .
echo :D
