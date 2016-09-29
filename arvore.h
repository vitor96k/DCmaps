#ifndef _ARVORE
#define _ARVORE



typedef struct no *pNo;

pNo *criarArvore();
void *getInfo(pNo ele);
int qtdNos(pNo *raiz);
pNo inserir(pNo *raiz, float chave,  float y, float l, float h, void *dado, int tipo);
int altura(pNo *raiz);
void printar(pNo *raiz);
pNo getLeft(pNo a);
pNo getRight(pNo a);
void findCloser(pNo *raiz, double x, double y, double *dist, char *s);
double getX(pNo a);
double getY(pNo a);
double getL(pNo a);
double getH(pNo a);
int getTipo(pNo a);
// Funcoes que deveriam estar no tad arvHash :
void setDeletePath(pNo *raiz, double x, double y, double l, double h, int *qnt);
void changeAllColors(pNo *raiz,char *antigo,char *novo, int *qnt);
void defineArea(pNo *raiz, char *antigo, char *novo, double x, double y, double l, double h, int *qnt);
void gerarSvg(pNo *raiz, char *path, float a, float b, int op);
void mr(pNo *raiz, double x, double y, double l, double h, FILE *f);
void auxSvg(pNo *raiz, FILE *fsvg,float b,int op);
#endif


