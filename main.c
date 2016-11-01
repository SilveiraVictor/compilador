#include <stdio.h>
#include <stdlib.h>
#include "analex.h"
#include "anasin.h"

extern int indice_fila;
extern token fila_tokens[10];

int main(){
    FILE* ptr;
    token lex;
    int erro_ou_nao;
    ptr = abrir_arquivo("codigo.txt");
    inicia_sintatico(ptr);
    return 0;
}

