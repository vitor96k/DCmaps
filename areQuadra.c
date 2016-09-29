#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "areQuadra.h"


pVertex createVertex(char *id, double x, double y){

	pVertex novo = (pVertex)malloc(sizeof(struct vertex));
	novo->id = (char *)malloc((strlen(id)+1)*sizeof(char));
	strcpy(novo->id,id);
	novo->x = x;
	novo->y=y;

	return novo;
}

pEdge createEdge(char *v1, char *v2, char *cepL, char *cepR, double dist, double tempo, char *rua){

	pEdge novo = (pEdge)malloc(sizeof(struct edge));

	novo->v1 = (char *)malloc((strlen(v1)+1)*sizeof(char));
	strcpy(novo->v1,v1);

	novo->v2 = (char *)malloc((strlen(v2)+1)*sizeof(char));
	strcpy(novo->v2,v2);

	novo->cepL = (char *)malloc((strlen(cepL)+1)*sizeof(char));
	strcpy(novo->cepL,cepL);

	novo->cepR = (char *)malloc((strlen(cepR)+1)*sizeof(char));
	strcpy(novo->cepR,cepR);

	novo->rua = (char *)malloc((strlen(rua)+1)*sizeof(char));
	strcpy(novo->rua,rua);

	novo->distancia = dist;
	novo->tempo = tempo;

	return novo;
}

char direction(pVertex v1, pVertex v2){

	if(v1->x == v2->x){

		if(v1->y < v2->y) return 'N';
		else if(v1->y > v2->y) return 'S';

	}else if(v1->y == v2->y){

		if(v1->x < v2->x) return 'L';
		else if(v1->x > v2->x) return 'O'; 
	}



}

