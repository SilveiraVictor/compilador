#include <stdio.h>
#include <stdlib.h>
#include "analex.h"
#include "anasin.h"

token fila_tokens[TAM_FILA];
int indice_fila = 0;

int main(){
    FILE* ptr;
    token lex;
    int erro_ou_nao;
    ptr = abrir_arquivo("codigo.txt");
    inicia_sintatico(ptr);
    return 0;
}

