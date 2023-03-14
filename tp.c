#include "indiceInvertido.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{

    int n;
    scanf("%d\n", &n);

    // Colisoes - Variável para contar a quantidade de colisões
    int colisoes = 0;

    // Criação do Indice Invertido
    IndiceInvertido dic;
    inicia(dic);

    // Cálculo do tempo de execução do código
    double tempo_gasto = 0.0;
    clock_t begin = clock();

    // Função que le os documentos e palavras chaves associadas, adicionando-os ao Indice Invertido, por meio de outras funções criadas no TAD IndiceInvertido
    leDocumento(dic, n, &colisoes);

    // Vetor de chaves que será usado para receber as palavras chaves passadas pelo usuário para busca
    Chave chaves[M];
    int qtdChavesBusca;

    char op;

    // Vetor de documentos que será utilizado para receber os documentos que atendem as pesquisas + strings VAZIO
    NomeDocumento resultados[ND];

    // Coloca vazio em todas as posições em Documentos
    vazioTodosDocumentos(resultados);

    // Le opção do usuário e pega as palavras chaves da busca e a quantidade das mesmas, em caso de uma busca
    leOpcao(&op, chaves, &qtdChavesBusca);

    switch (op)
    {
    case 'B':
        // Realiza a busca dos documentos que possuem as palavras chaves informadas pelo usu[ario]
        consulta(dic, chaves, qtdChavesBusca, resultados);

        // Vetor auxiliar para receber documentos válidos (não vazios)
        int tamNaoVazios;
        NomeDocumento naoVazios[ND];

        // Função varre todo o vetor resultados e passa somente os documentos válidos (não vazios) para o vetor auxiliar
        selecionaNaoVazio(resultados, naoVazios, &tamNaoVazios);

        // Caso não haja nenhum  documento válido ou apenas um documento válido, não se faz necessário chamar a função de ordenação
        if (tamNaoVazios != 0 && tamNaoVazios != 1)
        {
            // Ordena o vetor de documentos válidos que atendem as demandas da pesquisa (QuickSort)
            ordena(naoVazios, 0, tamNaoVazios - 1);
        }

        // Imprime os documentos válidos que atendem as demandas da pesquisa
        imprimeResultadoBusca(naoVazios, tamNaoVazios);
        break;
    case 'I':
        // Função que imprime o Indice Invertido
        imprime(dic);
        break;
    default:
        break;
    }

    // Término do cálculo da execução
    clock_t end = clock();
    tempo_gasto += (double)(end - begin) / CLOCKS_PER_SEC;
    // printf("Tempo gasto %f s\n", tempo_gasto);
    // imprimeColisoes(colisoes);
    // imprimeMemoria();
    return 0;
}
