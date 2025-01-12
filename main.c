#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "jogo.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    NoDigital *raiz = criarNoDigital();

    ler_palavras_arquivo("palavras.txt", raiz);

    bool resultado = procurar_digital(raiz, "calo");

    if (resultado)
    {
        printf("A palavra foi encontrada.\n");
    }
    else
    {
        printf("A palavra não foi encontrada.\n");
    }

    return 0;
}