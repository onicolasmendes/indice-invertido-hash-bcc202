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
        dic[i].n = 0;                // Zera a quantidade de documentos em cada chave
    }
}

// Função que le os documentos e palavras chaves associadas, adicionando-os ao Indice Invertido, por meio de outras funções criadas no TAD IndiceInvertido
void leDocumento(IndiceInvertido dic, int n, int *colisoes)
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
                inserePalavraChave(dic, aux, colisoes);
                insereDocumento(dic, aux, nomeDocumento);
                qtdPalavras++;
            }

            aux = strtok(NULL, " ");
        }
    }
}

void vazioTodosDocumentos(NomeDocumento *documentos)
{
    for (int i = 0; i < ND; i++)
    {
        strcpy(documentos[i], VAZIO);
    }
}

bool inserePalavraChave(IndiceInvertido dic, Chave chave, int *colisoes)
{
    // Caso em que a chave já está no Indice Invertido
    int pos = busca(dic, chave);
    if (pos != -1)
    {
        return false;
    }
    // Caso em que a chave não está no Indice Invertido
    int j = 0;
    int ini = h(chave);
    while ((strcmp(dic[(ini + j) % M].chave, VAZIO) != 0) && (j < M)) // Busca a posição disponível
    {
        j++;
        *colisoes = *colisoes + 1; // Incrementa o contador de colisões
    }

    if (j < M) // Verifica se a posição é válida - Se não estoura o tamanho máximo de Palavras Chaves
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

    // Caso a posição que a chave deveria ocupar idealmente esteja sendo ocupada por outra chave, ele vai percorrer até achar uma vazia ou uma que seja igual a chave que está sendo buscada
    while ((strcmp(dic[(ini + j) % M].chave, VAZIO) != 0) && (strcmp(dic[(ini + j) % M].chave, chave) != 0) && (j < M))
    {
        j++;
    }

    if (strcmp(dic[(ini + j) % M].chave, chave) == 0) // Caso em que a chave é encontrada na tabela - Verificaçãp
    {
        return (ini + j) % M; // Retorna a posição
    }

    return -1;
}

bool insereDocumento(IndiceInvertido dic, Chave chave, NomeDocumento doc)
{

    // Busca posição da chave
    int pos = busca(dic, chave);

    if (dic[pos].n == ND) // Caso em que o numero máximo de documentos foi atingido
    {
        return false;
    }

    // Insere o documento e incrementa o n
    strcpy(dic[pos].documentos[dic[pos].n], doc);
    dic[pos].n++;
    return true;
}

void imprime(IndiceInvertido dic)
{
    for (int i = 0; i < M; i++)
    {
        if (strcmp(dic[i].chave, VAZIO) != 0) // Caso em que há uma chave válida (não vazia)
        {
            printf("%s -", dic[i].chave);
            for (int j = 0; j < dic[i].n; j++) // For para printar todos os documentos associados a chave
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
                    for (int l = 0; l < ND; l++) // Percorre o vetor de documentos dque possuem a(s) chave(s) anterior(es)
                    {
                        int docExistente = 0;
                        for (int k = 0; k < dic[j].n; k++) // Percorre o vetor de documentos que possuem a palavra chave atual da busca
                        {
                            // Se um documento do vetor que possui as palavras chaves anteriormente pesquisadas POSSUIR TAMBÉM a palavra chave atual da busca, Ele permanece no vetor
                            if (strcmp(resultados[l], dic[j].documentos[k]) == 0)
                            {
                                docExistente = 1;
                            }
                        }
                        if (!docExistente) // Caso o documento do vetor que possui as palavras chaves anteriores NÃO POSSUA a palavra chave atual da busca, ele recebe a string VAZIO - ou seja, é removido
                        {
                            strcpy(resultados[l], VAZIO); // Recebe vazio
                        }
                    }
                }
            }
        }
    }
}

void leOpcao(char *c, Chave *chaves, int *quantChaves)
{
    // Le string
    char str[MAX_STR];
    fgets(str, MAX_STR, stdin);

    // Remove \n
    str[strcspn(str, "\n")] = 0;

    // Tokenização da string
    char *aux = strtok(str, " ");

    // Opção do user: B ou I
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

void ordena(NomeDocumento *documentos, int inicio, int final) // QuickSort para ordenar os documentos em ordem alfabética crescente
{
    int pivo, esquerda, direita;
    NomeDocumento aux;
    pivo = inicio;
    esquerda = inicio;
    direita = final;

    while (esquerda <= direita)
    {
        while ((esquerda < final) && (strcmp(documentos[esquerda], documentos[pivo]) < 0))
        {
            esquerda++;
        }
        while ((direita > inicio) && (strcmp(documentos[direita], documentos[pivo]) > 0))
        {
            direita--;
        }
        if (esquerda <= direita)
        {
            if (&aux != &documentos[esquerda]) // IF para evitar o overlap de strings - copiar um endereço para ele mesmo
            {
                strcpy(aux, documentos[esquerda]);
            }
            if (&documentos[esquerda] != &documentos[direita])
            {
                strcpy(documentos[esquerda], documentos[direita]);
            }
            if (&documentos[direita] != &aux)
            {
                strcpy(documentos[direita], aux);
            }
            esquerda++;
            direita--;
        }
    }
    if (direita > inicio)
    {
        ordena(documentos, inicio, direita);
    }
    if (esquerda < final)
    {
        ordena(documentos, esquerda, final);
    }
}

void imprimeResultadoBusca(NomeDocumento *documentos, int tamNaoVazio)
{
    // Caso em que não há nenhum documento que corresponde atenda as demandas da busca
    if (tamNaoVazio == 0)
    {
        printf("none\n");
        return;
    }
    else // Caso em que há um ou mais documentos que atendem as demandas da busca
    {
        for (int i = 0; i < tamNaoVazio; i++)
        {
            printf("%s\n", documentos[i]);
        }
        return;
    }
}

void selecionaNaoVazio(NomeDocumento *origem, NomeDocumento *destino, int *qtd)
{
    int pos = 0;
    // For que percorre todo o vetor de documentos
    for (int i = 0; i < ND; i++)
    {
        if (strcmp(origem[i], VAZIO) != 0) // Caso o documento seja válido, ele será copiado para o próximo vetor
        {
            strcpy(destino[pos], origem[i]);
            pos++;
        }
    }
    // Retorna a quantidade de documentos válidos por referência
    *qtd = pos;
}

void imprimeColisoes(int colisoes)
{
    printf("Quantidade de colisões: %d\n", colisoes);
}

void imprimeMemoria()
{
    int memoria = M * sizeof(Item); // Tamanho do vetor IndiceInvertido alocado estaticamente
    printf("Memória gasta: %d bytes\n", memoria);
}