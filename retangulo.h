#ifndef _RETANGULO
#define _RETANGULO

// 0 - Retangulo
// 1 - Quadra
// 2 - Semafaro
// 3 - Hidrante
// 4 - Torre
// 5 - VERTICE

struct casa{

	char face;
	char *num; 
	char *nome;
	char *fone;
	struct casa *prox;
};

struct comercio{
	char face;
	char *num;
	char *tipo;
	char *razao;
	char *telefone;
	struct comercio *prox;
};

struct retangulo{

	float x,y,l,h;
	char *cor;
};

struct quadra{

	float x,y,l,h;
	char *cep;

	struct casa *moradores;
	struct comercio *comercial;
};

struct aux{
	char *id;
	float x,y;
};

typedef struct casa casa;
typedef struct casa *pCasa;

typedef struct comercio comercio;
typedef struct comercio *pComercio;

typedef struct retangulo retangulo; 
typedef struct retangulo *pRetangulo; 

typedef struct quadra quadra;
typedef struct quadra *pQuadra;

typedef struct aux aux;
typedef struct aux *pAux;

pCasa criarCasa(char face,char *num, char *nome,char *fone);
pComercio criarComercio(char face, char *num, char *tipo, char *razao, char *telefone);
pRetangulo criarRetangulo(float x,float y,float l,float h, char *cor);
pQuadra criarQuadra(float x,float y,float l,float h, char *cep);
pAux criarAux(char *id, float x,float y);
void mq(pQuadra q, FILE *f);
void EstabDaQuadra(pQuadra q, char *est, int *k, FILE *f);
void ligarCasa(pQuadra q, pCasa c);
void ligarComercio(pQuadra q, pComercio c);  
void EstabDaQuadra2(pQuadra q, char *est, int *k, double x, double y, double l, double h,FILE *f);
void printAllComercio(pQuadra q);
void EstabDaQuadraAll(pQuadra q, char *est, int *k,FILE *f);
void EstabDaQuadraAll2(pQuadra q, char *est, int *k, double x, double y, double l, double h,FILE *f);
void printHidrantes(pAux a, FILE *f);
int torreInside(pQuadra q, pAux torre);
char getFaceMorador(pQuadra q, char *fone);
char getFaceMoradorNome(pQuadra q, char *n);
void setPoint(pQuadra q, char f, double *x, double *y);
double distancia(double x1,double y1,double x2,double y2);
char getFaceEstab(pQuadra q, char *tipo);
void limites(pQuadra esquerda, pQuadra direita,double *x1,double *x2,double *y1,double *y2);
pComercio getEstabelecimento(pQuadra q, char *tipo);
#endif
