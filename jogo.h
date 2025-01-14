#ifndef JOGO_H
#define JOGO_H
#include "trie.h"
#include "avl.h"

void ler_palavras_arquivo(char *nome_arquivo, NoDigital *raiz);

char **ler_tabuleiro_arquivo(char *nome_arquivo, int *linhas, int *colunas);

void buscar_palavras_aux(char **tabuleiro, NoAVL **rootAVL, NoDigital *root, int i, int j, int linhas, int colunas, int i_dir, int j_dir);

void buscar_palavras(char **tabuleiro, NoAVL **rootAVL, NoDigital *root, int linhas, int colunas);
#endif
