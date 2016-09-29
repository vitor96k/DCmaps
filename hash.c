#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct lista{
	char *chave;
	char *id;
	void *dado;
	struct lista *proximo;
};

struct hash{	
	int tamanho;
	struct lista **dados;			// 
};

pLista getInfoHash(phash a,unsigned long int z){

	pLista zu = a->dados[z];
	return zu;
}

void *getDadoHash(pLista a){
	return a->dado;
}

unsigned long int funcao(phash a, char *chave){

	int i;
	unsigned long int val=7;
	int tam= strlen(chave);

	for(i=0;i<tam;i++){
		val = 3*val + (int)chave[i];
	}
	
	val = val % a->tamanho;

	return val;	
	 
}

phash criarHash(int n){

	int i;

	phash novo = (phash)malloc(sizeof(hash));				//Criou um ponteiro para hash
	novo->tamanho=n;
	novo->dados = (struct lista **)malloc((n+1)*sizeof(struct lista *));	// Salvou n ponteiros para lista ()

	if(novo->dados == NULL){
		free(novo);
		printf("\nERRO NA CRIACAO DA HASH");
		return NULL;
	}

	//printf("\nHash alocada com %d posicoes",n);

	
	for(i=0; i<n;i++){
		novo->dados[i] = NULL;				//SETA O PONTEIRO COMO NULO PARA TODAS POSICOES
	}

	return novo;	
}

void insertHash(phash a, char *chave, void *p){	

	unsigned long int  val= funcao(a,chave);	

	//printf("\nInserir na posicao: %lu",val);


	if(a->dados[val]==NULL){
		//printf("\nSem colisao");
		a->dados[val] = (struct lista *)malloc(sizeof(struct lista));
		a->dados[val]->dado=p;
		a->dados[val]->chave=(char *)malloc((1+strlen(chave))*sizeof(char));
		strcpy(a->dados[val]->chave,chave);		

		a->dados[val]->proximo=NULL;
	}else {
		//printf("\nColisao com a chave %s",chave);

		struct lista *aux = a->dados[val];
		struct lista *ant = a->dados[val];

		while(aux!=NULL){
			ant=aux;
			aux=aux->proximo;
		}

		ant->proximo = (struct lista*)malloc(sizeof(struct lista));
		ant->proximo->dado = p;
		ant->proximo->chave=(char *)malloc((1+strlen(chave))*sizeof(char));
		strcpy(ant->proximo->chave,chave);		

		ant->proximo->proximo=NULL;
	}
}

void *getHash(phash a, char *chave){

	unsigned long int  val= funcao(a,chave);		
	struct lista *aux=a->dados[val];

	while(aux!=NULL && strcmp(aux->chave,chave)!=0){
		aux=aux->proximo;
	}

	if(aux==NULL)	 return NULL;
	else return aux->dado;
		
}

pLista getProxHash(pLista a){
	return a->proximo;
}

void insertHash2(phash a, char *chave, void *p, char *id){

	int cont=0;

	unsigned long int  val= funcao(a,chave);	

	//printf("\nInserir na posicao: %lu",val);


	if(a->dados[val]==NULL){
		//printf("\nSem colisao");
		a->dados[val] = (struct lista *)malloc(sizeof(struct lista));
		a->dados[val]->dado=p;
		a->dados[val]->chave=(char *)malloc((1+strlen(chave))*sizeof(char));
		strcpy(a->dados[val]->chave,chave);	
		a->dados[val]->id=(char *)malloc((1+strlen(id))*sizeof(char));
		strcpy(a->dados[val]->id,id);			

		a->dados[val]->proximo=NULL;
	}else {
		//printf("\nColisao com a chave %s",chave);

		struct lista *aux = a->dados[val];
		struct lista *ant = a->dados[val];

		while(aux!=NULL){

			if(strcmp(aux->id,id)==0 && strcmp(aux->chave,chave)==0) cont=1;

			ant=aux;
			aux=aux->proximo;
		}

		if(cont==0){
			ant->proximo = (struct lista*)malloc(sizeof(struct lista));
			ant->proximo->dado = p;
			ant->proximo->chave=(char *)malloc((1+strlen(chave))*sizeof(char));
			strcpy(ant->proximo->chave,chave);	

			ant->proximo->id=(char *)malloc((1+strlen(id))*sizeof(char));
			strcpy(ant->proximo->id,id);		

			ant->proximo->proximo=NULL;

		}		
	}
}



