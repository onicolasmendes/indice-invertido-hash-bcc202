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

        // Remove o \n
        str[strcspn(str, "\n")] = 0;

        // Tokenização da string
        char *aux = strtok(str, " ");

        // Nome do documento
        char nomeDocumento[D];
        int qtdPalavras = 0;

        // Inserções
        while (aux != NULL)
        {
            if (qtdPalavras == 0) // Nome do documentos
            {
                strcpy(nomeDocumento, aux);
                qtdPalavras++;
            }
            else // Palavras chaves associadas ao documento
            {
                // Insere as palavras chaves e o nome do documento associado
                inserePalavraChave(dic, aux);
                insereDocumento(dic, aux, nomeDocumento);
                // printf("%s\n", aux);
                qtdPalavras++;
            }

            aux = strtok(NULL, " ");
        }
    }
}

bool inserePalavraChave(IndiceInvertido dic, Chave chave)
{
    // Caso em que a chave já está no TAD
    int pos = busca(dic, chave);
    if (pos != -1)
    {
        if ((strcmp(dic[pos].chave, chave) == 0)) // Caso em que a posição possui a chave identica passada pelo parâmetro
        {
            return false;
        }
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

    int pos = busca(dic, chave);
    if (dic[pos].n == ND) // Caso em que o numero máximo de documentos foi atingido
    {
        return false;
    }
    strcpy(dic[pos].documentos[dic[pos].n], doc);
    dic[pos].n++;
    return true;
}

void imprime(IndiceInvertido dic)
{
    for (int i = 0; i < M; i++)
    {
        if (strcmp(dic[i].chave, VAZIO) != 0)
        {
            printf("%s -", dic[i].chave);
            for (int j = 0; j < dic[i].n; j++)
            {
                printf(" %s", dic[i].documentos[j]);
            }
            printf("\n");
        }
    }
}

void consulta(IndiceInvertido dic, Chave *chaves, int n, NomeDocumento *resultados)
{

    for (int i = 0; i < n; i++)
    {
        int pos = 0;
        for (int j = 0; j < M; j++)
        {
            if (i == 0) // Caso da primeira palavra-chave pesquisada
            {
                if (strcmp(dic[j].chave, chaves[i]) == 0) // Insere os documentos que possuem a palavra chave associadas
                {
                    for (int k = 0; k < dic[j].n; k++) // Passa todos os documentos pro vetor
                    {
                        strcpy(resultados[pos], dic[j].documentos[k]);
                        pos++;
                    }
                }
            }
            else // Caso em que há mais de uma palavra chave na busca
            {
                if (strcmp(dic[j].chave, chaves[i]) == 0)
                {
                    for (int l = 0; l < ND; l++) //Percorre o vetor de documentos da chave (s) anterior
                    {
                        int docExistente = 0;
                        for (int k = 0; k < dic[j].n; k++) //Compara cada documento da chave (s) anterior com os documentos da chave que
                        {
                            if (strcmp(resultados[l], dic[j].documentos[k]) == 0)
                            {
                                docExistente = 1;
                            }
                        }
                        if (!docExistente) //Caso em que o documento não atende aos multiplos critérios da pesquisa
                        {
                            strcpy(resultados[l], VAZIO); //Recebe vazio
                        }
                    }
                }
            }
        }
    }
}

void leOpcao(char *c, Chave *chaves, int *quantChaves){
    //Le string
    char str[MAX_STR];
    fgets(str, MAX_STR, stdin);
    
    //Remove \n
    str[strcspn(str, "\n")] = 0;

    //Tokenização da string
    char *aux = strtok(str, " ");

    //Opção do user: B ou I
    *c = aux[0];

    aux = strtok(NULL, " ");

    int posChaves = 0;

    while (aux != NULL)
    {
        strcpy(chaves[posChaves], aux);
        aux = strtok(NULL, " ");
        posChaves++;
    }

    *quantChaves = posChaves;
}


void ordena(NomeDocumento *documentos, int inicio, int final)
{
    int pivo, esquerda, direita;
    NomeDocumento aux;
    pivo = inicio;
    esquerda = inicio;
    direita = final;

    while(esquerda <= direita)
    {
        while((esquerda < final) && (strcmp(documentos[esquerda], documentos[pivo]) <= 0))
        {
            esquerda++;
        }
        while((direita > inicio) && (strcmp(documentos[direita], documentos[pivo])> 0))
        {
            direita--;
        }
        if(esquerda <= direita)
        {
            strcpy(aux, documentos[esquerda]);
            strcpy(documentos[esquerda],documentos[direita]);
            strcpy(documentos[direita], aux);
            esquerda++;
            direita--;
        }
    }
    if(direita > inicio)
    {
        ordena(documentos, inicio, direita);
    }
    if(esquerda < final)
    {
        ordena(documentos, esquerda, final);
    }
}

void imprimeResultadoBusca(NomeDocumento *documentos)
{
    int control = 0;
    for (int i = 0; i < ND; i++)
    {
        if(strcmp(documentos[i], VAZIO) != 0)
        {
            printf("%s\n", documentos[i]);
            control++;
        }
    }
    if(!control)
    {
        printf("none\n");
    }
    
}