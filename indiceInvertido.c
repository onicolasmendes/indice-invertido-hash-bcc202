#include "indiceInvertido.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>

// Inicialização do indice invertido - Copia vazio para todas posições
void inicia(IndiceInvertido dic)
{
    int i;
    for (i = 0; i < M; i++)
    {
        strcpy(dic[i].chave, VAZIO); // Copia vazio para as chaves
        dic[i].n = 0;
    }
}

void leDocumento(IndiceInvertido dic, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Leitura da linha
        char str[MAX_STR];
        fgets(str, MAX_STR, stdin);
        int tam = strlen(str);
        str[tam - 1] = '\0';
        // Tokenização da string
        char *aux = strtok(str, " ");

        // Nome do documento
        char nomeDocumento[D];
        int qtdPalavras = 0;

        // Inserções
        while (aux != NULL)
        {
            if (qtdPalavras == 0) //Nome do documentos
            {
                strcpy(nomeDocumento, aux);
                qtdPalavras++;
                printf("%s\n", nomeDocumento);
            }
            else //Palavras chaves associadas ao documento
            {
                // Insere as palavras chaves e o nome do documento associado
                inserePalavraChave(dic, aux);
                insereDocumento(dic, aux, nomeDocumento);

                printf("%s\n", aux);
            }
            
            aux = strtok(NULL, " ");
        }
    }
    return;
}

bool inserePalavraChave(IndiceInvertido dic, Chave chave)
{
    // Caso em que a chave já está no TAD
    if (busca(dic, chave) != -1)
    {
        return false;
    }
    // Caso em que a chave não está no TAD
    int j = 0;
    int ini = h(chave);
    while ((strcmp(dic[(ini + j) % M].chave, VAZIO) != 0) && (j < M)) // Busca a posição disponível
    {
        j++;
    }

    if (j < M) // Verifica se a posição é válida
    {
        // Inserção da chave
        strcpy(dic[(ini + j) % M].chave, chave);
        return true;
    }

    return false;
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
