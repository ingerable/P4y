#!/bin/sh

for file in *.png; do
	convert ./"$file" ./"${file%.pgm}.png"
	#mv ./"$file" ../ImagesCompteRendu/
done

