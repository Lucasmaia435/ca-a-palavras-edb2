# Caça palavras

Este projeto é jogo simples de caça palavras que implementa uma árvore AVL para armazenar palavras encontradas e uma árvore digital (Trie) para validar palavras possíveis

## Estrutura do Projeto

- `avl.h`: Declaração das funções de árvore AVL do projeto.
- `trie.h`: Declaração das funções de árvore digital do projeto.
- `avl.c`: Implementação das funções declaradas em `avl.h`.
- `trie.c`: Implementação das funções declaradas em `trie.h`.
- `jogo.c`: Implementa a lógica do jogo.
- `main.c`: Arquivo principal que inicializa o projeto.
- `palavras.txt`: Arquivo com as palavras a serem buscadas.
- `tabuleiros.txt`: Arquivo contendo o tabuleiro de letras do jogo.
- `Makefile`: Arquivo para compilar o projeto.

## Como Executar

1. Certifique-se de ter o compilador GCC instalado.
2. Navegue até o diretório do projeto.
3. Compile o projeto utilizando os comandos:
    
    ```bash
    gcc -c funcs.c
    gcc -o funcs funcs.o main.c -o main
    ```
4. Caso possua a ferramenta make instalada, basta executá-la:

    ```bash
    mingw32-make.exe
    ```
    ou
    
    ```bash
    make
    ```