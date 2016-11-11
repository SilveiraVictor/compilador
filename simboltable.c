#include "simboltable.h"
#include <string.h>

void iniciar_pilha(nodo_simbol *pilha){
	int i;
	for(i=0;i<TAM_PILHA;i++){
		strcpy(pilha[i].nome,"");
		pilha[i].endereco = -1;
		pilha[i].isFunc = -1;
		pilha[i].escopo = -1;
		pilha[i].zombie = -1;
		pilha[i].tipo = -1;
	}
}

void set_tipo(nodo_simbol *pilha,int t,int *indicador){
	pilha[*indicador].tipo = t;
}

void set_nome(nodo_simbol *pilha,char *nome ,int *indicador){
	strcpy(pilha[*indicador].nome,nome);
}

void set_isFunc(nodo_simbol *pilha,int isFunc, int *indicador){
	pilha[*indicador].isFunc = isFunc;
}
void set_escopo(nodo_simbol *pilha,int escopo, int *indicador){
	pilha[*indicador].escopo = escopo;
}

void set_zombie(nodo_simbol *pilha,int zombie,int *indicador){
	pilha[*indicador].zombie = zombie;
}

void set_endereco(nodo_simbol *pilha,int endereco, int *indicador){
	pilha[*indicador].endereco = endereco;
}

void inserir_pilha(nodo_simbol element, nodo_simbol *pilha,int *indicador){	
}

void modificar_pilha(nodo_simbol element, nodo_simbol *pilha,int *indicador){

}


//retorna 1 se encontrar na pilha, senão 0
int procurar_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador){
	int last = *indicador;
	for(last;last>=0;last--){
		if( (!strcmp(nome,pilha[last].nome)) && (escopo == pilha[last].escopo)) return 1;
	}
	return 0;
}

void remover_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador){

}

void imprimir(nodo_simbol *pilha, int *ind){
	int i;
	for(i=0;i<=*ind;i++){
		printf("%s\n",pilha[i].nome);
	}
}
