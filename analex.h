#ifndef ANALEX_H
#define ANALEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define TAM_ARRAY 100
#define ERROR -1

typedef struct{
    int type;
    char value[20];
}token;

typedef struct{
    int prim;
    int sec;
}classe;

enum primaria{
    PR,ID,SIN,CONST,COMP, OPERL
}PRIMARIA;

enum sinal{
    MAIS, MENOS, MULT, DIVI, APARE, FPARE, ACOLH, FCOLH, ACHAV, FCHAV, PVIRG, ATRIB
}SINAL;

enum constante{
    INTEIRA, REAL, LITERAL, CHAR
}CONSTANTE;

enum comparacao{
    MAIOR, MENOR, IGUAL, MENORQ, MAIORQ, DIFERENTE
}COMPARACAO;

enum operador_logico{
    AND, NOT , OR
}OPERADOR_LOGICO;

static char palavras_reservadas[12][7] = { "if","else", "while", "for", "int", "float","bool", "char", "void", "return", "true", "false" };


static char estados_finais[27][16] = {"", "FIM_COLCHETE", "INI_COLCHETE", "ASTERISCO", "OP_MATEMATICO", "OP_COMPARACAO", "OP_COMPARACAO",
                                       "NEGACAO", "OP_COMPARACAO", "CONST_INTEIRA", "STRING", "IDENTIFICADOR", "COMENTARIO", "DIVISAO",
                                       "E_LOGICO", "OU_LOGICO", "VIRGULA", "PONTO", "INI_CHAVES", "FIM_CHAVES", "INI_PARENTESES",
                                       "FIM_PARENTESES", "CARACTER", "PONTO_VIRGULA", "ATRIBUICAO","CONST_REAL","OP_COMPARACAO"};

static token array_tokens[TAM_ARRAY];
static int indice_token = 0;

FILE* abrir_arquivo(char*);
int nextTokens(FILE*,token*);
void imprimirArrayTokens();
void porEmArrayDeTokens(char*,int);
void classificar_keyword(token *lex);
#endif // ANALEX_H
