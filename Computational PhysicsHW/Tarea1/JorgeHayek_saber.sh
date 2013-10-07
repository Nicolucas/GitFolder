mkdir Tarea1
cd Tarea1
mkdir ParteA
cd ParteA

wget http://www.finiterank.com/saber/2011.csv
wget https://raw.github.com/forero/ComputationalPhysicsUniandes/master/hands_on/unix/columnas_2011.csv.txt

awk -F "\"*,\"*" '{print $5}' 2011.csv > Lista.txt
echo "Número de Colegios Públicos:"
grep -c SI Lista.txt
echo "Número de Colegios Privados:"
grep -c NO Lista.txt
rm Lista.txt

echo "------------Lista Borrada exitosamente------------"

awk -F "\"*,\"*" '{print $8, $5}' 2011.csv > Lista2.txt
echo "Número de Colegios Privados en calendario A:"
grep -c "A NO" Lista2.txt
echo "Número de Colegios Privados En calendario B:"
grep -c "B NO" Lista2.txt
echo "Número de Colegios Publicos En calendario B:"
grep -c "B SI" Lista2.txt
rm Lista2.txt
echo "------------Lista2 Borrada exitosamente------------"

rm columnas_2011.csv.txt
rm 2011.csv
cd ..
rmdir ParteA
cd ..
rmdir Tarea1
echo "------------Datos borrados exitosamente------------"
echo .
echo .
echo .
echo :D

