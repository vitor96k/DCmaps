#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include "arvore.h"
#include "arvHash.h"
#include "hash.h"
#include "areQuadra.h"
#include "grafo.h"
#include "bd.h"



// ---------------- FUNCA PEGAR NOME DO ARQUIVO ---------------- //
void pegarNome(char *word, char *sair){

	int tamanho=strlen(word);	
	char aux;
	int i=0;
	int k=0;
	int p;	

	tamanho--;			//word[tamanho]=s
	tamanho--;			//word[tamanho]=p
	tamanho--;			//word[tamanho]=o
	tamanho--;			//word[tamanho]=.
	tamanho--;			//word[tamanho]= nome do arquivo;

	while(tamanho>=0 && word[tamanho]!='/'){			//PEGA O NOME DO ARQUIVO
		sair[i]=word[tamanho];
		tamanho--;
		i++;
	}

	sair[i]='\0';	
	i--;
	p=i/2;

	while(i>p){											//COLOCA EM ORDEM
		//printf("\n%d %d",k,i);
		aux=sair[k];
		sair[k]=sair[i];
		sair[i]=aux;
		i--;
		k++;

	}		
}
// ---------------- FUNCAO PEGAR NOME DO ARQUIVO ---------------- //

// ---------------- FUNCAO LIMPAR STRING ---------------- //
void limpar(char *s){

	int i;

	for(i=0;i<strlen(s);i++){
		s[i]= '\0';
	}
}
// ---------------- FUNCAO LIMPAR STRING ---------------- //

int verespacos(char *z){

	int i;
	int c=0;
	for(i=0;i<strlen(z);i++){
		if(z[i]==' ') c++;
	}
	//printf("\nLinha com %d espacos",c);
	return c;
}

char *getVal(char *u, int *k){

	int bo = 0;
	int i=*k;
	char *retorno = (char *)malloc(150*sizeof(char));
	char *r = &retorno[0];

	while(i <strlen(u) && u[i]!=32 && u[i]!='\0' && u[i]!='\n'){
		retorno[bo] = u[i];
		i++;
		bo++;
		*k=*k+1;
	}
	*k=*k+1;
	retorno[bo]= '\0';
	return r;
}

// ---------------- FUNCAO PEGAR REAL DE STRING --------------------//
double getReal(char *s, int *start){

	char num[10];
	int k=0;

	while(s[*start]!=32 && s[*start]!='\0'){

		num[k]=s[*start];
		k++;
		*start=(*start)+1;
	}
	*start=(*start)+1;

	num[k]='\0';
	return (atof(num));
}
// ---------------- FIM FUNCAO PEGAR REAL DE STRING --------------------//


// ---------------- FUNCAO LER PONTOS -------------------- \\
// precisa estar apontando no espaco
float lerpontos(FILE *farq){

			int z=0;
			char aux2;
			char num[10];

			for(aux2=fgetc(farq);(aux2!=32) && (aux2!='\n') && (aux2!=EOF);aux2=fgetc(farq)){
				num[z]=aux2;
				z++;				
			}

			num[z]='\0';			
			return atof(num);
}
// ---------------- FUNCAO LER COR -------------------- \\
// precisa estar apontando no caracter espaco (), le uma string até encontrar um outro espaco
//é chamada de lercor por causa do uso, mas dps é aplicada para ler o sufixo da opcao -o
void lercor(FILE *farq, char *s){

			int z=0;
			char aux2;		
			char cor[15];

			for(aux2=fgetc(farq);(aux2!=32) && (aux2!='\n') && (aux2!=EOF);aux2=fgetc(farq)){
				cor[z]=aux2;
				z++;							
			}

			cor[z]='\0';			
			strcpy(s,cor);		

}
// ---------------- FIM FUNCAO LER COR -------------------- \\




int main(int argc, char *argv[]){

	pNo *raiz = criarArvore();
	pNo *raizVertices = criarArvore();

	phash hashQuadra = criarHash(7919);		//Insere nó (quadra) pelo cep
	phash hashQuadra_Estab = criarHash(7919);		//Insere nó (quadra) pelo TIpo de Estabelecimento
	phash hashAux = criarHash(3);			//Insere nó (quadra) pelo Tipo de Equipamento Urbano
	
	phash hashGrafo = criarHash(7919);			//Insere nó (vertice) pelo ID do vertice 
	phash hashQuadra_byTelefone = criarHash(7919);	//Insere nó (quadra) pelo Telefone do morador;
	phash hashQuadra_byNome = criarHash(7919);	//Insere nó (quadra) pelo Nome do morador;

	inteiro *pathArray;	
	inteiro i2;

	 FILE * fp;
	 char abrirArq[250];
	 char fecharArq[250];
	 char kls[500];
  
	pQuadra q=NULL;
	pRetangulo r=NULL;
	pQuadra auxQ=NULL;

	pNo retornoQuadra=NULL;
	pCasa cas = NULL;
	pNo retornoAux = NULL;
	pNo retornoVertice=NULL;


	int i=1;
	int cinserido=0;	
	int cremovido=0;
	int crecolorido=0;
	int z=0;
	int p;
	int nespaco;
	int auxz;
	int m;
	inteiro m1,m2;
	int op;
	char auxface;
	float ymax=0;
	float xmax=0;
	int marcar = 0;
	double xmeadle=0,ymeadle=0;
	char *comando;

  	double x,y,larg,alt,menorDistancia;

  	double xlim,x2lim,ylim,y2lim; 
  	double distm;

	char *entrada;		//ARQUIVO A SER LIDO
	char *saida;		//PATH DO DIRETORIO PARA SALVAR O RESUMO.TXT E OS .SVG
	char *stemp;		//NOME DO ARQUIVO DE SAIDA, LINKAR COM O NOME DO ARQUIVO QUE ESTA LENDO:
	char *resultado;
	char aux,aux2,faceno;
	char cor[150],cor2[150];
	char num[50];
	char andar[500];
	char nomeOps[150];	//NOME DO ARQUIVO LIDO (.OPS)  
	char nomeOps2[150];	//NOME DO ARQUIVO LIDO (.OPS)  - CONCATENAR: SAIDA, NOMEOPS, .SVG
	char nomeOps3[150];
	char save[200];	    //NOME DO ARQUIVO LIDO (.OPS) CONCATENADO COM - SUFIXO 	
	char *j1,*j2,*j3,*j4,*j5,*j6,*j7,*j8;
	char *dirViario;
	char cop2f;
	char faux;
	unsigned long int contarVertices=0;
	pVertex auxV = NULL;
	pVertex auxV2 = NULL;
	pVertex auxV3 = NULL;
	pEdge auxEd;


	inteiro out,in;
	

	FILE *farquivo;
	FILE *fsvg;
	FILE *fresumo;
	FILE *fviario;
	FILE *printarRota = NULL;

	pNo retorno;

	if(argc==1){
		printf("\nNennhum Comando inserido !");	
		return 0;	
	}else{	
		while(i<argc){

			if(strcmp("-f",argv[i])==0){			 	
				i++; 						
				entrada = (char *)malloc((strlen(argv[i])+1)*sizeof(char));				
				strcpy(entrada,argv[i]);										
			}else{
				if(strcmp("-o",argv[i])==0){					 
					i++;
					saida = (char *)malloc((strlen(argv[i])+2)*sizeof(char));			
					strcpy(saida,argv[i]);
					saida[strlen(saida)]='/';
					saida[strlen(saida)+1]='\0';
					strcpy(nomeOps2,saida);
					strcpy(nomeOps3,nomeOps2);	
					strcpy(abrirArq,saida);	
					strcpy(fecharArq,saida);
				}else if(strcmp("-g",argv[i])==0){
					i++;
					dirViario = (char *)malloc((strlen(argv[i])+1)*sizeof(char));			
					strcpy(dirViario,argv[i]);
					//printf("\nO diretorio ficou: %s",dirViario);
				}
			}

			i++;			
		}
	}

	farquivo=fopen(entrada,"r");

	if(farquivo==NULL){
		return 0;
	}

	pegarNome(entrada,nomeOps);
	strcat(abrirArq,nomeOps);
	strcat(fecharArq,nomeOps);

	strcat(abrirArq,".txt");
	strcat(fecharArq,".svg");
	//printf("\nFICOU: %s",abrirArq);

	fp=fopen(abrirArq,"a");


	//printf("\nLAST SVG: %s",fecharArq);


	

	//----------------- LER ARQUIVO ------------------//	
	
	int posLinha=0;

	// -------------- LER MAPA VIARIO PARA VER COMO CRIAR----------- //

	fviario = fopen(dirViario, "r");

	if(fviario==NULL){
		printf("\nDiretorio do mapa VIARIO invalido");
		return 1;
	}

	resultado=fgets(andar,400,fviario);	
	
	posLinha = 0;	
	contarVertices = 0;
						
	while(resultado!= NULL){
		comando = getVal(resultado,&posLinha);		
		if(strcmp(comando,"v")==0) contarVertices++;		
		resultado=fgets(andar,400,fviario);
		posLinha = 0;
	}

	fclose(fviario);

	// -------------------- Ler arquivo VIA para inserir os elementos no grafo -------------------------------

	fviario = fopen(dirViario, "r");
	resultado=fgets(andar,400,fviario);	

	//printf("\nNumero de vert: %lu",contarVertices);
	pGrafo gr = criarGrafo(contarVertices);


	unsigned long int contV=0;
	
	
						
	while(resultado!= NULL){
		posLinha = 0;	
		comando = getVal(resultado,&posLinha);
		if(strcmp(comando,"v")==0){
			j1 = getVal(resultado,&posLinha);
			x=getReal(resultado,&posLinha);	
			y=getReal(resultado,&posLinha);

			//printf("\nInserir na posicao: %lu",contV);

			pVertex v1 = createVertex(j1,x,y);				//CRIA O VERTICE		
			setValueVertice(gr,contV, v1);					//INSERE O VERTICE NO GRAFO
			retornoVertice = inserir(raizVertices,x,y,0,0,v1,5);		//INSERE O VERTICE NA ARVORE de vertices
			inserir(raiz,x,y,0,0,v1,5);					//INSERE O VERTICE NA ARVORE de TUDO
			insertHash(hashGrafo, j1, retornoVertice);			//INSERE O NÓ DA ARVORE NA HASH

			
			contV++;

		}else if(strcmp(comando,"e")==0){

			j1 = getVal(resultado,&posLinha); // SAIDA
			j2 = getVal(resultado,&posLinha); // ENTRADA
			j3 = getVal(resultado,&posLinha); // CEP ESQUERDA
			j4 = getVal(resultado,&posLinha); // CEP DIREITA
			x = getReal(resultado,&posLinha); // DISTANCIA
			y = getReal(resultado,&posLinha); // TEMPO
			j5 = getVal(resultado,&posLinha); // RUA

			pEdge e1 = createEdge(j1,j2,j3,j4,x,y,j5);

			inteiro sai1 = pegarPosicao(gr,j1);
			inteiro ent1 = pegarPosicao(gr,j2);

			//printf("\nLiga vertice %lu com %lu",sai1,ent1);
			ligarNos(gr, sai1, ent1, x,y);
			setValueAresta(gr,sai1,ent1,e1);	
			//printf("\nout: %s in: %s cepL: %s cepR: %s dis:%.2f tp:%.2f rua:%s",e1->v1,e1->v2,e1->cepL,e1->cepR,e1->distancia,e1->tempo,e1->rua);
		}
		resultado=fgets(andar,400,fviario);
		
	}
	fclose(fviario);

	pathArray = (inteiro *)malloc((contarVertices+1)*sizeof(inteiro));

	for(i2=0;i2<=contarVertices;i2++){
		pathArray[i2]=-1;
	}



	resultado=fgets(andar,400,farquivo);		//PEGA DE LINHA EM LINHA, farquivo é o FILE que aponta para .txt	
						
	while(resultado!= NULL){			// NO FINAL DO WHILE TEM Q TER:  resultado=fgets(andar,400,farquivo);	

		posLinha = 0;				// TODA VEZ QUE LER UMA LINHA NOVA PRECISA INICIAR COM ZERO (GUARDA A INDICE DA LINHA)

		comando = getVal(resultado,&posLinha);	// PEGA A PRIMEIRA STRING DA LINHA QUE VEM ANTES DO ESPACO QUE SERA UM COMANDO
		

		if(strcmp(comando,"r")==0){
			//printf("\nRetangulo");
			x=getReal(resultado,&posLinha);	//PEGA A PROXIMA STRING DA LINHA QUE VEM ANTES DO ESPACO (NESSE CASO VIRAL DOUBLE);
			y=getReal(resultado,&posLinha);	//PEGA A PROXIMA STRING DA LINHA QUE VEM ANTES DO ESPACO (NESSE CASO VIRAL DOUBLE);
			larg=getReal(resultado,&posLinha);	
			alt=getReal(resultado,&posLinha);
			j1 = getVal(resultado,&posLinha);  ///PEGA A PROXIMA STRING DA LINHA QUE VEM ANTES DO ESPACO

			//printf("\n%.2f %.2f %.2f %.2f ",x,y,larg,alt);

			r = criarRetangulo(x,y,larg,alt,j1);
			inserir(raiz,x,y,larg,alt,r,0);

			if(x+larg>xmax) xmax=x+larg;
			if(y>ymax) ymax=y;	
			
		}else if(strcmp(comando,"d")==0){	

			//printf("\nRemocao:");

			x=getReal(resultado,&posLinha);	
			y=getReal(resultado,&posLinha);
			larg=getReal(resultado,&posLinha);
			alt=getReal(resultado,&posLinha);

			fprintf(fp,"\nAntes da remocao %d nós",qtdNos(raiz));
			//printf("\n%.2f %.2f %.2f %.2f ",x,y,larg,alt);

			setDeletePath(raiz, x, y, larg, alt, &cremovido);
			fprintf(fp,"\nDepois da remocao %d nós",qtdNos(raiz));

			fprintf(fp,"\n\n------------------------------------------------------");
			
		}else if(strcmp(comando,"c")==0){

			j1 = getVal(resultado,&posLinha);
			j2 = getVal(resultado,&posLinha);			
			

			if(verespacos(resultado)>3){
				//printf("\nMUDAR COR EM CERTA REGIAO");
				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);
				//printf("\n%s %s %.2f %.2f %.2f %.2f ",j1,j2,x,y,larg,alt);
				defineArea(raiz,j1,j2,x,y,larg,alt,&crecolorido);	


			}else{
				//printf("\nMUDAR COR GERAL");
				//printf("\n%s %s",j1,j2);
				changeAllColors(raiz,j1,j2,&crecolorido);

			}
			
		}else if(strcmp(comando,"q")==0){	
				//printf("\nQUADRA");
				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);
				j1 = getVal(resultado,&posLinha);
				//printf("\n%.2f %.2f %.2f %.2f %s ",x,y,larg,alt,j1);

				q = criarQuadra(x,y,larg,alt,j1);
				retornoQuadra = inserir(raiz,x,y,larg,alt,q,1);
				insertHash(hashQuadra, j1, retornoQuadra);

				if(x+larg>xmax) xmax=x+larg;
				if(y>ymax) ymax=y;	
			
		}else if(strcmp(comando,"m")==0){	
			//cep face num nome fone
			j1 = getVal(resultado,&posLinha);
			j2 = getVal(resultado,&posLinha);
			j3 = getVal(resultado,&posLinha);
			j4 = getVal(resultado,&posLinha);
			j5 = getVal(resultado,&posLinha);

			//printf("\nCEP: %s Face: %c Num: %s Nome: %s Tel: %s ",j1,j2[0],j3,j4,j5);

			retornoQuadra = (pNo) getHash(hashQuadra,j1); //PEGA O PONTEIRO DO NÓ QUE TEM A QUADRA



			if(retornoQuadra==NULL){
				//printf("\nNao existe uma quadra com cep %s",j1);

			}else{
				//printf("\nQuadra Encontrada para ser inserido a CASA");
				cas = criarCasa(j2[0],j3,j4,j5);    //CRIA A CASA	
				auxQ = (pQuadra) getInfo(retornoQuadra);  // PEGA A QUADRA QUE ESTA NO NÓ
				ligarCasa(auxQ,cas);
				insertHash(hashQuadra_byTelefone,j5,retornoQuadra);
				insertHash(hashQuadra_byNome,j4,retornoQuadra);
				//printf("\nCRIADO");
			}
			
			
		}else if(strcmp(comando,"e")==0){

			//cep face num tp nome f 

			j1 = getVal(resultado,&posLinha);
			j2 = getVal(resultado,&posLinha);
			j3 = getVal(resultado,&posLinha);
			j4 = getVal(resultado,&posLinha);
			j5 = getVal(resultado,&posLinha);
			j6 = getVal(resultado,&posLinha);

			//printf("\nCEP: %s Face: %c Num: %s Tipo: %s Nome: %s Telefone: %s ",j1,j2[0],j3,j4,j5,j6);	

			retornoQuadra = (pNo) getHash(hashQuadra,j1);

			if(retornoQuadra==NULL){
				//printf("\nNao existe uma quadra com cep %s",cor);
			}else{
				//printf("\nQuadra Encontrada para ser inserido o ESTABELECIMENTO");
				pComercio com = criarComercio(j2[0], j3, j4, j5,j6);    
	
				pQuadra auxQ = (pQuadra) getInfo(retornoQuadra);  // PEGA A QUADRA QUE ESTA NO NÓ
				ligarComercio(auxQ,com);

				//ATÉ AQUI ELE BUSCOU A QUADRA NA HASH (BY CEP) A QUADRA E LIGOU O ESTABELECIMENTO
				// O CÓDIGO ABAIXO É PARA FAZER UMA HASH DE QUADRAS (BY ESTABELECIMENTO)
				//ASSIM OS ESTABELECIMENTOS DO MESMO TIPO OCUPARAO O MESMO INDICE

				//printf("\nInserir QUADRA usando a hash de QUADRA by ESTAB");
				insertHash2(hashQuadra_Estab, j4, retornoQuadra,j1);

			}
			
		}else if(strcmp(comando,"h")==0){	

			j1 = getVal(resultado,&posLinha);
			x=getReal(resultado,&posLinha);	
			y=getReal(resultado,&posLinha);

			pAux pa = criarAux(j1,x,y);
			retornoAux = inserir(raiz,x,y,0,0,pa,3);
			insertHash(hashAux, "3", retornoAux);

			if(x+larg>xmax) xmax=x+larg;
			if(y>ymax) ymax=y;

			//printf("\nID: %s x:%.2f y:%.2f",j1,x,y);
			
		}else if(strcmp(comando,"s")==0){	

			j1 = getVal(resultado,&posLinha);
			x=getReal(resultado,&posLinha);	
			y=getReal(resultado,&posLinha);

			pAux pa = criarAux(j1,x,y);
			retornoAux= inserir(raiz, x, y,0,0,pa,2);
			insertHash(hashAux, "2", retornoAux);	

			if(x+larg>xmax) xmax=x+larg;
			if(y>ymax) ymax=y;

			//printf("\nID: %s x:%.2f y:%.2f",j1,x,y);
			
		}else if(strcmp(comando,"t")==0){

			j1 = getVal(resultado,&posLinha);
			x=getReal(resultado,&posLinha);	
			y=getReal(resultado,&posLinha);

			pAux pa = criarAux(j1,x,y);
			retornoAux= inserir(raiz, x, y,0,0,pa,4);
			insertHash(hashAux, "4", retornoAux);	

			//printf("\nID: %s x:%.2f y:%.2f",j1,x,y);	
			
		}else if(strcmp(comando,"mq?")==0){

			j1 = getVal(resultado,&posLinha);	
			//printf("\nCEP: %s",j1);

			fprintf(fp,"\nComando: mq? %s",j1);

			retornoQuadra = (pNo) getHash(hashQuadra,j1);

			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra);
				mq(auxQ,fp);											
			}else //printf("\nNao existe a quadra com cep %s",cor);

			fprintf(fp,"\n\n------------------------------------------------------");
			
		}else if(strcmp(comando,"mr?")==0){

				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);	

				fprintf(fp,"\nComando: mr? %.2f %.2f %.2f %.2f ",x,y,larg,alt);

				mr(raiz,x,y,larg,alt,fp);
				fprintf(fp,"\n\n------------------------------------------------------");
			
		}else if(strcmp(comando,"et?")==0){	

			j1 = getVal(resultado,&posLinha);	

			if(verespacos(resultado)>3){
				//printf("\nET COM RESTRICAO");
				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);

				fprintf(fp,"\nComando: et? %s %.2f %.2f %.2f %.2f",j1,x,y,larg,alt);	
				et2(hashQuadra_Estab,j1,x,y,larg,alt,fp);
				fprintf(fp,"\n\n------------------------------------------------------");
			}else{
				//printf("\nET SEM RESTRICAO");
				fprintf(fp,"\nComando: et? %s",j1);	
				et(hashQuadra_Estab,j1,fp);
				fprintf(fp,"\n\n------------------------------------------------------");
			}
			
		}else if(strcmp(comando,"ed?")==0){

			j1 = getVal(resultado,&posLinha);			

			if(verespacos(resultado)>3){
				//printf("\nED COM RESTRICAO");
				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);

				fprintf(fp,"\nComando: ed? %s %.2f %.2f %.2f %.2f",j1,x,y,larg,alt);
				ed2(hashQuadra_Estab,j1,x,y,larg,alt,fp);
				fprintf(fp,"\n\n------------------------------------------------------");	
			}else{
				//printf("\nED SEM RESTRICAO");
				fprintf(fp,"\nComando: ed? %s",j1);	
				ed(hashQuadra_Estab,j1,fp);	
				fprintf(fp,"\n\n------------------------------------------------------");
			}	
			
		}else if(strcmp(comando,"h?")==0){	

				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);
				fprintf(fp,"\nComando: h? %.2f %.2f %.2f %.2f",x,y,larg,alt);
				searchAux(hashAux,"3",x,y,larg,alt,fp);
				fprintf(fp,"\n\n------------------------------------------------------");
				
			
		}else if(strcmp(comando,"s?")==0){

				x=getReal(resultado,&posLinha);	
				y=getReal(resultado,&posLinha);
				larg=getReal(resultado,&posLinha);
				alt=getReal(resultado,&posLinha);
				fprintf(fp,"\nComando: s? %.2f %.2f %.2f %.2f",x,y,larg,alt);
				searchAux(hashAux,"2",x,y,larg,alt,fp);
				fprintf(fp,"\n\n------------------------------------------------------");


			
		}else if(strcmp(comando,"hq?")==0){

			j1 = getVal(resultado,&posLinha);
			larg=getReal(resultado,&posLinha);	

			fprintf(fp,"\nComando: hq? %s %.2f",j1,larg);
			hq(hashQuadra,j1, larg,hashAux,"3",fp);
			fprintf(fp,"\n\n------------------------------------------------------");
			
		}else if(strcmp(comando,"qt?")==0){	
			fprintf(fp,"\nComando: qt? %s %.2f",j1,larg);
			qt(*raiz, hashAux,fp);		
			fprintf(fp,"\n\n------------------------------------------------------");	
		}
		else if(strcmp(comando,"o")==0){	

			j1 = getVal(resultado,&posLinha);

			pegarNome(entrada,nomeOps);

			strcpy(nomeOps2,saida);
			strcat(nomeOps2,nomeOps);
			strcat(nomeOps2,"-");									
			strcat(nomeOps2,j1);
			strcat(nomeOps2,".svg");

			//printf("\nNome ficou: %s",nomeOps2);
			gerarSvg(raiz,nomeOps2,xmax+2,ymax+2,0);
			limpar(nomeOps);
			limpar(nomeOps2);			
		}else if(strcmp(comando,"pfe?")==0){

			j5 = getVal(resultado,&posLinha);	// DISTANCIA OU TEMPO (D | T)
			j6 = getVal(resultado,&posLinha);	// TEXTO OU IMAGEM (t | p)
			j7 = getVal(resultado,&posLinha);	// SUFIXO

			if(strcmp(j5,"D")==0) op = 1;
			else op =2;

			//printf("\nOpcao: %d",op);

			pegarNome(entrada,nomeOps);	//PEGA O NOME DO ARQUIVO .OPS
			strcpy(nomeOps3,saida);		//PEGA O PATH COM BARRA
			//printf("\nPath: %s",nomeOps3);
			//printf("\nNome do arquivo: %s",nomeOps);
			strcat(nomeOps3,nomeOps);		//PATH + NOME DO ARQUIVO
			strcat(nomeOps3,"-");									
			strcat(nomeOps3,j7);

			if(strcmp(j6,"t")==0) strcat(nomeOps3,".txt");
			else strcat(nomeOps3,".svg");

			//printf("Path Completo: %s",nomeOps3);
			//strcat(nomeOps2,".svg");			


			j1 = getVal(resultado,&posLinha);	//FONE
			j2 = getVal(resultado,&posLinha);	//CEP
			j3 = getVal(resultado,&posLinha);	//FACE
			j4 = getVal(resultado,&posLinha);   //NUM

			//printf("\nComando: pfe? %s %s %s %s ",j1,j2,j3,j4);	
			//printf("\nBasico: %s %s %s ",j5,j6,j7);	

			retornoQuadra = NULL;
			retornoQuadra = (pNo) getHash(hashQuadra_byTelefone,j1); 

			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra);				
				if(auxQ!=NULL){

					auxface = getFaceMorador(auxQ,j1);	// PEGA A FACE DO MORADOR COM TAL TELEFONE
					//printf("\nQuadra: x:%.2f y:%.2f l:%.2f h:%.2f, face: %c",auxQ->x,auxQ->y,auxQ->l,auxQ->h,auxface);			
					setPoint(auxQ, auxface, &xmeadle, &ymeadle);	

					menorDistancia = -1;			
					findCloser(raizVertices,xmeadle, ymeadle, &menorDistancia,kls);			
				

					if(kls!=NULL){			//RETORNA O ID NO NÓ
						retornoVertice =NULL;
						retornoVertice = getHash(hashGrafo,kls);
						if(retornoVertice!=NULL){					
							auxV = (pVertex)getInfo(retornoVertice);							
							if(auxV!=NULL){						
						 		out = pegarPosicao(gr, auxV->id);
						 		//printf("\nSaida: %s %lu %.2f %.2f",kls,out,auxV->x,auxV->y);
							}
						}
					}else printf("\nNao tem nada perto");
				}
			}else printf("\nNOT FOUND IN HASH");

			retornoQuadra = NULL;
			retornoQuadra = (pNo) getHash(hashQuadra,j2); 

			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra);
				if(auxQ!=NULL){

					 //printf("\nQuadra: x:%.2f y:%.2f l:%.2f h:%.2f, face:%c",auxQ->x,auxQ->y,auxQ->l,auxQ->h, j3[0]);
			
					setPoint(auxQ, j3[0], &xmeadle, &ymeadle);			
					menorDistancia = -1;			
					findCloser(raizVertices,xmeadle, ymeadle, &menorDistancia,kls);
					//printf("\na menor distancia ficou: %.2f",menorDistancia);

					if(kls!=NULL){			//RETORNA O ID NO NÓ

						retornoVertice =NULL;
						retornoVertice = getHash(hashGrafo,kls);
						if(retornoVertice!=NULL){					
							auxV = (pVertex)getInfo(retornoVertice);
							if(auxV!=NULL){						
						 		in = pegarPosicao(gr, auxV->id);
						 		//printf("\nEntrada: %s %lu %.2f %.2f",kls, in, auxV->x,auxV->y);
						 		printf("\n----------------------- DIJKSTRA ----------------------- \n");
						 		pilha *p = dijkstra (gr, out, in, op);

						 		printarRota=fopen(nomeOps3,"w");

						 		


								if(strcmp(j6,"t")==0){

									fprintf(printarRota,"Comando: pfe? %s %s %s %s\n",j1,j2,j3,j4);	

									while(p!= NULL && p->prox!=NULL){

										auxV3 = (pVertex) getValueVertice(gr, p->indice);
										m1 = p->indice;
										p = p->prox;	
										auxV2 = (pVertex) getValueVertice(gr, p->indice);	
										m2 = p->indice;										

										auxEd = (pEdge) getValueAresta(gr, m1, m2);

										if(auxEd!=NULL) fprintf(printarRota,"Siga ao %c a rua %s por %.2f metros\n",direction(auxV3,auxV2),auxEd->rua,auxEd->distancia);																				
										
									}

									auxEd = (pEdge) getValueAresta(gr, m2, in);
									if(auxEd!=NULL) fprintf(printarRota,"Siga ao %c a rua %s por %.2f metros\n",direction(auxV3,auxV2),auxEd->rua,auxEd->distancia);																				

									fprintf(printarRota,"Voce chegou o local !");



								}else{
									fprintf(printarRota,"<svg width=%c%.2f%c height=%c%.2f%c xmlns=%chttp://www.w3.org/2000/svg%c>",34,xmax*1.2,34,34,(1.2*ymax),34,34,34);
									auxSvg(raiz,printarRota,ymax,0);

									while(p!= NULL && p->prox!=NULL){

										auxV3 = (pVertex) getValueVertice(gr, p->indice);
										p = p->prox;	
										auxV2 = (pVertex) getValueVertice(gr, p->indice);									
										fprintf(printarRota,"\n  <line x1=%c%.2f%c y1=%c%.2f%c x2=%c%.2f%c y2=%c%.2f%c style=%cstroke:rgb(255,255,0);stroke-width:2%c />",34,auxV3->x,34,34,auxV3->y,34,34,auxV2->x,34,34,auxV2->y,34,34,34);
										

										//printf("\nIndice: %lu", p->indice);
										
									}

									fprintf(printarRota,"\n  <line x1=%c%.2f%c y1=%c%.2f%c x2=%c%.2f%c y2=%c%.2f%c style=%cstroke:rgb(255,255,0);stroke-width:2%c />",34,auxV2->x,34,34,auxV2->y,34,34,auxV->x,34,34,auxV->y,34,34,34);

									fprintf(printarRota,"\n</svg>");	
									fclose(printarRota);

								}					

													 		
							}
						}
					}else printf("\nNao tem nada perto");
				}

				limpar(nomeOps);
				limpar(nomeOps3);	
			}




		}else if(strcmp(comando,"pnn?")==0){

			j5 = getVal(resultado,&posLinha);	// DISTANCIA OU TEMPO (D | T)
			j6 = getVal(resultado,&posLinha);	// TEXTO OU IMAGEM (t | p)
			j7 = getVal(resultado,&posLinha);	// SUFIXO

			if(strcmp(j5,"D")==0) op = 1;
			else op =2;

			pegarNome(entrada,nomeOps);	//PEGA O NOME DO ARQUIVO .OPS
			strcpy(nomeOps3,saida);		//PEGA O PATH COM BARRA
			strcat(nomeOps3,nomeOps);		//PATH + NOME DO ARQUIVO
			strcat(nomeOps3,"-");									
			strcat(nomeOps3,j7);

			if(strcmp(j6,"t")==0) strcat(nomeOps3,".txt");
			else strcat(nomeOps3,".svg");

			//printf("Path Completo: %s",nomeOps3);			

			j1 = getVal(resultado,&posLinha);	//NOME1
			j2 = getVal(resultado,&posLinha);	//NOME2

			//printf("\nComando pnn? %s %s",j1,j2);

			retornoQuadra = NULL;
			retornoQuadra = (pNo) getHash(hashQuadra_byNome,j1); 

			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra);				
				if(auxQ!=NULL){

					auxface = getFaceMoradorNome(auxQ,j1);	//RETORNA A FACE PELO NOME DO MORADOR
					//printf("\nQuadra: x:%.2f y:%.2f l:%.2f h:%.2f, face: %c",auxQ->x,auxQ->y,auxQ->l,auxQ->h,auxface);			
					setPoint(auxQ, auxface, &xmeadle, &ymeadle);	

					menorDistancia = -1;			
					findCloser(raizVertices,xmeadle, ymeadle, &menorDistancia,kls);
					if(kls!=NULL){			//RETORNA O ID NO NÓ
						retornoVertice =NULL;
						retornoVertice = getHash(hashGrafo,kls);
						if(retornoVertice!=NULL){					
							auxV = (pVertex)getInfo(retornoVertice);							
							if(auxV!=NULL){						
						 		out = pegarPosicao(gr, auxV->id);
						 		//printf("\nSaida: %s %lu %.2f %.2f",kls,out,auxV->x,auxV->y);
							}
						}
					}else printf("\nNao tem nada perto");
				}
			}else printf("\nNOT FOUND IN HASH");

			retornoQuadra = NULL;
			retornoQuadra = (pNo) getHash(hashQuadra_byNome,j2); 

			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra);				
				if(auxQ!=NULL){

					auxface = getFaceMoradorNome(auxQ,j2);
					//printf("\nQuadra: x:%.2f y:%.2f l:%.2f h:%.2f, face: %c",auxQ->x,auxQ->y,auxQ->l,auxQ->h,auxface);			
					setPoint(auxQ, auxface, &xmeadle, &ymeadle);	

					menorDistancia = -1;			
					findCloser(raizVertices,xmeadle, ymeadle, &menorDistancia,kls);
					if(kls!=NULL){			//RETORNA O ID NO NÓ
						retornoVertice =NULL;
						retornoVertice = getHash(hashGrafo,kls);
						if(retornoVertice!=NULL){					
							auxV = (pVertex)getInfo(retornoVertice);							
							if(auxV!=NULL){						
						 		in = pegarPosicao(gr, auxV->id);
						 		//printf("\nEntrada: %s %lu %.2f %.2f",kls,in,auxV->x,auxV->y);
						 		printf("\n----------------------- DIJKSTRA ----------------------- \n");	

						 		pilha *p = dijkstra (gr, out, in, op);

						 		printarRota=fopen(nomeOps3,"w");

						 		xlim=-1;
						 		x2lim=-1;
						 		ylim=-1;
						 		y2lim=-1;



								if(strcmp(j6,"t")==0){

									fprintf(printarRota,"Comando pnn? %s %s\n",j1,j2);

									while(p!= NULL && p->prox!=NULL){

										auxV3 = (pVertex) getValueVertice(gr, p->indice);										

										m1 = p->indice;
										p = p->prox;	
										auxV2 = (pVertex) getValueVertice(gr, p->indice);	
										m2 = p->indice;										

										auxEd = (pEdge) getValueAresta(gr, m1, m2);

										if(auxEd!=NULL) fprintf(printarRota,"Siga ao %c a rua %s por %.2f metros\n",direction(auxV3,auxV2),auxEd->rua,auxEd->distancia);	
										
									}

									auxEd = (pEdge) getValueAresta(gr, m2, in);
									if(auxEd!=NULL) fprintf(printarRota,"Siga ao %c a rua %s por %.2f metros\n",direction(auxV3,auxV2),auxEd->rua,auxEd->distancia);																				

									fprintf(printarRota,"Voce chegou o local !");


								}else{

									fprintf(printarRota,"<svg width=%c%.2f%c height=%c%.2f%c xmlns=%chttp://www.w3.org/2000/svg%c>",34,xmax*1.2,34,34,(1.2*ymax),34,34,34);
									auxSvg(raiz,printarRota,ymax,0);

									while(p!= NULL && p->prox!=NULL){

										auxV3 = (pVertex) getValueVertice(gr, p->indice);
										p = p->prox;	
										auxV2 = (pVertex) getValueVertice(gr, p->indice);									
										fprintf(printarRota,"\n  <line x1=%c%.2f%c y1=%c%.2f%c x2=%c%.2f%c y2=%c%.2f%c style=%cstroke:rgb(255,255,0);stroke-width:2%c />",34,auxV3->x,34,34,auxV3->y,34,34,auxV2->x,34,34,auxV2->y,34,34,34);
										

										//printf("\nIndice: %lu", p->indice);
										
									}

									fprintf(printarRota,"\n  <line x1=%c%.2f%c y1=%c%.2f%c x2=%c%.2f%c y2=%c%.2f%c style=%cstroke:rgb(255,255,0);stroke-width:2%c />",34,auxV2->x,34,34,auxV2->y,34,34,auxV->x,34,34,auxV->y,34,34,34);

									fprintf(printarRota,"\n</svg>");	
									fclose(printarRota);

								}

						 		

								
							}
						}
					}else printf("\nNao tem nada perto");

					limpar(nomeOps);
					limpar(nomeOps3);	
				}
			}else printf("\nNOT FOUND IN HASH");
			

		}else if(strcmp(comando,"pet?")==0){


			j5 = getVal(resultado,&posLinha);	// DISTANCIA OU TEMPO (D | T)
			j6 = getVal(resultado,&posLinha);	// TEXTO OU IMAGEM (t | p)
			j7 = getVal(resultado,&posLinha);	// SUFIXO

			if(strcmp(j5,"D")==0) op = 1;
			else op =2;

			pegarNome(entrada,nomeOps);	//PEGA O NOME DO ARQUIVO .OPS
			strcpy(nomeOps3,saida);		//PEGA O PATH COM BARRA
			strcat(nomeOps3,nomeOps);		//PATH + NOME DO ARQUIVO
			strcat(nomeOps3,"-");									
			strcat(nomeOps3,j7);

			if(strcmp(j6,"t")==0) strcat(nomeOps3,".txt");
			else strcat(nomeOps3,".svg");

			//printf("Path Completo: %s",nomeOps3);

			
			j1 = getVal(resultado,&posLinha);	//cep
			j2 = getVal(resultado,&posLinha);	//Face
			j3 = getVal(resultado,&posLinha);	//num
			j4 = getVal(resultado,&posLinha);      //tipo

			//printf("\nComando: pet? %s %s %s %s ",j1,j2,j3,j4);

			retornoQuadra = NULL;
			retornoQuadra = (pNo) getHash(hashQuadra,j1); 

			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra);
				if(auxQ!=NULL){

					 //printf("\nQuadra: x:%.2f y:%.2f l:%.2f h:%.2f, face:%c",auxQ->x,auxQ->y,auxQ->l,auxQ->h, j2[0]);
			
					setPoint(auxQ, j2[0], &xmeadle, &ymeadle);			
					menorDistancia = -1;			
					findCloser(raizVertices,xmeadle, ymeadle, &menorDistancia,kls);
					//printf("\na menor distancia ficou: %.2f",menorDistancia);

					if(kls!=NULL){			//RETORNA O ID NO NÓ

						retornoVertice =NULL;
						retornoVertice = getHash(hashGrafo,kls);
						if(retornoVertice!=NULL){					
							auxV = (pVertex)getInfo(retornoVertice);
							if(auxV!=NULL){						
						 		out = pegarPosicao(gr, auxV->id);
						 		//printf("\nSaida: %s %lu %.2f %.2f",kls, out, auxV->x,auxV->y);
							}
						}
					}else printf("\nNao tem nada perto");
				}
			}

			retornoQuadra = getHash(hashQuadra_Estab,j4);
			if(retornoQuadra!=NULL){
				auxQ = (pQuadra) getInfo(retornoQuadra); 	//QUADRA Q ESTA O ESTABELICIMENTO
				if(auxQ!=NULL){
					
					 faux = getFaceEstab(auxQ, j4);
					// printf("\nQuadra: x:%.2f y:%.2f l:%.2f h:%.2f, face:%c",auxQ->x,auxQ->y,auxQ->l,auxQ->h,faux);
					
					 setPoint(auxQ, faux, &xmeadle, &ymeadle);						
					menorDistancia = -1;			
					findCloser(raizVertices,xmeadle, ymeadle, &menorDistancia,kls);
					

					if(kls!=NULL){			//RETORNA O ID NO NÓ

						retornoVertice =NULL;
						retornoVertice = getHash(hashGrafo,kls);
						if(retornoVertice!=NULL){					
							auxV = (pVertex)getInfo(retornoVertice);
							if(auxV!=NULL){						
						 		in = pegarPosicao(gr, auxV->id);
						 		//printf("\nEntrada: %s %lu %.2f %.2f",kls,in, auxV->x,auxV->y);	
						 		printf("\n----------------------- DIJKSTRA ----------------------- \n");

								pilha *p = dijkstra (gr, out, in, op);

						 		printarRota=fopen(nomeOps3,"w");


								if(strcmp(j6,"t")==0){

									fprintf(printarRota,"Comando: pet? %s %s %s %s\n",j1,j2,j3,j4);

									while(p!= NULL && p->prox!=NULL){

										auxV3 = (pVertex) getValueVertice(gr, p->indice);
										m1 = p->indice;
										p = p->prox;	
										auxV2 = (pVertex) getValueVertice(gr, p->indice);	
										m2 = p->indice;										

										auxEd = (pEdge) getValueAresta(gr, m1, m2);

										if(auxEd!=NULL) fprintf(printarRota,"Siga ao %c a rua %s por %.2f metros\n",direction(auxV3,auxV2),auxEd->rua,auxEd->distancia);																				
										
									}

									auxEd = (pEdge) getValueAresta(gr, m2, in);
									if(auxEd!=NULL) fprintf(printarRota,"Siga ao %c a rua %s por %.2f metros\n",direction(auxV3,auxV2),auxEd->rua,auxEd->distancia);																				

									fprintf(printarRota,"Voce chegou o local !");


								}else{

									fprintf(printarRota,"<svg width=%c%.2f%c height=%c%.2f%c xmlns=%chttp://www.w3.org/2000/svg%c>",34,xmax*1.2,34,34,(1.2*ymax),34,34,34);
									auxSvg(raiz,printarRota,ymax,0);

									while(p!= NULL && p->prox!=NULL){

										auxV3 = (pVertex) getValueVertice(gr, p->indice);
										p = p->prox;	
										auxV2 = (pVertex) getValueVertice(gr, p->indice);									
										fprintf(printarRota,"\n  <line x1=%c%.2f%c y1=%c%.2f%c x2=%c%.2f%c y2=%c%.2f%c style=%cstroke:rgb(255,255,0);stroke-width:2%c />",34,auxV3->x,34,34,auxV3->y,34,34,auxV2->x,34,34,auxV2->y,34,34,34);
										

										//printf("\nIndice: %lu", p->indice);
										
									}

									fprintf(printarRota,"\n  <line x1=%c%.2f%c y1=%c%.2f%c x2=%c%.2f%c y2=%c%.2f%c style=%cstroke:rgb(255,255,0);stroke-width:2%c />",34,auxV2->x,34,34,auxV2->y,34,34,auxV->x,34,34,auxV->y,34,34,34);

									fprintf(printarRota,"\n</svg>");	
									fclose(printarRota);

								}					 			
														
							}
						}
					}else printf("\nNao tem nada perto");		
					limpar(nomeOps);
					limpar(nomeOps3);				
				}
			}
			


		}else if(strcmp(comando,"qer?")==0){

			j1 = getVal(resultado,&posLinha);	//NOME DA RUA
			j2 = getVal(resultado,&posLinha);	//TIPO DO ESTABELECIMENTO

			fprintf(fp,"Comando qer? %s %s\n",j1,j2);
			printEstab_daRua(gr, hashQuadra, j1, j2, fp);
			fprintf(fp,"\n\n------------------------------------------------------");
		}

		resultado=fgets(andar,400,farquivo);	
	}

	// ------------- GERAR SVG DAS CASAS ---------------- //

	fclose(farquivo);	
	fclose(fp);
	gerarSvg(raiz,fecharArq,xmax*1.2,ymax*1.2,1);

	// ------------- GERAR SVG DAS CASAS ---------------- //

	printf("\n");	
	return 1;
	
}