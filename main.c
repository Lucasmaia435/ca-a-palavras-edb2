#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "jogo.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    NoDigital *raiz = criar_no_digital();
    NoAVL *raizAVL = NULL;

    int *linhas = (int *)malloc(sizeof(int));
    int *colunas = (int *)malloc(sizeof(int));

    char **tabuleiro = ler_tabuleiro_arquivo("tabuleiro.txt", linhas, colunas);

    ler_palavras_arquivo("palavras.txt", raiz);

    buscar_palavras(tabuleiro, &raizAVL, raiz, *linhas, *colunas);

    imprimir_em_ordem_avl(raizAVL);

    return 0;
}