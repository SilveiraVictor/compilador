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
		pilha[i].label = -1;
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

void set_label(nodo_simbol *pilha,int label,int *indicador){
	pilha[*indicador].label = label;
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

escAdd get_adress(char *nome,nodo_simbol *pilha,int *indicador){
		int i;
		escAdd j;
		i = *indicador;
		for(i;i>=0;i--){
			if(!strcmp(pilha[i].nome,nome)){
				j.escopo = pilha[i].escopo;
				if(pilha[i].categoria == FUNC){
					j.add = pilha[i].label;
				}else{
					j.add = pilha[i].endereco;				
				}							
			return j;			
			}
		}
		return j;
}

void remover_elemento(char* nome,int escopo, nodo_simbol *pilha,int *indicador){
}

int destruir_func(nodo_simbol *pilha,int *indicador){
	int qtd=0;	
	//printf("cat = %d\n",pilha[*indicador-1].categoria);
	while(pilha[*indicador-1].categoria == VAR){
		strcpy(pilha[(*indicador)-1].nome,"");
		pilha[(*indicador)-1].endereco = -1;
		pilha[(*indicador)-1].categoria = -1;
		pilha[(*indicador)-1].escopo = -1;
		pilha[(*indicador)-1].zombie = -1;
		pilha[(*indicador)-1].tipo = -1;
		pilha[(*indicador)-1].tamanho = 1;
		(*indicador)--;
		qtd++;	
	}
	return qtd;
}

int pegar_param(nodo_simbol* pilha,int pos,int* tipos){
	int qtd=0;
	pos++;
	while(pilha[pos].categoria == PARAM){
		tipos[qtd++] = pilha[pos++].tipo;	
	}
	return qtd;	
}

void imprimir(nodo_simbol *pilha, int *ind){
	int i;
	char cat[3][6] = {"FUNC","PARAM","VAR"};
	char tipo[5][6] = {"VOID","INT","CHAR","FLOAT","BOOL"};
	printf("|%15s|%6s|%5s|%9s|%6s|%5s|%3s|\n","nome","tipo","size","categoria","escopo","label","end");
	for(i=0;i<*ind;i++){
		printf("|%15s|%6s|%5d|%9s|%6d|%5d|%3d|\n",pilha[i].nome,tipo[pilha[i].tipo],pilha[i].tamanho,cat[pilha[i].categoria],pilha[i].escopo,pilha[i].label,pilha[i].endereco);
	}
}
