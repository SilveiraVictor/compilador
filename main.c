#include <stdio.h>
#include <stdlib.h>
#include "analex.h"
#include "anasin.h"

token fila_tokens[TAM_FILA];
int indice_fila = 0;

int main(){
    FILE* ptr;
    token lex;
    int erro_ou_nao = 1;
    ptr = abrir_arquivo("codigo.txt");
    while(erro_ou_nao == 1){
	    erro_ou_nao = inicia_sintatico(ptr);
		printf("passou uma vez res = %d\n",erro_ou_nao);
	}
    return 0;
}

