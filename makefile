all: Ex1 Ex2
Ex1: Ex1.o gestionFichiers.o
		gcc Ex1.o gestionFichiers.o -o Ex1
Ex2: Ex2.o gestionFichiers.o
		gcc Ex2.o gestionFichiers.o -o Ex2
gestionFichiers.o: gestionFichiers.c gestionFichiers.h
		gcc -c gestionFichiers.c
Ex1.o: Ex1.c gestionFichiers.h
		gcc -c Ex1.c
Ex2.o: Ex2.c gestionFichiers.h
		gcc -c Ex2.c