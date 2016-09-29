#ifndef _MATRIZ
#define _MATRIZ

//Cria um matriz quadrada (n*n)
double **criarMatriz(unsigned long int n);

//Atribui um valor para a posicao m[i][j];
void setMatriz(double **m,unsigned long int i, unsigned long int j, double valor);

//Retorna o valor da matriz m[i][j]
double getMatriz(double **m,unsigned long int i, unsigned long int j);

//Retorna a linha do menor valor da coluna n
unsigned long int ColOfLessLine (double **m, unsigned long int size, unsigned long int l);

//Imprime os valores de uma linha da matriz;
void printLine(double **m, unsigned long int size,unsigned long int l);

//Procura as posicoes da matriz que possuem valor 0
void catchZero(double **mat, unsigned long int size);





#endif