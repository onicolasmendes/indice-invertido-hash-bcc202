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

void leDocumento(IndiceInvertido dic, int n, int *);

bool insereDocumento(IndiceInvertido, Chave, NomeDocumento);

bool inserePalavraChave(IndiceInvertido, Chave, int *);

void vazioTodosDocumentos(NomeDocumento *documentos);

int busca(IndiceInvertido, Chave);

void leOpcao(char *c, Chave *chaves, int *qtdChaves);

void selecionaNaoVazio(NomeDocumento *origem, NomeDocumento *destino, int *qtd);

void ordena(NomeDocumento *documentos, int inicio, int fim);

void imprimeResultadoBusca(NomeDocumento *documentos, int tamNaoVazio);

void consulta(IndiceInvertido, Chave*, int, NomeDocumento*);

void imprime(IndiceInvertido);

//void sort(NomeDocumento*, int);

void imprimeColisoes(int);

void imprimeMemoria();

#endif // !HASH_ABERTO
