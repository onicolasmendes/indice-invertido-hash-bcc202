#include "indiceInvertido.h"
#include <stdio.h>

int main() {
    int n;
    scanf("%d\n", &n);

    IndiceInvertido dic;
    inicia(dic);

    leDocumento(dic, n);

    imprime(dic);
    
    

    
    return 0;
}
