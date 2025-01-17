#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define TAM_ALFABETO 26

typedef struct NoDigital
{
    struct NoDigital *filhos[TAM_ALFABETO];
    bool fim_da_palavra;
} NoDigital;

NoDigital *criar_no_digital(void);
void inserir_digital(NoDigital *raiz, const char *word);
bool procurar_digital(NoDigital *raiz, const char *word);
bool comeca_com_digital(NoDigital *raiz, const char *prefix);
void carrega_palavras_digital(NoDigital *raiz, const char *arquivo);
void liberar_no_digital(NoDigital *raiz);
bool remover_digital(NoDigital *root, const char *word);
bool remover_digital_operacao(NoDigital *node, const char *word, int depth);

#endif