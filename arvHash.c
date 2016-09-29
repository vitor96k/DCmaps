#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"
#include "arvHash.h"
#include "hash.h"
#include "arvore.h"


void et(void *h, char *key,FILE *f){

	int i = 1;

	phash hashQ_est = (phash) h;	 	//HASH RECEBIDA
	pNo n = NULL;

	unsigned long int val= funcao(hashQ_est,key);	//GEROU A CHAVE;

	pLista aux = getInfoHash(hashQ_est,val);		// PEGA O PRIMEIRO ELEMENTO DO INDICE;

	if(aux!=NULL){
		n = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH
	}

	while(aux!=NULL){		

		n = (pNo)getDadoHash(aux);
		pQuadra q = (pQuadra)getInfo(n);
		if(q!=NULL){
			 EstabDaQuadra(q,key,&i,f);
		}		
		aux = getProxHash(aux);
	}
}

void et2(void *h, char *key,double x,double y,double l ,double alt, FILE *f){

	//printf("\nEntrou na funcao");

	int i = 1;

	phash hashQ_est = (phash) h;	 	//HASH RECEBIDA
	pNo n = NULL;

	unsigned long int val= funcao(hashQ_est,key);	//GEROU A CHAVE;

	pLista aux = getInfoHash(hashQ_est,val);		// PEGA O PRIMEIRO ELEMENTO DO INDICE;

	if(aux!=NULL){
		n = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH
	}

	while(aux!=NULL){

		n = (pNo)getDadoHash(aux);
		pQuadra q = (pQuadra)getInfo(n);
		if(q!=NULL){
			 //printf("\nAchou a quadra");
			 EstabDaQuadra2(q,key,&i,x,y,l,alt,f);
		}		
		aux = getProxHash(aux);
	}

}

void ed(void *h, char *key,FILE *f){

	int i = 1;

	phash hashQ_est = (phash) h;	 	//HASH RECEBIDA
	pNo n = NULL;

	unsigned long int val= funcao(hashQ_est,key);	//GEROU A CHAVE;

	pLista aux = getInfoHash(hashQ_est,val);		// PEGA O PRIMEIRO ELEMENTO DO INDICE;

	if(aux!=NULL){
		n = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH
	}

	while(aux!=NULL){		

		n = (pNo)getDadoHash(aux);
		pQuadra q = (pQuadra)getInfo(n);		
		if(q!=NULL){
			 fprintf(f,"\n\nCEP: %s",q->cep);
			 EstabDaQuadraAll(q,key,&i,f);
		}		
		aux = getProxHash(aux);
	}
}

void ed2(void *h, char *key,double x,double y,double l ,double alt,FILE *f){

	//printf("\nEntrou na funcao");

	int i = 1;

	phash hashQ_est = (phash) h;	 	//HASH RECEBIDA
	pNo n = NULL;

	unsigned long int val= funcao(hashQ_est,key);	//GEROU A CHAVE;

	pLista aux = getInfoHash(hashQ_est,val);		// PEGA O PRIMEIRO ELEMENTO DO INDICE;

	if(aux!=NULL){
		n = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH
	}

	while(aux!=NULL){

		n = (pNo)getDadoHash(aux);
		pQuadra q = (pQuadra)getInfo(n);
		if(q!=NULL){
			 //printf("\nAchou a quadra");
			  EstabDaQuadraAll2(q,key,&i,x,y,l,alt,f);
		}		
		aux = getProxHash(aux);
	}
}

void searchAux(void *h, char *key,double x,double y,double l ,double alt,FILE *f){

	int i = 1;

	phash hashQ_est = (phash) h;	 	//HASH RECEBIDA
	pNo n = NULL;

	unsigned long int val= funcao(hashQ_est,key);	//GEROU A CHAVE;

	pLista aux = getInfoHash(hashQ_est,val);		// PEGA O PRIMEIRO ELEMENTO DO INDICE;

	if(aux!=NULL){
		n = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH
	}

	while(aux!=NULL){

		n = (pNo)getDadoHash(aux);
		pAux a = (pAux)getInfo(n);

		if(a!=NULL){
			 //printf("\nAchou a quadra");
			if(a->x >= x && (a->x) <= (x+l) && a->y <= y && (a->y) >= y-alt){
				printHidrantes(a,f);
			}			 
		}		
		aux = getProxHash(aux);
	}
}



void hq(void *h, char *key, double l, void *h2, char *key2, FILE *f){

	phash z = (phash) h;
	pQuadra q=NULL;
	pNo n2 = NULL;

	pNo n = (pNo) getHash(z,key);
	if(n!=NULL) q = (pQuadra) getInfo(n);	

	if(q!=NULL){	

		double x = q->x - l;
		if(x<0) x=0;

		double larg = q->l + 2*l;

		double y = q->y + l;		
		double alt = q->h + 2*l;		

		phash Hidrantes = (phash) h2;
		unsigned long int val= funcao(Hidrantes,key2);	
		
		pLista aux = getInfoHash(Hidrantes,val);

		if(aux!=NULL){
			n2 = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH

			while(aux!=NULL){
	
				n2 = (pNo)getDadoHash(aux);
				pAux a = (pAux)getInfo(n2);

				if(a!=NULL){					
			
					if(a->x >= x && (a->x) <= (x+larg) && a->y <= y && (a->y) >= y-alt){
						printHidrantes(a,f);
					}			 
				}					
				aux = getProxHash(aux);
			}
		}	
		
	}	
}

void qt(void *arvore, void *hash, FILE *f){

	pNo raiz = (pNo) arvore;
	phash torre = (phash) hash;
	pNo n2 =NULL;

	if(raiz==NULL){
		return;
	}

	qt(getLeft(raiz),hash,f);

	if(getTipo(raiz) == 1){

		unsigned long int val= funcao(torre,"4");
		
		pLista aux = getInfoHash(torre,val);

		if(aux!=NULL){
			n2 = (pNo)getDadoHash(aux);			// PEGA O CONTEUDO DA HASH

			while(aux!=NULL){
	
				n2 = (pNo)getDadoHash(aux);
				pAux a = (pAux)getInfo(n2);

				if(a!=NULL){			

					if(a->x >= getX(raiz) && (a->x) <= ( getX(raiz)+getL(raiz)) && a->y <= getY(raiz)&& (a->y) >= getY(raiz)-getH(raiz)){
						pQuadra pq = (pQuadra) getInfo(raiz);
						fprintf(f,"\nCEP: %s, x:%.2f, y:%.2f, l:%.2f, h:%.2f",pq->cep,pq->x,pq->y,pq->l,pq->h);
					}			 
				}					
				aux = getProxHash(aux);
			}
		}
	}	
	qt(getRight(raiz),hash,f);
}






