#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include "arvore.h"
#include "areQuadra.h"
#include "grafo.h"

struct no{

	int tipo;
	float xdir,ydir,ldir,hdir;	
	struct no *dir;
	struct no *esq;
	struct no *pai;
	void *dados;
};

pNo *criarArvore(){
	
	pNo *raiz = (pNo*)malloc(sizeof(pNo));			
	*raiz=NULL;										
	return raiz;
}

void *getInfo(pNo ele){
	return ele->dados;	
}

double getX(pNo a){
	return a->xdir;
} 
double getY(pNo a){
	return a->ydir;
}
double getL(pNo a){
	return a->ldir;
}
double getH(pNo a){
	return a->hdir;
}

pNo getLeft(pNo a){
	return a->esq;
}
pNo getRight(pNo a){
	return a->dir;
}

int getTipo(pNo a){
	return a->tipo;
}

void findCloser(pNo *raiz,double x, double y, double *dist, char *s){

	if(*raiz==NULL){
		return;
	}

	findCloser(&(*raiz)->esq,x,y,dist,s);

	if(distancia (  (*raiz)->xdir,(*raiz)->ydir,x,y   ) < *dist || *dist == -1){
		
		*dist = distancia((*raiz)->xdir,(*raiz)->ydir,x,y);
		pVertex aux = (pVertex)(*raiz)->dados;		
		strcpy(s,aux->id);
		//printf("\n%s",s);
		//printf("\nselecionado: %.2f %.2f",(*raiz)->xdir,(*raiz)->ydir);						
	}	
	
	findCloser(&(*raiz)->dir,x,y,dist,s);

}

pNo inserir(pNo *raiz, float chave, float y, float l, float h,void *dado, int tipo){
	
	pNo atual=*raiz;
	pNo ant=NULL;
	
	pNo novo=(pNo)malloc(sizeof(struct no));
	novo->esq=NULL;
	novo->dir=NULL;

	novo->tipo = tipo;

	novo->xdir=chave;
	novo->ydir=y;
	novo->ldir=l;
	novo->hdir=h;

	novo->dados = dado;		

	if(*raiz==NULL){		
		novo->pai=NULL;	
		*raiz=novo;	
		return novo;

	}else{
		while(atual!=NULL){					

			ant=atual;	
									 // O ATUAL VAI FICAR NULL NO FINAL DO LOOP
			if(chave < atual->xdir) atual=atual->esq;				
			else atual=atual->dir;
		}

		novo->pai=ant;

		if(ant->xdir > chave) ant->esq=novo;
		else ant->dir=novo;			
		return novo;
	}	
	
}

void printar(pNo *raiz){

	if(*raiz==NULL){
		return;
	}

	if(*raiz!=NULL){

		printar(&(*raiz)->esq);
		printf("\nx: %.2lf,y: %.2lf,l: %.2lf,h: %.2lf",(*raiz)->xdir,(*raiz)->ydir,(*raiz)->ldir,(*raiz)->hdir);			
		printar(&(*raiz)->dir);		
	}
}

void auxnos(pNo *raiz, int *contar){

	if(*raiz==NULL){
		return;
	}

	auxnos(&(*raiz)->esq,contar);
	*contar=(*contar)+1;
	auxnos(&(*raiz)->dir,contar);	
}

int qtdNos(pNo *raiz){

	int k=0;	
	auxnos(raiz,&k);
	return k;
}

int altura(pNo *raiz){

	int hd,he;

	if(*raiz==NULL){
		return -1;
	}

	he=altura(&(*raiz)->esq);
	hd=altura(&(*raiz)->dir);	

	if(hd>he) return (hd+1);
	else return (he+1);

}
void remover(pNo *raiz,pNo achou){


	//printf("\nRemovendo ponto x:%.2f, y:%.2f, l:%.2f, h:%.2f",achou->xdir,achou->ydir,achou->ldir,achou->hdir);
	//Ponteiro achou aponta para o elemento que sera removido

	pNo pai=NULL,paisub=NULL,sub=NULL;	// pai é o pai do achou; sub aponta para a folha da subarvore a esquerda mais a direita e o paisub para seu pai
	pai=achou->pai;

	//printf("\nO pai do %.2f,%.2f e: %.2f,%.2f",achou->x,achou->y,pai->x,pai->y);	

	if(achou!=NULL){						//Encontrou o elemento
		//printf("\nTry 1");
		//----VERIFICAR QUANTIDADE DE FILHOS E REMOVER----
		if(achou->esq==NULL && achou->dir==NULL){		//Nenhum filho
			//printf("\nNenhum filho");
			if(pai!=NULL){
				//printf("\nPai diferente de nulo");
				if(pai->esq!=NULL && pai->esq==achou) pai->esq=NULL;
				else pai->dir=NULL;
				free(achou);
			}else{						//raiz
				//printf("\nRemovendo raiz pura");
				free(achou);
				*raiz=NULL;
			}											
			//printf("\nTry 2");
		}else{

			if(achou->esq!=NULL && achou->dir!=NULL){	//Dois Filhos
				//printf("\nRemover com 2 filhos");	
				sub=achou->esq;
				while(sub->dir!=NULL){
					paisub=sub;
					sub=sub->dir;
				}

				//printf("\nFilho mais a direita da esquerda é: %d",sub->chave);
				if(sub!=achou->esq){
					//Andou para a direta
					achou->dados = sub->dados;
					achou->xdir = sub->xdir;
					achou->ydir = sub->ydir;
					achou->ldir = sub->ldir;
					achou->hdir = sub->hdir;
					achou->tipo = sub->tipo;					
					paisub->dir=sub->esq;					
				}else{								//Nao andou para a direita								
					achou->dados = sub->dados;
					achou->xdir = sub->xdir;
					achou->ydir = sub->ydir;
					achou->ldir = sub->ldir;
					achou->hdir = sub->hdir;
					achou->tipo = sub->tipo;
					achou->esq=sub->esq;
				}
				//printf("\nTry 3");
			}else{										//Um filho
				//printf("\nUm filho");
				if(achou->dir==NULL){
					//printf("\nRemover com um filho, filho a esquerda");
					(achou->esq)->pai = achou->pai;
					*achou = *(achou->esq);
				}
				else{
					//printf("\nRemover com um filho, filho a direita");
					(achou->dir)->pai = achou->pai;
					*achou = *(achou->dir);					
				}
			}
		}		
		//----\VERIFICAR QUANTIDADE DE FILHOS E REMOVER----
	}	
}

void changeAllColors(pNo *raiz,char *antigo,char *novo, int *qnt){

	if(*raiz==NULL){
		return;
	}

	if(*raiz!=NULL){

		changeAllColors(&(*raiz)->esq,antigo,novo,qnt);

		if((*raiz)->tipo == 0){

			pRetangulo r = (*raiz)->dados;

			if(strcmp(r->cor,antigo)==0){
				r->cor= (char *)malloc((1+strlen(novo))*sizeof(char));
				strcpy(r->cor,novo);				
				*qnt=(*qnt)+1;
			} 
		}		
			
		changeAllColors(&(*raiz)->dir,antigo,novo,qnt);
	}
}

void auxSvg(pNo *raiz, FILE *fsvg,float b,int op){

	if(*raiz==NULL){
		return;
	}

	if(*raiz!=NULL){

		auxSvg(&(*raiz)->esq,fsvg,b,op);	

		if((*raiz)->tipo == 0){
			
			pRetangulo r = (pRetangulo) (*raiz)->dados;
			fprintf(fsvg,"\n<rect x=%c%.2f%c y=%c%.2f%c width=%c%.2f%c height=%c%.2f%c ",34,r->x,34,34,(r->y),34,34, r->l,34,34, r->h,34);
			fprintf(fsvg,"style=%cfill:%s ;fill-opacity:0.5;stroke:black;stroke-width:0.1%c/>",34,r->cor,34); 
		}else{
			if((*raiz)->tipo == 1){

				pQuadra q = (pQuadra) (*raiz)->dados;
				//fprintf(fsvg,"\n<rect x=%c%.2f%c y=%c%.2f%c width=%c%.2f%c height=%c%.2f%c ",34,q->x,34,34,(q->y),34,34, q->l,34,34, q->h,34);
				//fprintf(fsvg,"style=%cfill:white ;fill-opacity:0.1;stroke:white;stroke-width:0.05%c/>",34,34); 

				
				fprintf(fsvg,"\n<rect x=%c%.2f%c y=%c%.2f%c width=%c%.2f%c height=%c%.2f%c ",34,q->x,34,34,(q->y),34,34, q->l,34,34, q->h,34);
				fprintf(fsvg,"style=%cfill:white ;fill-opacity:0.1;stroke:white;stroke-width:0.05%c>",34,34); 
				fprintf(fsvg,"\n</rect>"); 
				fprintf(fsvg,"<text x=%c%.2f%c y=%c%.2f%c font-family=%cVerdana%c font-size=%c10%c fill=%cwhite%c > %s </text>",34,q->x+(q->l)/4,34,34,q->y+(q->h)/2,34,34,34,34,34,34,34,q->cep);
				


			
			}else if((*raiz)->tipo == 2){

				pAux a = (pAux) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cpurple%c />",34,34,34,34);

			}else if((*raiz)->tipo == 3){

				pAux a = (pAux) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cred%c />",34,34,34,34);

			}else if((*raiz)->tipo == 4){
				pAux a = (pAux) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cblue%c />",34,34,34,34);

			}else if((*raiz)->tipo == 5 && op == 1){
				pVertex a = (pVertex) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cgreen%c />",34,34,34,34);

			}

		}	

			
		auxSvg(&(*raiz)->dir,fsvg,b,op);		
	}
}



void gerarSvg(pNo *raiz, char *path, float a, float b, int op){

	FILE *fsvg=fopen(path,"w");

	fprintf(fsvg,"<svg width=%c%.2f%c height=%c%.2f%c xmlns=%chttp://www.w3.org/2000/svg%c>",34,(a)+5,34,34,(b)+5,34,34,34);
	auxSvg(raiz,fsvg,b,op);
	fprintf(fsvg,"\n</svg>");
}


void changeColorArea(pNo raiz,char *antigo, char *novo, double xmax,double y, double h, int *qnt){

	if(raiz==NULL) return;	

	changeColorArea(raiz->esq, antigo, novo,xmax,y,h,qnt);
	
	if(raiz->tipo == 0){

		pRetangulo aux = raiz->dados;

		if(strcmp(aux->cor,antigo)==0 && (raiz->xdir + raiz->ldir) <= xmax && raiz->ydir <= y && (raiz->ydir)-(raiz->hdir) >= y-h){
			aux->cor= (char *)malloc((1+strlen(novo))*sizeof(char));
			strcpy(aux->cor,novo);
			*qnt=(*qnt)+1;
		} 
	}
	
	changeColorArea(raiz->dir,antigo, novo,xmax,y,h,qnt);
}

void defineArea(pNo *raiz, char *antigo, char *novo, double x, double y, double l, double h, int *qnt){

	pNo inicio,fim,ant1,ant2,inter,aux;
	inicio=*raiz;
	fim=*raiz;
	inter=*raiz;

	pRetangulo auxini,auxinter,auxfim;	

	if(*raiz==NULL) return;

	do{
		
		ant1=inicio;
		if(inicio->xdir > x) inicio=inicio->esq;				//ACHA O NÓ NO NIVEL MAIS ALTO COM O X = XMIN OU X>XMIN
		else inicio=inicio->dir; 

		ant2=fim;
		if(fim->xdir > x+l) fim=fim->esq;						//ACHA O NÓ NO NIVEL MAIS ALTO COM O X = XMAX OU X < XMAX
		else fim=fim->dir;
		
		if(inicio!=NULL && fim!=NULL && inicio==fim) inter=inicio;						// PONTO DE INTERCESSAO ENTRE A TRAJETORIA DO MENOR X E O MAX

	}while(inicio!=NULL && fim!=NULL);

		if(inicio==NULL) inicio=ant1;

		if(fim==NULL) fim=ant2;

		while(inter->pai!=NULL && inter->pai->xdir >= x){				//ACHA O NÓ QUE RAMIFICA O CAMINHO XMIN E XMAX
			inter=inter->pai;
		}		

		while(inicio!=inter){

			ant1=inicio;

			if(inicio->xdir >=x && (inicio->xdir + inicio->ldir) <= x+l){
				
				if(inicio->tipo == 0){

					auxini = (pRetangulo)inicio->dados;

					if(strcmp(auxini->cor,antigo)==0 && inicio->ydir <= y && (inicio->ydir)-(inicio->hdir) >= y-h){
						auxini->cor= (char *)malloc((1+strlen(novo))*sizeof(char));
						strcpy(auxini->cor,novo);	
						*qnt=(*qnt)+1;																//ALTERA A COR DESSE ELEMENTO
					}
				}
				

				changeColorArea(inicio->dir,antigo,novo,(x+l),y,h,qnt);											//ALTERA A COR DA SUBARVORE A DIREITA;					
			}
			inicio=inicio->pai;			
		}

		if(inter->tipo == 0){

			auxinter = (pRetangulo)inter->dados;

			if(strcmp(auxinter->cor,antigo)==0 &&(inter->xdir + inter->ldir) <= x+l && inter->ydir <= y && (inter->ydir)-(inter->hdir) >= y-h){
				auxinter->cor= (char *)malloc((1+strlen(novo))*sizeof(char));
				strcpy(auxinter->cor,novo);
				*qnt=(*qnt)+1;	
			}
		}	

		while(fim!=inter){

			if(fim->xdir < x+l){
				
				if(fim->tipo == 0){

					auxfim = (pRetangulo)fim->dados;

					if(strcmp(auxfim->cor,antigo)==0 && fim->ydir <= y && (fim->ydir)-(fim->hdir) >= y-h){
						auxfim->cor= (char *)malloc((1+strlen(novo))*sizeof(char));
						strcpy(auxfim->cor,novo);
					 	*qnt=(*qnt)+1;
					}

				}			
				 
				changeColorArea(fim->esq,antigo,novo,x+l,y,h,qnt);			
			}

			if(fim->xdir == x+l) changeColorArea(fim->esq,antigo,novo,x+l,y,h,qnt); // SÓ ALTERA A SUBARVORE POIS NAO TERA UM RETANGULO Q COMECE NO LIMITE DO RETANGULO DE BUSCA
			fim=fim->pai;
		}
}

void RemoverResto(pNo raiz, double x, double y, double l, double h, int *qnt, pNo *inicio){

	if(raiz==NULL) return;	

	RemoverResto(raiz->esq,x,y,l,h,qnt,inicio);
	
	if((raiz->xdir + raiz->ldir) <= (x+l) && raiz->ydir <= y && (raiz->ydir)-(raiz->hdir) >= y-h){
		remover(inicio,raiz);
		*qnt=(*qnt)+1;
	} 

	RemoverResto(raiz->dir,x,y,l,h,qnt,inicio);
}

void setDeletePath(pNo *raiz, double x, double y, double l, double h, int *qnt){

	pNo inicio,fim,ant1,ant2,inter,aux;
	inicio=*raiz;
	fim=*raiz;
	inter=*raiz;

	if(*raiz==NULL) return;

	do{
		
		ant1=inicio;
		if(inicio->xdir > x) inicio=inicio->esq;				//ACHA O NÓ NO NIVEL MAIS ALTO COM O X = XMIN OU X>XMIN
		else inicio=inicio->dir; 

		ant2=fim;
		if(fim->xdir > x+l) fim=fim->esq;						//ACHA O NÓ NO NIVEL MAIS ALTO COM O X = XMAX OU X < XMAX
		else fim=fim->dir;
		
		if(inicio!=NULL && fim!=NULL && inicio==fim) inter=inicio;						// PONTO DE INTERCESSAO ENTRE A TRAJETORIA DO MENOR X E O MAX

	}while(inicio!=NULL && fim!=NULL);

		if(inicio==NULL) inicio=ant1;

		if(fim==NULL) fim=ant2;

		while(inter->pai!=NULL && inter->pai->xdir >= x){				//ACHA O NÓ QUE RAMIFICA O CAMINHO XMIN E XMAX
			inter=inter->pai;
		}

		//printf("\nInicio é %.2f,%.2f",inicio->xdir,inicio->ydir);				
		//printf("\nInter é %.2f,%.2f",inter->xdir,inter->ydir);
		//printf("\nFm é %.2f,%.2f",fim->xdir,fim->ydir);		

		while(inicio!=inter){

			ant1=inicio;

			if(inicio->xdir >=x && (inicio->xdir + inicio->ldir) <= x+l){				
				if(inicio->ydir <= y && (inicio->ydir)-(inicio->hdir) >= y-h){
					remover(raiz,inicio);
					*qnt=(*qnt)+1;																//REMOVE DESSE ELEMENTO
				}

				RemoverResto((inicio->dir),x,y,l,h,qnt,raiz);											//REMOVE A SUBARVORE A DIREITA;					
			}
			inicio=inicio->pai;			
		}

		//printf("\n%.2f,%.2f; ",inter->x,inter->y);
		if((inter->xdir + inter->ldir) <= x+l && inter->ydir <= y && (inter->ydir)-(inter->hdir) >= y-h){

			remover(raiz,inter);
			*qnt=(*qnt)+1;	
		} 

		while(fim!=inter){

			if(fim->xdir < x+l){
				//printf("\n");
				//printf("%.2f,%.2f; ",fim->x,fim->y );				
				if(fim->ydir <= y && (fim->ydir)-(fim->hdir) >= y-h){
					  remover(raiz,fim);
					 *qnt=(*qnt)+1;
				} 
				RemoverResto(fim->esq,x,y,l,h,qnt,raiz);			
			}

			if(fim->xdir == x+l) RemoverResto(fim->esq,x,y,l,h,qnt,raiz); // SÓ ALTERA A SUBARVORE POIS NAO TERA UM RETANGULO Q COMECE NO LIMITE DO RETANGULO DE BUSCA
			fim=fim->pai;
		}
}

void mrAux(pNo raiz, double xmax,double y, double h, FILE *f){

	if(raiz==NULL) return;	

	mrAux(raiz->esq,xmax,y,h,f);
	
	if(raiz->tipo == 1){

		
		pQuadra aux = (pQuadra) raiz->dados;

		if( (raiz->xdir + raiz->ldir) <= xmax && raiz->ydir <= y && (raiz->ydir)-(raiz->hdir) >= y-h){
					
			mq(aux,f);			
		} 
	}	
	mrAux(raiz->dir,xmax,y,h,f);
}

void mr(pNo *raiz, double x, double y, double l, double h, FILE *f){
	
	pNo inicio,fim,ant1,ant2,inter,aux;
	inicio=*raiz;
	fim=*raiz;
	inter=*raiz;

	pQuadra auxini,auxinter,auxfim;	

	if(*raiz==NULL) return;

	do{
		
		ant1=inicio;
		if(inicio->xdir > x) inicio=inicio->esq;				//ACHA O NÓ NO NIVEL MAIS ALTO COM O X = XMIN OU X>XMIN
		else inicio=inicio->dir; 

		ant2=fim;
		if(fim->xdir > x+l) fim=fim->esq;						//ACHA O NÓ NO NIVEL MAIS ALTO COM O X = XMAX OU X < XMAX
		else fim=fim->dir;
		
		if(inicio!=NULL && fim!=NULL && inicio==fim) inter=inicio;						// PONTO DE INTERCESSAO ENTRE A TRAJETORIA DO MENOR X E O MAX

	}while(inicio!=NULL && fim!=NULL);

		if(inicio==NULL) inicio=ant1;

		if(fim==NULL) fim=ant2;

		while(inter->pai!=NULL && inter->pai->xdir >= x){				//ACHA O NÓ QUE RAMIFICA O CAMINHO XMIN E XMAX
			inter=inter->pai;
		}		

		while(inicio!=inter){

			ant1=inicio;



			if(inicio->xdir >=x && (inicio->xdir + inicio->ldir) <= x+l){
				
				if(inicio->tipo == 1){
					
					auxini = (pQuadra)inicio->dados;

					if(inicio->ydir <= y && (inicio->ydir)-(inicio->hdir) >= y-h){
						mq(auxini,f);																							//ALTERA A COR DESSE ELEMENTO
					}
				}
				

				mrAux(inicio->dir,(x+l),y,h,f);						//ALTERA A COR DA SUBARVORE A DIREITA;					
			}
			inicio=inicio->pai;			
		}

		if(inter->tipo == 1){
			
			auxinter = (pQuadra)inter->dados;

			if((inter->xdir + inter->ldir) <= x+l && inter->ydir <= y && (inter->ydir)-(inter->hdir) >= y-h){
				mq(auxinter,f);				
			}
		}	

		while(fim!=inter){
			
			if(fim->xdir < x+l){
				
				if(fim->tipo == 1){

					auxfim = (pQuadra)fim->dados;

					if(fim->ydir <= y && (fim->ydir)-(fim->hdir) >= y-h){
						mq(auxfim,f);					 	
					}
				}			
				 
				mrAux(fim->esq,x+l,y,h,f);			
			}

			if(fim->xdir == x+l) mrAux(fim->esq,x+l,y,h,f); // SÓ ALTERA A SUBARVORE POIS NAO TERA UM RETANGULO Q COMECE NO LIMITE DO RETANGULO DE BUSCA
			fim=fim->pai;
		}
}

void LimitesSvg(pNo *raiz, FILE *fsvg,int op, double x, double y, double x2, double y2){ 

	if(*raiz==NULL){
		return;
	}

	if(*raiz!=NULL  && (*raiz)->xdir >= x && (*raiz)->xdir + (*raiz)->ldir <= x2 && (*raiz)->ydir >=y  && (*raiz)->ydir + (*raiz)->hdir <= y2){

		LimitesSvg(&(*raiz)->esq,fsvg,op,x,y,x2,y2);	

		if((*raiz)->tipo == 0){
			
			pRetangulo r = (pRetangulo) (*raiz)->dados;
			fprintf(fsvg,"\n<rect x=%c%.2f%c y=%c%.2f%c width=%c%.2f%c height=%c%.2f%c ",34,r->x,34,34,(r->y),34,34, r->l,34,34, r->h,34);
			fprintf(fsvg,"style=%cfill:%s ;fill-opacity:0.5;stroke:black;stroke-width:0.1%c/>",34,r->cor,34); 
		}else{
			if((*raiz)->tipo == 1){

				pQuadra q = (pQuadra) (*raiz)->dados;
				//fprintf(fsvg,"\n<rect x=%c%.2f%c y=%c%.2f%c width=%c%.2f%c height=%c%.2f%c ",34,q->x,34,34,(q->y),34,34, q->l,34,34, q->h,34);
				//fprintf(fsvg,"style=%cfill:white ;fill-opacity:0.1;stroke:white;stroke-width:0.05%c/>",34,34); 

				
				fprintf(fsvg,"\n<rect x=%c%.2f%c y=%c%.2f%c width=%c%.2f%c height=%c%.2f%c ",34,q->x,34,34,(q->y),34,34, q->l,34,34, q->h,34);
				fprintf(fsvg,"style=%cfill:white ;fill-opacity:0.1;stroke:white;stroke-width:0.05%c>",34,34); 
				fprintf(fsvg,"\n</rect>"); 
				fprintf(fsvg,"<text x=%c%.2f%c y=%c%.2f%c font-family=%cVerdana%c font-size=%c10%c fill=%cwhite%c > %s </text>",34,q->x+(q->l)/4,34,34,q->y+(q->h)/2,34,34,34,34,34,34,34,q->cep);
				


			
			}else if((*raiz)->tipo == 2){

				pAux a = (pAux) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cpurple%c />",34,34,34,34);

			}else if((*raiz)->tipo == 3){

				pAux a = (pAux) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cred%c />",34,34,34,34);

			}else if((*raiz)->tipo == 4){
				pAux a = (pAux) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cblue%c />",34,34,34,34);

			}else if((*raiz)->tipo == 5 && op == 1){
				pVertex a = (pVertex) (*raiz)->dados;

				fprintf(fsvg,"\n<circle cx=%c%.2f%c cy=%c%.2f%c r=%c1.3%c stroke=%cblack%c ",34,a->x,34,34,(a->y),34,34,34,34,34);
				fprintf(fsvg,"stroke-width=%c0.1%c fill=%cgreen%c />",34,34,34,34);

			}

		}	

			
		LimitesSvg(&(*raiz)->dir,fsvg,op,x,y,x2,y2);		
	}
}


