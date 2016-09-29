#ifndef _AREQUADRA
#define _AREQUADRA

typedef struct vertex *pVertex;
typedef struct edge *pEdge;

struct vertex{

	char *id;
	double x,y;
};

struct edge{
	char *v1,*v2;
	char *cepL, *cepR;
	double distancia;
	double tempo;
	char *rua;	
};

//Cria um vertice
pVertex createVertex(char *id, double x, double y);

//Cria uma aresta
pEdge createEdge(char *v1, char *v2, char *cepL, char *cepR, double dist, double tempo, char *rua);

char direction(pVertex v1, pVertex v2);




#endif