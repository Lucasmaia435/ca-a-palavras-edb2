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