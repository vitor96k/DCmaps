#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "retangulo.h"


char getFaceMorador(pQuadra q, char *fone){

	pCasa c = q->moradores;

	while(c!=NULL && strcmp(c->fone,fone)!=0){
		c=c->prox;
	}

	if(c!=NULL) return c->face;
	else return 'F';	
}

char getFaceMoradorNome(pQuadra q, char *n){

	pCasa c = q->moradores;

	while(c!=NULL && strcmp(c->nome,n)!=0){
		c=c->prox;
	}

	if(c!=NULL) return c->face;
	else return 'F';	

}


void setPoint(pQuadra q, char f, double *x, double *y){

	if(f=='N' || f=='n'){
		*x = (q->x + q->x + q->l)/2; //ok
		*y = q->y+q->h;		//ok

	}else if(f=='S' || f=='s'){
		*x = (q->x + q->x + q->l)/2; //ok
		*y = q->y;			//ok
		
	}else if(f=='L' || f=='l'){
		*x = (q->x + q->l);              //ok
		*y = (q->y + q->y + q->h)/2;

		
	}else if(f=='O' || f=='o'){
		*x = q->x;			//ok
		*y = (q->y + q->y + q->h)/2;
		
	}

	printf("\nFace: %c x: %.2f y: %.2f",f,*x,*y);

}

double distancia(double x1,double y1,double x2,double y2){

	double auxX = (x1-x2)*(x1-x2);
	double auxY = (y1-y2)*(y1-y2);

	return sqrt(auxX + auxY);
}

char getFaceEstab(pQuadra q, char *tipo){
	pComercio c = q->comercial;
	while(c!=NULL && strcmp(c->tipo,tipo)!=0){
		c=c->prox;
	}

	if(c!=NULL) return c->face;
	else return 'f';
}

pComercio getEstabelecimento(pQuadra q, char *tipo){

	pComercio c = q->comercial;
	while(c!=NULL && strcmp(c->tipo,tipo)!=0){
		c=c->prox;
	}

	return c;
}



pCasa criarCasa(char face,char *num, char *nome,char *fone){

	pCasa novo = (pCasa)malloc(sizeof(casa));

	novo->face=face;	

	novo->num = (char *) malloc((strlen(num)+ 1)*sizeof(char));
	strcpy(novo->num,num);

	novo->nome = (char *) malloc((1+strlen(nome))*sizeof(char));
	strcpy(novo->nome,nome);

	novo->fone = (char *) malloc(( 1+ strlen(fone)) *sizeof(char));
	strcpy(novo->fone,fone);

	novo->prox = NULL;

	return novo;
}

pComercio criarComercio(char face, char *num, char *tipo, char *razao, char *telefone){

	pComercio novo =  (pComercio)malloc(sizeof(comercio));

	novo->face=face;	

	novo->num = (char *) malloc(( 1+strlen(num)) *sizeof(char));
	strcpy(novo->num,num);

	novo->tipo = (char *) malloc((1+strlen(tipo))*sizeof(char));
	strcpy(novo->tipo,tipo);

	novo->razao = (char *) malloc((1+strlen(razao))*sizeof(char));
	strcpy(novo->razao,razao);

	novo->telefone = (char *) malloc((1+strlen(telefone))*sizeof(char));
	strcpy(novo->telefone,telefone);

	novo->prox = NULL;

	return novo;
}

pRetangulo criarRetangulo(float x,float y,float l,float h, char *cor){

	pRetangulo novo =  (pRetangulo)malloc(sizeof(retangulo));

	novo->x=x;
	novo->y=y;
	novo->l=l;
	novo->h=h;

	novo->cor = (char *) malloc((1+strlen(cor))*sizeof(char));
	strcpy(novo->cor,cor);

	return novo;
}

pQuadra criarQuadra(float x,float y,float l,float h, char *cep){

	pQuadra novo =  (pQuadra)malloc(sizeof(quadra));

	novo->x=x;
	novo->y=y;
	novo->l=l;
	novo->h=h;

	novo->cep = (char *) malloc((1+strlen(cep)) *sizeof(char));
	strcpy(novo->cep,cep);

	novo->moradores = NULL;
	novo->comercial = NULL;

	return novo;
}

pAux criarAux(char *id, float x,float y){

	pAux novo =  (pAux)malloc(sizeof(aux));

	novo->x=x;
	novo->y=y;

	novo->id = (char *) malloc(1+ (strlen(id)) *sizeof(char));
	strcpy(novo->id,id);

	return novo;
}

void ligarCasa(pQuadra q, pCasa c){

	pCasa aux = q->moradores;

	if(q->moradores == NULL){
		q->moradores = c;	
	} 

	else{
		while(aux->prox!=NULL) aux=aux->prox;
		aux->prox = c;
	}
}

void ligarComercio(pQuadra q, pComercio c){

	pComercio aux = q->comercial;

	if(q->comercial == NULL){
		q->comercial = c;	
	} 

	else{
		while(aux->prox!=NULL) aux=aux->prox;
		aux->prox = c;
	}
}

void mq(pQuadra q, FILE *f){

	int i=1;

	pCasa aux = q->moradores;
	while(aux!=NULL){
		fprintf(f,"\nMorador %d:",i);
		fprintf(f,"\nNome: %s - Tel: %s - Face: %c - Num: %s",aux->nome,aux->fone,aux->face,aux->num);
		i++;
		aux=aux->prox;
	}
}

void EstabDaQuadra(pQuadra q, char *est, int *k, FILE *f){	

	pComercio aux = q->comercial;
	while(aux!=NULL){

		if(strcmp(aux->tipo,est)==0){
			fprintf(f,"\nEstabelecimento %d",*k);			
			fprintf(f,"\nCEP: %s - FACE: %c - Num: %s",q->cep,aux->face,aux->num);
			*k = *k +1;			
		}		
		aux=aux->prox;
	}
}

void EstabDaQuadra2(pQuadra q, char *est, int *k, double x, double y, double l, double h,FILE *f){	

	pComercio aux = q->comercial;
	//printf("\nENTROU NA ESTABQUADRA2");
	while(aux!=NULL){

		if(strcmp(aux->tipo,est)==0 && q->x >= x && (q->x+q->l) <= (x+l) && q->y <= y && (q->y-q->h) >= y-h){
			fprintf(f,"\nEstabelecimento %d",*k);			
			fprintf(f,"\nCEP: %s - FACE: %c - Num: %s",q->cep,aux->face,aux->num);
			*k = *k +1;			
		}		
		aux=aux->prox;
	}
}

void EstabDaQuadraAll(pQuadra q, char *est, int *k,FILE *f){

	pComercio aux = q->comercial;
	while(aux!=NULL){

		if(strcmp(aux->tipo,est)==0){
			fprintf(f,"\nEstabelecimento %d",*k);			
			fprintf(f,"\nFace: %c - Num: %s - Razao: %s - Telefone: %s",aux->face,aux->num,aux->razao,aux->telefone);
			*k = *k +1;			
		}		
		aux=aux->prox;
	}
}

void EstabDaQuadraAll2(pQuadra q, char *est, int *k, double x, double y, double l, double h,FILE *f){	

	pComercio aux = q->comercial;
	//printf("\nENTROU NA ESTABQUADRA2");
	while(aux!=NULL){

		if(strcmp(aux->tipo,est)==0 && q->x >= x && (q->x+q->l) <= (x+l) && q->y <= y && (q->y-q->h) >= y-h){
			fprintf(f,"\nEstabelecimento %d",*k);			
			fprintf(f,"\nFace: %c - Num: %s - Razao: %s - Telefone: %s",aux->face,aux->num,aux->razao,aux->telefone);
			*k = *k +1;			
		}		
		aux=aux->prox;
	}
}

void printHidrantes(pAux a, FILE *f){
	fprintf(f,"\nID:%s, x:%.2f, y:%.2f",a->id,a->x,a->y);
}

int torreInside(pQuadra q, pAux a){

	if(a->x >= q->x && (a->x) <= (q->x+q->l) && a->y <= q->y && (a->y) >= q->y-q->h)	return 1;		
	else return 0;
}

void limites(pQuadra esquerda, pQuadra direita, double *x1,double *x2,double *y1,double *y2){

	if(direita!=NULL && esquerda!=NULL){

		if(esquerda->y == direita->y){
			*x1= (direita->x + (esquerda->x + esquerda->l))/2;
			*x2 = *x1;
			

		}else if(esquerda->x == direita->x){

			*x1 = esquerda->x;
			*x2 = esquerda->x + esquerda->h;
			

		}

	}else if(esquerda==NULL){

	}else if(direita==NULL){

	}

}



