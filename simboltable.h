#ifndef SIMBOL_H
#define SIMBOL_H

#include <stdio.h>
#include <stdlib.h>

#define TAM_VARIAVEL	30
#define TAM_PILHA		50
#define ERROR_SIMBOL    -3

enum TIPO_VAR {
	VOID,INT,CHAR,FLOAT, BOOL
}TIPO_VAR;

enum categoria{
	FUNC,PARAM,VAR
}CATEGORIA;

typedef struct nodo_simbol{
	char nome[TAM_VARIAVEL];
	int  tamanho;
	int  escopo;
	int  tipo;
	int  categoria;
	int  endereco;
	int  zombie;
}nodo_simbol;

void iniciar_pilha(nodo_simbol*);

void set_tipo(nodo_simbol*,int,int*);
void set_nome(nodo_simbol*,char*,int*);
void set_categoria(nodo_simbol*,int, int*);
void set_escopo(nodo_simbol*,int,int*);
void set_zombie(nodo_simbol*,int,int*);
void set_endereco(nodo_simbol*,int,int*);
void set_tamanho(nodo_simbol*,int,int*);

void inserir_pilha(nodo_simbol element, nodo_simbol *pilha, int *indicador);

int procurar_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador);

int pegar_param(char *nome,nodo_simbol* pilha,int *indicador,int* tipos);

int conferir_tipo_func(int tipo,nodo_simbol *pilha,int pos);

void remover_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador);

void imprimir(nodo_simbol*,int*);

#endif //SIMBOL_H
