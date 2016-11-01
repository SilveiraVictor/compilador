#include <stdio.h>
#include "analex.h"

/*
Lembrar de usar o retorno das funcoes
*/


int inicia_sintatico(FILE* ptr){
    int flag;
    token tok,taux;
    extern int indice_fila;
    extern token fila_tokens[10];
    inicia_fila_tokens();
    flag = nextTokens(ptr,&tok);
    if(flag != 1) return flag;
    if( (! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
        fila_tokens[indice_fila++] = tok;
    }else if (!strcmp(tok.value,"char")){
        fila_tokens[indice_fila++] = tok;
    }else return ERROR;
    flag = nextTokens(ptr,&tok);
    if(flag != 1) return flag;
    if(tok.type != 11) return ERROR;
    fila_tokens[indice_fila++] = tok;
    flag = nextTokens(ptr,&tok);
    if(flag != 1) return flag;
    fila_tokens[indice_fila++] = tok;
    if(!strcmp(tok.value,"[") || !strcmp(tok.value,",") || !strcmp(tok.value,";")){
        fila_tokens[indice_fila++] = tok;
        decl(ptr);
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,";")) return 1;
        else return ERROR;
    }else if(!strcmp(tok.value,"(")){
            do{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
                fila_tokens[indice_fila++] = tok;
            }while(strcmp(tok.value,")"));
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
                fila_tokens[indice_fila++] = tok;
            if(!strcmp(tok.value,";")){
                decl(ptr);
                return 1;
            }else if(!strcmp(tok.value,",")){
                decl(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,";")) return 1;
                else return ERROR;
            }else if(!strcmp(tok.value,"{")){
                func(ptr);
                return 1;
            }else return ERROR;
    }else return ERROR;
}

int decl(FILE *ptr){
    extern int indice_fila;
    extern token fila_tokens[10];
    token tok, taux;
    int i=0,flag;
    printf("ENTROU EM DECL\n");
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"void")){
        if(indice_fila > 0){
           get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        do{
            if(tok.type == 11){
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;                                              
                }
                if(strcmp(tok.value,"(")){
                        tipo_param(ptr);
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                        }
                        if(!strcmp(tok.value,")")){
                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                        }else return ERROR;
                }else return ERROR;
            }else return ERROR;
        }while(!strcmp(tok.value,","));
        fila_tokens[indice_fila++] = tok;
        return 1;
    }else if((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        do{
        if(tok.type == 11){
            taux = tok;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,"(")){
                tipo_param(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,")")){
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }else return ERROR;
            }else{
                por_de_volta(tok);
                por_de_volta(taux);
                do{
                    decl_var(ptr);
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }while(!strcmp(tok.value,","));
                return 1;
            }
        }else return ERROR;
    }while(!strcmp(tok.value,","));
    }else return ERROR;
}

int func(FILE* ptr){
    extern int indice_fila;
    extern token fila_tokens[10];
    token tok;
    int i=0,flag;
    printf("ENTROU EM FUNC fila :\n");
    imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(tok.type == 11){
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,"(")){
//                if(indice_fila > 0){
//                    get_token_fila(&tok);
//                }else{
//                    flag = nextTokens(ptr,&tok);
//                    if(flag != 1) return flag;
//                }
                tipo_param(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,")")){
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(!strcmp(tok.value,"{")){
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                        }
                        while((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool") || (!strcmp(tok.value,"void")))){
                            do{
                            decl_var(ptr);
                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                            }while(!strcmp(tok.value,","));

                            if(!strcmp(tok.value,";")){
                            }else return ERROR;

                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                        }
                        while(strcmp(tok.value,"}")){
                            cmd(ptr);

                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                        }
                        return 1;
                    }else return ERROR;
                }else return ERROR;
            }else return ERROR;
        }else return ERROR;
    }else return ERROR;
}

int tipo_param(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    token tok;
    int flag;
    printf("ENTROU TIPO_PARAM file:\n");
    imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"void")){
        return 1;
    }else if((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        do{
            if(tok.type == 11){
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,"[")){
                   if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(!strcmp(tok.value,"]")){
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                        }
                        if(!strcmp(tok.value,",")){
                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                            if(!((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool")))) return ERROR;
                        }else{
                            por_de_volta(tok);
                            return 1;
                        }
                    }
                    else return ERROR;
                }else if(!strcmp(tok.value,",")){
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }else{
                    por_de_volta(tok);
                    return 1;
                }
            }else if(strcmp(tok.value,"&")){
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(tok.type == 11){
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(strcmp(tok.value,",")){
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                        }
                        if(!((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool")))) return ERROR;
                    }else{
                        por_de_volta(tok);
                        return 1;
                    }
                }else return ERROR;
            }else return ERROR;
        }while(1);
    }else return ERROR;
}

int decl_var(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    int flag;
    token tok;
    printf("ENTROU DECL_VAR fila:\n");
    imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(tok.type == 11){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"[")){
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(tok.type == 9){
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,"]")){
                    return 1;
                }else return ERROR;
            }else return ERROR;
        }else{
            por_de_volta(tok);
            return 1;
        }
    }else return ERROR;
}

int cmd(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    int flag;
    token tok,taux;
    printf("ENTROU CMD\n");
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"if")){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"(")){
            expr(ptr);
            if(!strcmp(tok.value,")")){
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                cmd(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,"else")){
                    cmd(ptr);
                    return 1;
                }else{
                    por_de_volta(tok);
                    return 1;
                }
            }else return ERROR;
        }else return ERROR;
    }else if(!strcmp(tok.value,"while")){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"(")){
            expr(ptr);
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,")")){
                cmd(ptr);
                return 1;
            }else return ERROR;
        }else return ERROR;
    }else if(!strcmp(tok.value,"for")){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"(")){
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,";")){
                por_de_volta(tok);
                atrib(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,";")) return ERROR;
            }
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,";")){
                por_de_volta(tok);
                expr(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,";")) return ERROR;
            }
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,")")){
                por_de_volta(tok);
                atrib(ptr);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,")")) return ERROR;
            }
            cmd(ptr);
            return 1;
        }else return ERROR;
    }else if(!strcmp(tok.value,"return")){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(strcmp(tok.value,";")){
            expr(ptr);
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,";"))return ERROR;
            else return 1;
        }else return 1;
    }else if(tok.type == 11){
        taux = tok;
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(strcmp(tok.value,"(")){
            por_de_volta(taux);
            por_de_volta(tok);
            atrib(ptr);
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,";")) return 1;
            else return ERROR;
        }else{
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,")")){
                por_de_volta(tok);
                do{
                    expr(ptr);
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }while(!strcmp(tok.value,","));
                if(!strcmp(tok.value,")")){
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(!strcmp(tok.value,";")){
                        return 1;
                    }else return ERROR;
                }else return ERROR;
            }else{
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,";")){
                    return 1;
                }else return ERROR;
            }
        }
    }else if(!strcmp(tok.value,"{")){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        while(strcmp(tok.value,"}")){
            por_de_volta(tok);
            cmd(ptr);
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
        }
        return 1;
    }else if(!strcmp(tok.value,";")){
        return 1;
    }else return ERROR;

}

int expr(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    int flag;
    token tok;
    printf("ENTROU EXPR\n");
    expr_simp(ptr);
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"==") || !strcmp(tok.value,"!=") || !strcmp(tok.value,"<") || !strcmp(tok.value,"<=") || !strcmp(tok.value,">")  || !strcmp(tok.value,">=")){
        expr_simp(ptr);
        return 1;
    }else{
        por_de_volta(tok);
        return 1;
    }
}

int expr_simp(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    int flag;
    token tok;
    printf("ENTROU EXPR_SIMP\n");
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"+") || !strcmp(tok.value,"-")){
        termo(ptr);
    }else{
        por_de_volta(tok);
        termo(ptr);
    }
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    while((!strcmp(tok.value,"+")) || (!strcmp(tok.value,"-")) || (!strcmp(tok.value,"||")) ){
        termo(ptr);
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
    }
    por_de_volta(tok);
    return 1;
}

int termo(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    int flag;
    token tok;
    fator(ptr);
    printf("ENTROU TERMO\n");
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    while((!strcmp(tok.value,"*")) || (!strcmp(tok.value,"/")) || (!strcmp(tok.value,"&&")) ){
        fator(ptr);
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
    }
    por_de_volta(tok);
    return 1;
}

int fator(FILE *ptr){
    extern token fila_tokens[10];
    extern  int indice_fila;
    int flag;
    token tok;
    printf("ENTROU FATOR\n");
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(tok.type == 11){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if((!strcmp(tok.value,"("))){
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,")")){
                por_de_volta(tok);
                do{
                    expr(ptr);
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }while(!strcmp(tok.value,","));
                por_de_volta(tok);
                return 1;
            }
        }else if((!strcmp(tok.value,"["))){
            expr(ptr);
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,"]")) return 1;
            else return ERROR;
        }else{
            por_de_volta(tok);
            return 1;
        }
    }else if(!strcmp(tok.value,"(")){
        expr(ptr);
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,")")) return 1;
        else return ERROR;
    }else if(!strcmp(tok.value,"!")){
        fator(ptr);
        return 1;
    }else if(tok.type == 9){ //intcon
        return 1;
    }else if(tok.type == 25){ //realcon
        return 1;
    }else if(tok.type == 22){ //charcon
        return 1;
    }else return ERROR;
}

int atrib(FILE* ptr){
    extern token fila_tokens[10];
    extern int indice_fila;
    int flag;
    token tok;
    printf("ENTROU ATRIB\n");
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(tok.type == 11){
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"[")){
            expr(ptr);
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,"]")) return ERROR;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
        }
        if(!strcmp(tok.value,"=")){
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            expr(ptr);
            return 1;
        }else return ERROR;
    }else return ERROR;
}

void inicia_fila_tokens(){
    int i;
    extern token fila_tokens[10];
    extern int indice_fila;
    indice_fila = 0;
    for(i=0;i<5;i++){
        fila_tokens[i].type = -1;
        strcpy(fila_tokens[i].value,"");
    }
    return;
}

void get_token_fila(token* t){
    extern int indice_fila;
    extern token fila_tokens[10];
    int i;
    t->type = fila_tokens[0].type;
    strcpy(t->value,fila_tokens[0].value);
    for(i = 0;i<indice_fila-1;i++){
        fila_tokens[i] = fila_tokens[i+1];
    }
    remove_elemento_fila();
    return;
}

void por_de_volta(token t){
    extern int indice_fila;
    extern token fila_tokens[10];
    int i;
    indice_fila++;
    for(i = 0;i<indice_fila;i++){
        fila_tokens[i+1] = fila_tokens[i];
    }
    fila_tokens[0] = t;
    return;
}

void remove_elemento_fila(){
    extern int indice_fila;
    extern token fila_tokens[10];
    fila_tokens[indice_fila].type = -1;
    strcpy(fila_tokens[indice_fila].value,"");
    indice_fila--;
    return;
}

void imprimir_fila(){
    extern int indice_fila;
    extern token fila_tokens[10];
    int i;
    if(indice_fila==0) printf("--- FILA  VAZIA ---\n");
    for(i = 0;i<indice_fila;i++){
        printf("-- %10s --\n",fila_tokens[i].value);
    }
    return;
}
