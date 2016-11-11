#ifndef ANASIN_H
#define ANASIN_H
#include "analex.h"

#define SINTAX_ERROR -2
#define TAM_FILA 50

int inicia_sintatico(FILE* ptr);
int decl(FILE *ptr);
int func(FILE *ptr);
int decl_var(FILE* ptr,int escopo, int tipo);
int tipo_param(FILE* ptr,int isDecl,int*);
int cmd(FILE* ptr);
int expr(FILE* ptr);
int expr_simp(FILE* ptr);
int termo(FILE* ptr);
int fator(FILE *ptr);
int atrib(FILE* ptr);
void inicia_fila_tokens();
void get_token_fila(token* t);
void por_de_volta(token t);
void remove_elemento_fila();
void imprimir_fila();

#endif // ANASIN_H
