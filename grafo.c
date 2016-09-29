#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "matriz.h"
#include "areQuadra.h"
#include "hash.h"
#include "retangulo.h"
#include "arvore.h"

struct aresta{

	int conectado;		
	double peso;
	double peso2;
	char direcao;
	void *arestaSignificado;
	// ESSE VOID POINTER ()
};

struct grafo{

	inteiro qntVert;
	pAresta *are;						//Ponteiro Duplo para Aresta => Matriz de Arestas
	 void **verticeSignificado;				//Vetor de void pointers apontando para o significado de cada aresta
	// ESSE VOID POINTER APONTA PARA UMA STRUCT (id,, x, y);	
};

char *getId(pGrafo g, inteiro u){
	pVertex atual = (pVertex) g->verticeSignificado[u];
	return atual->id;
}


pGrafo criarGrafo(inteiro v){

	inteiro i,j;

	pGrafo novo = (pGrafo)malloc(sizeof(Grafo));						//Grafo Criado
	novo->qntVert = v;										//Possui v vértices

	novo->are = (pAresta *)malloc((v+1)*sizeof(pAresta)); 				//Aloca n ponteiros para Aresta

	novo->verticeSignificado = (void **)malloc((v+1)*sizeof(void*));		//Aloca n ponteiros void para o Significado do Vertice

	for(i=0;i<v;i++){
		//printf("\nAlocando aresta");
		novo->are[i] = (pAresta)malloc((v+1)*sizeof(Aresta));			//Aloca realmente a struct Aresta	
	}

	for(i=0;i<v;i++){
		for(j=0;j<v;j++){
			//printf("\nSetando 0 as conexoes");
			novo->are[i][j].conectado = 0;						//Atribui que o vertice nao esta ligado com outro
			novo->are[i][j].arestaSignificado =NULL;
		}
	}

	for(i=0;i<v;i++){
		//printf("\nAtribuindo nullo");
		novo->verticeSignificado[i] = NULL;						//Atribui NULL aos ponteiros que tem o significado do Nó 
	}

	return novo;
}

int temLigacao(pGrafo g, inteiro saida, inteiro entrada){

	if(g->are[saida][entrada].conectado == 0) return 0;
	else return 1;
}


void ligarNos(pGrafo g, inteiro saida, inteiro entrada, double peso, double peso2){

	if(temLigacao(g,saida,entrada)==0){
		//printf("\nFoi possivel ligar os vertices");
		g->are[saida][entrada].conectado = 1;
		g->are[saida][entrada].peso = peso;
		g->are[saida][entrada].peso2 = peso2;
		g->are[saida][entrada].direcao = direction( (pVertex) g->verticeSignificado[saida], (pVertex) g->verticeSignificado[entrada]);
		//printf("\nDIRECAO: %c",g->are[saida][entrada].direcao);
	}else printf("\nOs vertices ja estao ligados");
}

void setValueVertice(pGrafo g, inteiro vertice, void *dado){

	//printf("\nVc entrou com %lu",vertice);

	if(g->verticeSignificado[vertice]==NULL){
		//printf("\nFoi possivel atribuir significado ao vertice");
		g->verticeSignificado[vertice] = dado;
	}else printf("\nO vertice ja possui um significado");
}

void *getValueVertice(pGrafo g, inteiro vertice){

	if(g->verticeSignificado[vertice]==NULL){
		//printf("\nSignificado do vertice: NULL");
		return NULL;
	}else printf("\nO vertice possui um significado");
	
	return g->verticeSignificado[vertice];
}


void setValueAresta(pGrafo g, inteiro saida, inteiro entrada, void *dado){

	if(temLigacao(g,saida,entrada)== 1 && g->are[saida][entrada].arestaSignificado == NULL){
		//printf("\nSignificado da Aresta inserido !");		
		g->are[saida][entrada].arestaSignificado = dado;
	}else printf("\nSignificado da aresta ja foi inserido ou nao possui ligacao");
}

void *getValueAresta(pGrafo g, inteiro saida, inteiro entrada){

	if(temLigacao(g,saida,entrada)!=0 && g->are[saida][entrada].arestaSignificado != NULL) return g->are[saida][entrada].arestaSignificado;	
	else return NULL;
}

unsigned long int pegarPosicao(pGrafo g, char *s1){

	unsigned long int i = 0;

	while(i<g->qntVert){

		if(g->verticeSignificado[i]!=NULL){
			pVertex aux = (pVertex) g->verticeSignificado[i];

			if(strcmp(aux->id,s1)==0){
				//printf("\nPosicao %lu",i);
				return i;
			}
		}
		i++;
	}
}

void menorCusto(pGrafo g, inteiro saida, inteiro entrada, inteiro *vetor){

	double **mat = criarMatriz(g->qntVert+1);

	inteiro linha = 0;
	inteiro coluna = saida;			//COLUNA DA MATRIZ Q VAI SER FEITA E LINHA DA MATRIZ DO GRAFO
	double peso=0;
	inteiro controlar=1;

	inteiro linhaZero=0;
	inteiro colunaZero=saida;
	inteiro colAnt;

	inteiro i;

	vetor[0] = saida;

	while(coluna!=entrada){

		//printf("\n------------------------------------");

		for(i=0;i<g->qntVert;i++){
								//FAZ NAO REPETIR O CAMINHO
			if(g->are[coluna][i].conectado != 0){
				if(linha>=1 && getMatriz(mat,linha-1,i)!=0){
					setMatriz(mat, linha,i,g->are[coluna][i].peso + peso);
				}else if(linha==0){
					setMatriz(mat, linha,i,g->are[coluna][i].peso + peso);
				}			
				
			}

			if(coluna == i && getMatriz(mat,linha,i)==-1) {

				if(linha>=1 && getMatriz(mat,linha-1,i)!=0){

					setMatriz(mat, linha,i,0);
					linhaZero = linha;
					colunaZero = i;
					vetor[controlar] = i;				
					controlar++;	
					//printf("\nOI");			

				}				
			}			
		}

		
		//printLine(mat, g->qntVert, linha);
		colAnt = coluna;
		coluna = ColOfLessLine(mat,g->qntVert, linha);		
		peso = getMatriz(mat,linha,coluna);
		

		//printf("\nEntrada: %lu , Atual: %lu",entrada,coluna);

		//printf("\nO PESO FICOU %.2f",peso);
		linha++;
		//printf("\n------------------------------------");				
	}

	coluna = ColOfLessLine(mat,g->qntVert, linha-1);

	if(linha>=1 && getMatriz(mat,linha-1,i)!=0) {
		vetor[controlar] = coluna;		
		setMatriz(mat, linha,coluna,0);
	}
	//catchZero(mat, g->qntVert);
}

void inserirPilha(pilha **ini, unsigned long int dado){
	
	pilha *inicio = *ini;

	if(inicio == NULL){

		pilha *nova = (pilha *) malloc(sizeof(pilha));
		nova->indice = dado;
		nova->prox = NULL;
		*ini = nova;
	}
	else{

		pilha *nova = (pilha *) malloc(sizeof(pilha));
		nova->indice = dado;
		nova->prox = inicio;
		*ini = nova;
	}
}

unsigned long int minDistance(double *dist, unsigned long int *sptSet, unsigned long int qtdVertices){
	unsigned long int min_index;
	unsigned long int v;
	double min = 1000000;

	for (v = 0; v < qtdVertices; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}

pilha *dijkstra (pGrafo gr, int src, int destino, int w){
	
	double *dist = (double *) malloc(gr->qntVert * sizeof(double));     
	unsigned long int *ant = (unsigned long int *) malloc(gr->qntVert * sizeof(unsigned long int));	
	unsigned long int *sptSet = (unsigned long int *) malloc(gr->qntVert * sizeof(unsigned long int)); 
	unsigned long int i, v, u;
	
	for (i = 0; i < gr->qntVert; i++){

		sptSet[i] = 0;
		dist[i] = 1000000;
		ant[i] = -1;
	}
	
	dist[src] = 0.0;	
	unsigned long int count;
	pilha *inicio = NULL;	

	for (count = 0; count < gr->qntVert-1; count++){

		u = minDistance(dist, sptSet, gr->qntVert);

		if(u == destino){

			u = destino;
			while(ant[u]!=-1){				
				inserirPilha(&inicio, u);
				u = ant[u];
			}			
			inserirPilha(&inicio, u);
			return inicio;
		}
		
		sptSet[u] = 1;
		
		for (v = 0; v < gr->qntVert; v++){
		
			if(w == 2){
				if (!sptSet[v] && gr->are[u][v].conectado != 0 && dist[u] != 1000000 && dist[u] + gr->are[u][v].peso2 < dist[v]){
					dist[v] = dist[u] + gr->are[u][v].peso2;
					ant[v] = u;
				}
			}
			else{
				if (!sptSet[v] && gr->are[u][v].conectado != 0 && dist[u] != 1000000 && dist[u] + gr->are[u][v].peso < dist[v]){
					dist[v] = dist[u] + gr->are[u][v].peso;
					ant[v] = u;
				}
			}
		}
		
	}
}


int tem(char **mat, char *busca, int tamanho){

	int i;
	int cont = 0;

	for(i=0;i<tamanho; i++){

		if(mat[i]!=NULL && strcmp(mat[i],busca)==0) cont = cont +1;


	}

	return cont;



}

void printEstab_daRua(pGrafo gr, phash hashQuadra, char *rua, char *tipo,FILE *f){

	inteiro i,j;
	pEdge e;
	int contcep;
	pComercio c1=NULL,c2=NULL;
	pQuadra q1=NULL,q2=NULL;
	pNo p1=NULL,p2=NULL;

	char ** ceps = (char **)malloc(50000*sizeof(char *));

	for(i=0;i<50000;i++) ceps[i] = NULL;

	contcep=0;

	for(i=0;i<gr->qntVert;i++){

		for(j=0;j<gr->qntVert;j++){

			if(temLigacao(gr,i,j)==1){

				e = (pEdge) gr->are[i][j].arestaSignificado;

				if(strcmp(e->rua,rua)==0){

					p1 = (pNo) getHash(hashQuadra,e->cepL);
					p2 = (pNo) getHash(hashQuadra,e->cepR);					

					if(p1!=NULL && tem(ceps, e->cepL, 50000)==0){

						q1 = (pQuadra) getInfo(p1);
						if(q1!=NULL){
							c1 = getEstabelecimento(q1,tipo);
							if(c1!=NULL){
								fprintf(f,"\nRazao: %s Endereco: %s %s Telefone: %s",c1->razao,rua,c1->num,c1->telefone);
								ceps[contcep] = (char *)malloc((strlen(e->cepL)+1)*sizeof(char));
								strcpy(ceps[contcep],e->cepL);								
								contcep++;

							}

						}						

					}

					if(p2!=NULL && tem(ceps, e->cepR, 50000)==0){

						q2 = (pQuadra) getInfo(p2);
						if(q2!=NULL){
							c2 = getEstabelecimento(q2,tipo);
							if(c2!=NULL){
								fprintf(f,"\nRazao: %s Endereco: %s %s Telefone: %s",c2->razao,rua,c2->num,c2->telefone);
								ceps[contcep] = (char *)malloc((strlen(e->cepR)+1)*sizeof(char));
								strcpy(ceps[contcep],e->cepR);
								contcep++;
							}

						}						

					}
				}

			}
		
		}

	}



}


















