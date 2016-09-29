#ifndef _ARVHASH
#define _ARVHASH

void et(void *h, char *key,FILE *f);
void et2(void *h, char *key,double x,double y,double l ,double alt,FILE *f);
void ed(void *h, char *key,FILE *f);
void ed2(void *h, char *key,double x,double y,double l ,double alt,FILE *f);
void searchAux(void *h, char *key,double x,double y,double l ,double alt,FILE *f);
void hq(void *h, char *key, double l,void *h2, char *key2, FILE *f);
void qt(void *arvore, void *hash,FILE *f);
#endif