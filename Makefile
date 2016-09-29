arquivo1: main.o grafo.o matriz.o areQuadra.o retangulo.o arvore.o hash.o arvHash.o bd.o
	gcc -o dcmaps main.o grafo.o matriz.o areQuadra.o retangulo.o arvore.o hash.o arvHash.o bd.o -lm

arquivo2: areQuadra.c areQuadra.h
	gcc -c areQuadra.c
	
arquivo3: matriz.c matriz.h
	gcc -c matriz.c

arquivo4: grafo.c grafo.h
	gcc -c grafo.c

arquivo5: arvHash.c arvHash.h
	gcc -c arvHash.c

arquivo6: hash.c hash.h
	gcc -c hash.c

arquivo7: retangulo.c retangulo.h
	gcc -c retangulo.c -lm

arquivo8: arvore.c arvore.h
	gcc -c arvore.c

arquivo9: bd.c bd.h
	gcc -c bd.c

arquivo10: main.c
	gcc -c main.c