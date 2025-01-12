#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int obter_altura_avl(NoAVL *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

int calcular_fator_de_balanceamento_avl(NoAVL *no)
{
    if (no == NULL)
        return 0;
    else
        return obter_altura_avl(no->esquerdo) - obter_altura_avl(no->direito);
}

NoAVL *criar_no_avl(int dado)
{
    NoAVL *no = (NoAVL *)malloc(sizeof(NoAVL));
    no->dado = dado;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 0;

    return no;
}

NoAVL *rotacao_direita_avl(NoAVL *y)
{
    NoAVL *x = y->esquerdo;
    NoAVL *z = x->direito;

    x->direito = y;
    y->esquerdo = z;

    if (obter_altura_avl(y->esquerdo) > obter_altura_avl(y->direito))
        y->altura = 1 + obter_altura_avl(y->esquerdo);
    else
        y->altura = 1 + obter_altura_avl(y->direito);

    if (obter_altura_avl(x->esquerdo) > obter_altura_avl(x->direito))
        x->altura = 1 + obter_altura_avl(x->esquerdo);
    else
        x->altura = 1 + obter_altura_avl(x->direito);

    return x;
}

NoAVL *rotacao_esquerda_avl(NoAVL *x)
{
    NoAVL *y = x->direito;
    NoAVL *z = y->esquerdo;

    y->esquerdo = x;
    x->direito = z;

    if (obter_altura_avl(x->esquerdo) > obter_altura_avl(x->direito))
        x->altura = 1 + obter_altura_avl(x->esquerdo);
    else
        x->altura = 1 + obter_altura_avl(x->direito);

    if (obter_altura_avl(y->esquerdo) > obter_altura_avl(y->direito))
        y->altura = 1 + obter_altura_avl(y->esquerdo);
    else
        y->altura = 1 + obter_altura_avl(y->direito);

    return y;
}

NoAVL *inserir_no_avl(NoAVL *no, int dado)
{
    if (no == NULL)
        return criar_no_avl(dado);

    if (dado < no->dado)
        no->esquerdo = inserir_no_avl(no->esquerdo, dado);
    else if (dado > no->dado)
        no->direito = inserir_no_avl(no->direito, dado);
    else
        return no;

    if (obter_altura_avl(no->esquerdo) > obter_altura_avl(no->direito))
        no->altura = 1 + obter_altura_avl(no->esquerdo);
    else
        no->altura = 1 + obter_altura_avl(no->direito);

    int balanceamento = calcular_fator_de_balanceamento_avl(no);

    /* Caso 1: Desbalanceamento à esquerda (Rotação à direita). */
    if (balanceamento > 1 && dado < no->esquerdo->dado)
        return rotacao_direita_avl(no);

    /* Caso 2: Desbalanceamento à direita (Rotação à esquerda). */
    if (balanceamento < -1 && dado > no->direito->dado)
        return rotacao_esquerda_avl(no);

    /* Caso 3: Desbalanceamento esquerda-direita (Rotação dupla esquerda-direita). */
    if (balanceamento > 1 && dado > no->esquerdo->dado)
    {
        no->esquerdo = rotacao_esquerda_avl(no->esquerdo);
        return rotacao_direita_avl(no);
    }

    /* Caso 4: Desbalanceamento direita-esquerda (Rotação dupla direita-esquerda). */
    if (balanceamento < -1 && dado < no->direito->dado)
    {
        no->direito = rotacao_direita_avl(no->direito);
        return rotacao_esquerda_avl(no);
    }

    return no;
}

NoAVL *menor_valorNo_avl(NoAVL *no)
{
    NoAVL *atual = no;

    while (atual->esquerdo != NULL)
        atual = atual->esquerdo;

    return atual;
}

NoAVL *remover_no_avl(NoAVL *raiz, int dado)
{
    if (raiz == NULL)
        return raiz;

    if (dado < raiz->dado)
    {
        raiz->esquerdo = remover_no_avl(raiz->esquerdo, dado);
    }
    else if (dado > raiz->dado)
    {
        raiz->direito = remover_no_avl(raiz->direito, dado);
    }
    else
    {
        /* Nó com apenas um filho ou nenhum. */
        if ((raiz->esquerdo == NULL) || (raiz->direito == NULL))
        {
            NoAVL *temp;

            if (raiz->esquerdo != NULL)
                temp = raiz->esquerdo;
            else
                temp = raiz->direito;

            /* Caso de nenhum filho. */
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }

            free(temp);
        }
        else
        {
            /* Caso de dois filhos: obtém o sucessor. */
            NoAVL *temp = menor_valorNo_avl(raiz->direito);

            raiz->dado = temp->dado;

            raiz->direito = remover_no_avl(raiz->direito, temp->dado);
        }
    }

    /* Se a árvore tinha apenas um nó. */
    if (raiz == NULL)
        return raiz;

    if (obter_altura_avl(raiz->esquerdo) > obter_altura_avl(raiz->direito))
        raiz->altura = 1 + obter_altura_avl(raiz->esquerdo);
    else
        raiz->altura = 1 + obter_altura_avl(raiz->direito);

    int balanceamento = calcular_fator_de_balanceamento_avl(raiz);

    /* Caso 1: Desbalanceamento à esquerda. */
    if (balanceamento > 1 && calcular_fator_de_balanceamento_avl(raiz->esquerdo) >= 0)
        return rotacao_direita_avl(raiz);

    /* Caso 2: Desbalanceamento esquerda-direita. */
    if (balanceamento > 1 && calcular_fator_de_balanceamento_avl(raiz->esquerdo) < 0)
    {
        raiz->esquerdo = rotacao_esquerda_avl(raiz->esquerdo);
        return rotacao_direita_avl(raiz);
    }

    /* Caso 3: Desbalanceamento à direita. */
    if (balanceamento < -1 && calcular_fator_de_balanceamento_avl(raiz->direito) <= 0)
        return rotacao_esquerda_avl(raiz);

    /* Caso 4: Desbalanceamento direita-esquerda. */
    if (balanceamento < -1 && calcular_fator_de_balanceamento_avl(raiz->direito) > 0)
    {
        raiz->direito = rotacao_direita_avl(raiz->direito);
        return rotacao_esquerda_avl(raiz);
    }

    return raiz;
}

void imprimir_em_ordem_avl(NoAVL *raiz)
{
    if (raiz != NULL)
    {
        imprimir_em_ordem_avl(raiz->esquerdo);
        printf("%d ", raiz->dado);
        imprimir_em_ordem_avl(raiz->direito);
    }
}