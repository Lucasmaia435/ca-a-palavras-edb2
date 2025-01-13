#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "trie.h"

void ler_palavras_arquivo(char *nome_arquivo, NoDigital *raiz)
{
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char palavra[100];

    while (fscanf(arquivo, "%s", palavra) != EOF)
    {
        inserir_digital(raiz, palavra);
    }

    fclose(arquivo);
}

char **ler_tabuleiro_arquivo(char *nome_arquivo, int *linhas, int *colunas)
{

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(arquivo, "%d %d", linhas, colunas);

    char **tabuleiro = (char **)malloc(*linhas * sizeof(char *));
    for (int i = 0; i < *linhas; i++)
    {
        tabuleiro[i] = (char *)malloc((*colunas + 1) * sizeof(char));
        for (int j = 0; j < *colunas; j++)
        {
            fscanf(arquivo, " %c", &tabuleiro[i][j]);
        }
    }

    fclose(arquivo);

    return tabuleiro;
}