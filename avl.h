#ifndef AVL_H
#define AVL_H

typedef struct NoAVL
{
  int dado;
  struct NoAVL *esquerdo;
  struct NoAVL *direito;
  int altura;
} NoAVL;

int obter_altura_avl(NoAVL *no);
int calcular_fator_de_balanceamento_avl(NoAVL *no);
NoAVL *rotacao_direita_avl(NoAVL *y);
NoAVL *rotacao_esquerda_avl(NoAVL *x);
NoAVL *criar_no_avl(int dado);
NoAVL *inserir_no_avl(NoAVL *no, int dado);
NoAVL *remover_no_avl(NoAVL *raiz, int dado);
void imprimir_em_ordem_avl(NoAVL *raiz);

#endif