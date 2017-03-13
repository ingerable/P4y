#!/bin/sh

for file in *.pgm; do
	convert ./"$file" ./"${file%.pgm}.png"
done
for fileP in *.png; do
	mv ./"$fileP" ./../imagesCompteRendu
done

