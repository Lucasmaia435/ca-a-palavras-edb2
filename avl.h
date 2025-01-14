#ifndef AVL_H
#define AVL_H

typedef struct NoAVL
{
  char *palavra;
  struct NoAVL *esquerdo;
  struct NoAVL *direito;
  int altura;
} NoAVL;

NoAVL *criar_no_avl(char *palavra);
int obter_altura_avl(NoAVL *no);
int calcular_fator_de_balanceamento_avl(NoAVL *no);
NoAVL *rotacao_direita_avl(NoAVL *y);
NoAVL *rotacao_esquerda_avl(NoAVL *x);
NoAVL *inserir_no_avl(NoAVL *no, char *valor);
NoAVL *remover_no_avl(NoAVL *raiz, char *valor);
void imprimir_em_ordem_avl(NoAVL *raiz);

#endif