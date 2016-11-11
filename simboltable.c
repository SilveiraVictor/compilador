#include "simboltable.h"
#include <string.h>

void iniciar_pilha(nodo_simbol *pilha){
	int i;
	for(i=0;i<TAM_PILHA;i++){
		strcpy(pilha[i].nome,"");
		pilha[i].endereco = -1;
		pilha[i].categoria = -1;
		pilha[i].escopo = -1;
		pilha[i].zombie = -1;
		pilha[i].tipo = -1;
		pilha[i].tamanho = 1;
	}
}

void set_tipo(nodo_simbol *pilha,int t,int *indicador){
	pilha[*indicador].tipo = t;
}

void set_nome(nodo_simbol *pilha,char *nome ,int *indicador){
	strcpy(pilha[*indicador].nome,nome);
}

void set_categoria(nodo_simbol *pilha,int categoria, int *indicador){
	pilha[*indicador].categoria = categoria;
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

void set_tamanho(nodo_simbol *pilha,int tamanho, int *indicador){
	pilha[*indicador].tamanho = tamanho;
}

void inserir_pilha(nodo_simbol element, nodo_simbol *pilha,int *indicador){	
}

void modificar_pilha(nodo_simbol element, nodo_simbol *pilha,int *indicador){

}


//retorna 1 se encontrar na pilha, senão 0
int procurar_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador){
	int last = *indicador-1;
	for(last;last>=0;last--){
		//printf("recebido = %s, comparando com %s\n",nome,pilha[last].nome);
		if( (!strcmp(nome,pilha[last].nome)) && (escopo == pilha[last].escopo)) return last;
	}
	return -1;
}

int conferir_tipo_func(int tipo,nodo_simbol *pilha,int pos){
		if( (tipo == pilha[pos].tipo) ) return 1;
		else return 0;
}

void remover_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador){

}

int pegar_param(char *nome,nodo_simbol* pilha,int *indicador,int* tipos){
	int qtd=0;
	int last = *indicador-1;
	for(last;last>=0;last--){
		if( (!strcmp(nome,pilha[last].nome)) && (pilha[last].categoria == FUNC)) break;
	}
	last++;
	while(pilha[last].categoria = PARAM){
		tipos[qtd++] = pilha[last].tipo;	
	}
	return qtd;	
}

void imprimir(nodo_simbol *pilha, int *ind){
	int i;
	char cat[3][6] = {"FUNC","PARAM","VAR"};
	char tipo[5][6] = {"VOID","INT","CHAR","FLOAT","BOOL"};
	printf("|%15s|%6s|%5s|%9s|%6s|\n","nome","tipo","size","categoria","escopo");
	for(i=0;i<*ind;i++){
		printf("|%15s|%6s|%5d|%9s|%6d|\n",pilha[i].nome,tipo[pilha[i].tipo],pilha[i].tamanho,cat[pilha[i].categoria],pilha[i].escopo);
	}
}
