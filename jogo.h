#ifndef JOGO_H
#define JOGO_H
#include "trie.h"

void ler_palavras_arquivo(char *nome_arquivo, NoDigital *raiz);

char **ler_tabuleiro_arquivo(char *nome_arquivo, int *linhas, int *colunas);

#endif
