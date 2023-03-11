#ifndef HASH_ABERTO
#define HASH_ABERTO
#include "hash.h"
#include <stdbool.h>

/* Os cabeçalhos de todas as funções e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave; //Palavras chave
    NomeDocumento documentos[ND]; //Documentos associados a palavra chave
} Item;

typedef Item IndiceInvertido[M];

/* Funções */

void inicia(IndiceInvertido dic);
void leDocumento(IndiceInvertido dic, int n);
bool insereDocumento(IndiceInvertido, Chave, NomeDocumento);
bool inserePalavraChave(IndiceInvertido, Chave);
int busca(IndiceInvertido, Chave);

int consulta(IndiceInvertido, Chave*, int, NomeDocumento*);
void imprime(IndiceInvertido);

void sort(NomeDocumento*, int);

#endif // !HASH_ABERTO
