// trie.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

NoDigital *criarNoDigital(void)
{
    NoDigital *node = (NoDigital *)malloc(sizeof(NoDigital));
    if (node)
    {
        node->fim_da_palavra = false;
        for (int i = 0; i < TAM_ALFABETO; i++)
        {
            node->filhos[i] = NULL;
        }
    }
    return node;
}

void inserir(NoDigital *root, const char *word)
{
    NoDigital *node = root;
    while (*word)
    {
        int index = *word - 'a';
        if (index < 0 || index >= TAM_ALFABETO)
        {
            fprintf(stderr, "Caracter inválido na palavra: %c\n", *word);
            return;
        }
        if (!node->filhos[index])
        {
            node->filhos[index] = create_node();
        }
        node = node->filhos[index];
        word++;
    }
    node->fim_da_palavra = true;
}

bool procurar(NoDigital *root, const char *word)
{
    NoDigital *node = root;
    while (*word)
    {
        int index = *word - 'a';
        if (index < 0 || index >= TAM_ALFABETO || !node->filhos[index])
        {
            return false;
        }
        node = node->filhos[index];
        word++;
    }
    return node->fim_da_palavra;
}

bool comecaCom(NoDigital *root, const char *prefix)
{
    NoDigital *node = root;
    while (*prefix)
    {
        int index = *prefix - 'a';
        if (index < 0 || index >= TAM_ALFABETO || !node->filhos[index])
        {
            return false;
        }
        node = node->filhos[index];
        prefix++;
    }
    return true;
}

void carregaPalavras(NoDigital *root, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erro no arquivo");
        return;
    }

    char word[256];
    while (fscanf(file, "%255s", word) == 1)
    {
        insert(root, word);
    }

    fclose(file);
}

void liberarNo(NoDigital *root)
{
    if (!root)
        return;
    for (int i = 0; i < TAM_ALFABETO; i++)
    {
        liberarNo(root->filhos[i]);
    }
    free(root);
}