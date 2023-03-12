#include "indiceInvertido.h"
#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d\n", &n);

    IndiceInvertido dic;
    inicia(dic);

    leDocumento(dic, n);

    Chave chaves[M];
    char op;
    int qtdChavesBusca;
    NomeDocumento resultados[ND];
    //Coloca vazio em todas as posições em Documentos
    for(int i = 0; i < ND; i++)
    {
        strcpy(resultados[i], VAZIO);
    }

    leOpcao(&op, chaves, &qtdChavesBusca);

    switch (op)
    {
    case 'B':
        consulta(dic, chaves,qtdChavesBusca, resultados);
        ordena(resultados, 0 , 99 );
        imprimeResultadoBusca(resultados);
        break;
    case 'I':
        imprime(dic);
        break;
    default:
        break;
    }    
    return 0;
}
