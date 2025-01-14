// trie.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

NoDigital *criar_no_digital(void)
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

void inserir_digital(NoDigital *root, const char *word)
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
            node->filhos[index] = criar_no_digital();
        }
        node = node->filhos[index];
        word++;
    }
    node->fim_da_palavra = true;
}

bool procurar_digital(NoDigital *root, const char *word)
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

bool comeca_com_digital(NoDigital *root, const char *prefix)
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

void carrega_palavras_digital(NoDigital *root, const char *filename)
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
        inserir_digital(root, word);
    }

    fclose(file);
}

void liberar_no_digital(NoDigital *root)
{
    if (!root)
        return;
    for (int i = 0; i < TAM_ALFABETO; i++)
    {
        liberar_no_digital(root->filhos[i]);
    }
    free(root);
}

bool remover_digital(NoDigital *root, const char *word)
{
    if (!root)
        return false;

    return remover_digital_operacao(root, word, 0);
}

bool remover_digital_operacao(NoDigital *node, const char *word, int depth)
{
    if (!node)
        return false;

    if (*word == '\0')
    {
        if (node->fim_da_palavra)
        {
            node->fim_da_palavra = false;

            for (int i = 0; i < TAM_ALFABETO; i++)
            {
                if (node->filhos[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    int index = *word - 'a';
    if (remover_digital_operacao(node->filhos[index], word + 1, depth + 1))
    {
        free(node->filhos[index]);
        node->filhos[index] = NULL;

        if (!node->fim_da_palavra)
        {
            for (int i = 0; i < TAM_ALFABETO; i++)
            {
                if (node->filhos[i])
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}