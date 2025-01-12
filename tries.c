#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALFABETO 26

typedef struct No{
  struct No *filhos[ALFABETO];
  bool fim_da_palavra;
}No;

No *criar_no()
{
  No *novo_no = (No *)malloc(sizeof(No));
  
  if(novo_no)
  {
    novo_no->fim_da_palavra = false;
    for(int i = 0; i < ALFABETO; i++){
      novo_no->filhos[i] = NULL;
    }
  }
  
  return novo_no;
}

void inserir(No *raiz, const char *palavra)
{
  No *atual = raiz;
  
  for(int i = 0; palavra[i] != '\0'; i++){
    int indice = palavra[i] - 'a';

    if(atual->filhos[indice] == NULL)
      atual->filhos[indice] = criar_no();

    atual = atual->filhos[indice];
  }
  
  atual->fim_da_palavra = true;
}

bool buscar(No *raiz, const char *palavra)
{
  No *atual = raiz;
  
  for(int i = 0; palavra[i] != '\0'; i++){
    int indice = palavra[i] - 'a';

    if(atual->filhos[indice] == NULL)
      return false;

    atual = atual->filhos[indice];
  }
  
  return atual->fim_da_palavra;
}

void liberar_trie(No *raiz)
{
  if(raiz == NULL)
    return;

  for(int i = 0; i < ALFABETO; i++)
        liberar_trie(raiz->filhos[i]);

  free(raiz);
}

int main(void)
{
  No *raiz = criar_no();

  const char *palavras1[] = {"casa","carro","casaco","cadeira","sapato"};
  const char *palavras2[] = {"casa","carro","casaco","cadeira","sapato","casco","nuvem","prato"};

  for(int i=0; i<5; i++)
   inserir(raiz, palavras1[i]);
  
  for(int i=0; i<8; i++)
    if(buscar(raiz, palavras2[i]))
      printf("A palavra %s está na Trie.\n", palavras2[i]);
    else
      printf("A palavra %s não está na Trie.\n", palavras2[i]);
    
  liberar_trie(raiz);

  return 0;
}
