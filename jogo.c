#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

    printf("\nPalavras salvas!\n");
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
            tabuleiro[i][j] = tolower(tabuleiro[i][j]);
        }
    }

    fclose(arquivo);

    printf("\nTabuleiro salvo!\n");

    return tabuleiro;
}

int dir[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void buscar_palavras_aux(char **tabuleiro, NoAVL *rootAVL, NoDigital *root, int i, int j, int linhas, int colunas, int i_dir, int j_dir)
{
    if (i < 0 || j < 0 || i >= linhas || j >= colunas)
    {
        printf("Fora dos limites\n");
        return;
    }

    char *substring = (char *)malloc(2 * sizeof(char));
    substring[0] = tolower(tabuleiro[i][j]);
    substring[1] = '\0';

    while (i >= 0 && i < linhas && j >= 0 && j < colunas && comeca_com_digital(root, substring))
    {

        if (procurar_digital(root, substring) == true)
        {

            rootAVL = inserir_no_avl(rootAVL, substring);
            remover_digital(root, substring);
            printf("palavra achada %s\n", substring);
            free(substring);
            return;
        }

        i = i + i_dir;
        j = j + j_dir;

        if (i < 0 || j < 0 || i >= linhas || j >= colunas)
        {
            break;
        }

        int len = strlen(substring);
        substring = (char *)realloc(substring, (len + 2) * sizeof(char));
        substring[len] = tolower(tabuleiro[i][j]);
        substring[len + 1] = '\0';
    }

    free(substring);
}

void buscar_palavras(char **tabuleiro, NoAVL *rootAVL, NoDigital *root, int linhas, int colunas)
{
    printf("Varrendo o tabuleiro para buscar palavras...");

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {

            char str[2] = {tabuleiro[i][j], '\0'};
            if (comeca_com_digital(root, str) == true)
            {
                printf("Começando com %c\n", tabuleiro[i][j]);
                for (int z = 0; z < 8; z++)
                {

                    buscar_palavras_aux(tabuleiro, rootAVL, root, i, j, linhas, colunas, dir[z][0], dir[z][1]);
                }
            };
        }
    }

    printf("Finalizando varredura!\n");
}