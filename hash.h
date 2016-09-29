#ifndef _HASH
#define _HASH

typedef struct hash hash;
typedef struct hash * phash;
typedef struct lista lista;
typedef struct lista * pLista;

pLista getInfoHash(phash a,unsigned long int z);		// RETORNA A STRUCT LISTA
pLista getProxHash(pLista a);
void *getDadoHash(pLista a);					// RETORNA A GOROBA Q ESTA NA STRUCT LISTA

phash criarHash(int n);
void insertHash(phash a, char *chave, void *p);
unsigned long int funcao(phash a, char *chave);
void *getHash(phash a, char *chave);
void removeHash(phash a, char *chave);

void insertHash2(phash a, char *chave, void *p, char *id);
#endif

