#ifndef _GRAFO
#define _GRAFO

//Auxiliar no Percurso;
struct pilha{
	unsigned long int indice;
	struct pilha *prox;
};

typedef struct pilha pilha;

typedef struct grafo Grafo;
typedef struct grafo *pGrafo;
typedef struct aresta Aresta;
typedef struct aresta *pAresta;
typedef unsigned long int inteiro;


//Cria o grafo (Matriz v*v)
pGrafo criarGrafo(inteiro v);

//Insere uma aresta ligando os vertices "saida" e "entrada" e atribui o peso dessa aresta
void ligarNos(pGrafo g, inteiro saida, inteiro entrada, double peso, double peso2);

//Verifica se dois vertices possuem arestas;
int temLigacao(pGrafo g, inteiro saida, inteiro entrada);

//Insere o conteúdo do vertice (significado do vértice)
void setValueVertice(pGrafo g, inteiro vertice, void *dado);

//Retorna o conteúdo do vertice (significado do vértice)
void *getValueVertice(pGrafo g, inteiro vertice);

//Insere o conteúdo da aresta (significado da aresta)
void setValueAresta(pGrafo g, inteiro saida, inteiro entrada, void *dado);

//IRetorna o conteúdo da aresta (significado da aresta)
void *getValueAresta(pGrafo g, inteiro saida, inteiro entrada);

//Acha o percurso com menor gasto, caminho mais curto
void menorCusto(pGrafo g, inteiro saida, inteiro entrada, inteiro *vetor);

//Retorna a posicao que o vertice esta a partir de uma string
unsigned long int pegarPosicao(pGrafo g, char *s1);

//Dado um vertice u, retorna o seu ID
char *getId(pGrafo g, inteiro u);

pilha *dijkstra (pGrafo gr, int src, int destino, int w);


#endif

