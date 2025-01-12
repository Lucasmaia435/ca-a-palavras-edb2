#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define TAM_ALFABETO 26

typedef struct NoDigital
{
    struct NoDigital *filhos[TAM_ALFABETO];
    bool fim_da_palavra;
} NoDigital;

// Funções para a Trie
NoDigital *criarNoDigital(void);
void inserir(NoDigital *raiz, const char *word);
bool procurar(NoDigital *raiz, const char *word);
bool comecaCom(NoDigital *raiz, const char *prefix);
void carregaPalavras(NoDigital *raiz, const char *arquivo);
void liberarNo(NoDigital *raiz);

#endif // TRIE_H