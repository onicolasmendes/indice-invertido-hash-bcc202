#include "indiceInvertido.h"
#include "hash.h"
#include <string.h>

// Inicialização do indice invertido - Copia vazio para todas posições
void inicia(IndiceInvertido dic)
{
    int i;
    for (i = 0; i < M; i++)
    {
        memcpy(dic[i].chave, VAZIO, N); // Copia vazio para as chaves
        dic[i].n = 0;
    }
}

int busca(IndiceInvertido dic, Chave chave)
{
    int j = 0;
    int ini = h(chave);

    while ((strcmp(dic[(ini + j) % M].chave, VAZIO) != 0) && (strcmp(dic[(ini + j) % M].chave, chave) != 0) && (j < M)) // Caso em que a posição não está vazia, nem corresponde a chave e quando j é menor que o tamanho da tabela
    {
        j++;
    }

    if (strcmp(dic[(ini + j) % M].chave, chave) == 0) // Caso em que a chave é encontrada na tabela
    {
        return (ini + j) % M; // Retorna a posição
    }

    return -1;
}

bool insereDocumento(IndiceInvertido dic, Chave chave, NomeDocumento doc)
{
    if (busca(dic, chave) == -1) // Caso em que a chave não está no índice invertido
    {
        return false;
    }
    else
    {
        int pos = busca(dic, chave);
        if (dic[pos].n == ND) // Caso em que o numero máximo de documentos foi atingido
        {
            return false;
        }
        strcpy(dic[pos].documentos[dic->n++], doc);
        return true;
    }
}




