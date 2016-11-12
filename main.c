#include <stdio.h>
#include <stdlib.h>
#include "analex.h"
#include "anasin.h"
#include "simboltable.h"

token fila_tokens[TAM_FILA];
int indice_fila = 0;
nodo_simbol pilha[TAM_PILHA];
int ind;
int label=0;

int main(){
	char resp[4][16] = {"SUCESSO","ERRO LEXICO","ERRO SINTATICO","ERRO SEMANTICO"};	
	int erro_ou_nao = 1;
    FILE* ptr;
    token lex;
    ptr = abrir_arquivo("codigo.txt");
    iniciar_pilha(pilha);
    while(erro_ou_nao == 1){
	    erro_ou_nao = inicia_sintatico(ptr);
	}
	if(erro_ou_nao == 0){
		imprimir(pilha,&ind);
		printf("%s\n",resp[0]);
	}else{
		printf("%s\n",resp[erro_ou_nao*-1]);
	}
    return 0;
}

