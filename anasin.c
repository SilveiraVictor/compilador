#include <stdio.h>
#include "analex.h"
#include "anasin.h"
#include "simboltable.h"

/*
Lembrar de usar o retorno das funcoesc
*/

extern nodo_simbol pilha[TAM_PILHA];
extern int ind;

int inicia_sintatico(FILE* ptr){
    int flag;
    token tok,taux;
    extern int indice_fila;
    extern token fila_tokens[TAM_FILA];
    inicia_fila_tokens();
    flag = nextTokens(ptr,&tok);
    if(flag != 1) return flag;
    if( (! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
        fila_tokens[indice_fila++] = tok;
    }else if (!strcmp(tok.value,"void")){
        fila_tokens[indice_fila++] = tok;
    }else return SINTAX_ERROR;
    flag = nextTokens(ptr,&tok);
    if(flag != 1) return flag;
    if(tok.type != 11) return SINTAX_ERROR;
    fila_tokens[indice_fila++] = tok;
    flag = nextTokens(ptr,&tok);
    if(flag != 1) return flag;
    fila_tokens[indice_fila++] = tok;
    if(!strcmp(tok.value,"[") || !strcmp(tok.value,",") || !strcmp(tok.value,";")){
		//printf("primeiro if\n");
        flag = decl(ptr);
		if(flag != 1) return flag;
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
		//printf("val = %s\n",tok.value);
        if(!strcmp(tok.value,";"))return 1;
        else return SINTAX_ERROR;
    }else if(!strcmp(tok.value,"(")){
			//printf("if else\n");
            do{
				//printf("do\n");
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
                fila_tokens[indice_fila++] = tok;
            }while(strcmp(tok.value,")"));
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
                fila_tokens[indice_fila++] = tok;
            if(!strcmp(tok.value,";")){
                flag = decl(ptr);
				if(flag != 1) return flag;
                return 1;
            }else if(!strcmp(tok.value,",")){
                flag = decl(ptr);
				if(flag != 1) return flag;
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,";"))return 1;
                else return SINTAX_ERROR;
            }else if(!strcmp(tok.value,"{")){
                flag = func(ptr);
				if(flag != 1) return flag;
                return 1;
            }else return SINTAX_ERROR;
    }else return SINTAX_ERROR;
}

int decl(FILE *ptr){
    extern int indice_fila;
    extern token fila_tokens[TAM_FILA];
    token tok, taux;
    int i=0,flag;
    int lastType;
    printf("ENTROU EM DECL\n");
	//imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"void")){
		//printf("encontrou void\n");
		do{
			set_tipo(pilha,VOID,&ind);
			set_categoria(pilha,FUNC,&ind);
			set_escopo(pilha,0,&ind);
			set_zombie(pilha,1,&ind);
		    if(indice_fila > 0){
		       get_token_fila(&tok);
		    }else{
		        flag = nextTokens(ptr,&tok);
		        if(flag != 1) return flag;
		    }
            if(tok.type == 11){
				//printf("DECL encontrou ID\n");
				if(procurar_elemento(tok.value,0,pilha,&ind) != -1) return ERROR_SIMBOL;                
				set_nome(pilha,tok.value,&ind);ind++;
				if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;                                              
                }
                if(!strcmp(tok.value,"(")){
						//printf("DECL encontrou (\n");
                        flag = tipo_param(ptr,1,NULL);
						if(flag != 1) return flag;
						//imprimir_fila();
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                        }
                        if(!strcmp(tok.value,")")){
                            //printf("DECL encontrado )\n");
							if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                        }else return SINTAX_ERROR;
                }else return SINTAX_ERROR;
            }else return SINTAX_ERROR;
        }while(!strcmp(tok.value,","));
        por_de_volta(tok);
        return 1;
    }else if((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
		//printf("encontrou tipo\n");        
		if(!strcmp(tok.value,"char")){set_tipo(pilha,CHAR,&ind); lastType = CHAR;
		}else if((!strcmp(tok.value,"int"))){ set_tipo(pilha,INT,&ind); lastType = INT;
		}else if((!strcmp(tok.value,"float"))){ set_tipo(pilha,FLOAT,&ind);lastType = FLOAT;
		}else{ set_tipo(pilha,BOOL,&ind);lastType = BOOL; }
		do{
			set_escopo(pilha,0,&ind);			
			set_tipo(pilha,lastType,&ind);
			set_categoria(pilha,FUNC,&ind);
			if(indice_fila > 0){
		    	get_token_fila(&tok);
			}else{
			    flag = nextTokens(ptr,&tok);
		   	 	if(flag != 1) return flag;
			}
		    if(tok.type == 11){
				 //printf("encontrou ID\n");            
				taux = tok;
		        if(indice_fila > 0){
		            get_token_fila(&tok);
		        }else{
		            flag = nextTokens(ptr,&tok);
		            if(flag != 1) return flag;
		        }
		        if(!strcmp(tok.value,"(")){
					if(procurar_elemento(taux.value,0,pilha,&ind) != -1) return ERROR_SIMBOL;                
					set_zombie(pilha,1,&ind);					
					set_nome(pilha,taux.value,&ind);ind++;				
					 //printf("enc (\n");                
					flag = tipo_param(ptr,1,NULL);
					if(flag != 1) return flag;
		            if(indice_fila > 0){
		                get_token_fila(&tok);
		            }else{
		                flag = nextTokens(ptr,&tok);
		                if(flag != 1) return flag;
		            }
		            if(!strcmp(tok.value,")")){
						 //printf("enc )\n");                    
						if(indice_fila > 0){
		                    get_token_fila(&tok);
		                }else{
		                    flag = nextTokens(ptr,&tok);
		                    if(flag != 1) return flag;
		                }
						//printf("val = %s\n",tok.value);
		            }else return SINTAX_ERROR;
		        }else{
		            por_de_volta(tok);
		            por_de_volta(taux);
		            do{
		                flag = decl_var(ptr,0,lastType);
						if(flag != 1) return flag;
		                if(indice_fila > 0){
		                    get_token_fila(&tok);
		                }else{
		                    flag = nextTokens(ptr,&tok);
		                    if(flag != 1) return flag;
		                }
		            }while(!strcmp(tok.value,","));
					por_de_volta(tok);
					//printf("passou do while\n");
		            return 1;
		        }
		    }else return SINTAX_ERROR;
			//printf("val = %s\n",tok.value);
    	}while(!strcmp(tok.value,","));
    	por_de_volta(tok);
		//printf("chegogu nesse\n");
		return 1;    
	}else return SINTAX_ERROR;
}

int func(FILE* ptr){
    extern int indice_fila;
    extern token fila_tokens[TAM_FILA];
    token tok;
    int i=0,flag,lastType,pos;
    printf("ENTROU EM FUNC\n");
    //imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if( (!strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool")) || (!strcmp(tok.value,"void"))){
		//printf("FUNC TIPO\n");
		if(!strcmp(tok.value,"char")){lastType = CHAR;
		}else if((!strcmp(tok.value,"int"))){lastType = INT;
		}else if((!strcmp(tok.value,"float"))){lastType = FLOAT;
		}else{lastType = BOOL;}        
		if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(tok.type == 11){
			//printf("FUNC ID\n");
			pos = procurar_elemento(tok.value,0,pilha,&ind);
			if(pos != -1){
				if(conferir_tipo_func(lastType,pilha,pos) == 0)return ERROR_SIMBOL;
			}            
			if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,"(")){
				//printf("FUNC (\n");
//                if(indice_fila > 0){
//                    get_token_fila(&tok);
//                }else{
//                    flag = nextTokens(ptr,&tok);
//                    if(flag != 1) return flag;
//                }
                flag = tipo_param(ptr,0,NULL);
				if(flag != 1) return flag;
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
                        while((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool")) ){
							if(!strcmp(tok.value,"char")){lastType = CHAR;
							}else if((!strcmp(tok.value,"int"))){ lastType = INT;
							}else if((!strcmp(tok.value,"float"))){ lastType = FLOAT;
							}else{lastType = BOOL; }
                            do{
		                        flag = decl_var(ptr,1,lastType);
								if(flag != 1) return flag;
		                        if(indice_fila > 0){
		                            get_token_fila(&tok);
		                        }else{
		                            flag = nextTokens(ptr,&tok);
		                            if(flag != 1) return flag;
		                        }
                            }while(!strcmp(tok.value,","));

                            if(!strcmp(tok.value,";")){
                            }else return SINTAX_ERROR;

                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                        }
                        while(strcmp(tok.value,"}")){
							por_de_volta(tok);
                            flag = cmd(ptr);
							if(flag != 1) return flag;
                            if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                        }
                        return 1;
                    }else return SINTAX_ERROR;
                }else return SINTAX_ERROR;
            }else return SINTAX_ERROR;
        }else return SINTAX_ERROR;
    }else return SINTAX_ERROR;
}

int tipo_param(FILE* ptr,int isDecl,int *tipos){
    extern token fila_tokens[TAM_FILA];
    extern int indice_fila;
    token tok;
    int flag;
    printf("ENTROU TIPO_PARAM\n");
    //imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(!strcmp(tok.value,"void")){
		 //printf("encontrado void\n");
        return 1;
    }else if((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool"))){
		 //printf("encontrado tipo\n");		
		do{ 
			if(isDecl){       
				if(!strcmp(tok.value,"char")){set_tipo(pilha,CHAR,&ind);
				}else if((!strcmp(tok.value,"int"))){ set_tipo(pilha,INT,&ind);
				}else if((!strcmp(tok.value,"float"))){ set_tipo(pilha,FLOAT,&ind);
				}else{ set_tipo(pilha,BOOL,&ind);}
				set_escopo(pilha,0,&ind);
				set_categoria(pilha,PARAM,&ind);
				set_zombie(pilha,1,&ind);			
			}
			if(indice_fila > 0){
            	get_token_fila(&tok);
		    }else{
		        flag = nextTokens(ptr,&tok);
		        if(flag != 1) return flag;
       	 	}
            if(tok.type == 11){
				 //printf("encontrado ID\n");
				if(isDecl){				
					if(procurar_elemento(tok.value,0,pilha,&ind) != -1) return ERROR_SIMBOL;
					set_nome(pilha,tok.value,&ind);ind++;
				}                
				if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,"[")){
				   //printf("encontrado [\n");
                   if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(!strcmp(tok.value,"]")){
						//printf("encontrado ]\n");
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                        }
                        if(!strcmp(tok.value,",")){
							//printf("encontrado ,\n");                            
							if(indice_fila > 0){
                                get_token_fila(&tok);
                            }else{
                                flag = nextTokens(ptr,&tok);
                                if(flag != 1) return flag;
                            }
                            if(!((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool")))) return SINTAX_ERROR;
                        }else{
							//printf("pos de volta\n");
                            por_de_volta(tok);
                            return 1;
                        }
                    }
                    else return SINTAX_ERROR;
                }else if(!strcmp(tok.value,",")){
					 //printf("encontrado ,\n");
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
				 //printf("encontrado &\n");
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(tok.type == 11){
					//printf("encontrado ID\n");
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(strcmp(tok.value,",")){
						//printf("encontrado ,\n");
                        if(indice_fila > 0){
                            get_token_fila(&tok);
                        }else{
                            flag = nextTokens(ptr,&tok);
                            if(flag != 1) return flag;
                	        }
                        if(!((! strcmp(tok.value,"char")) || (!strcmp(tok.value,"int")) || (!strcmp(tok.value,"float")) || (!strcmp(tok.value,"bool")))) return SINTAX_ERROR;
                    }else{
                        por_de_volta(tok);
                        return 1;
                    }
                }else return SINTAX_ERROR;
            }else return SINTAX_ERROR;
        }while(1);
    }else return SINTAX_ERROR;
}

int decl_var(FILE* ptr,int escopo, int tipo){
    extern token fila_tokens[TAM_FILA];
    extern int indice_fila;
    int flag,size;
    token tok;
    printf("ENTROU DECL_VAR\n");
    //imprimir_fila();
	set_escopo(pilha,escopo,&ind);
	set_tipo(pilha,tipo,&ind);
	set_categoria(pilha,VAR,&ind);
	set_zombie(pilha,0,&ind);
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(tok.type == 11){
		if( procurar_elemento(tok.value,escopo,pilha,&ind) != -1) return ERROR_SIMBOL;		
		set_nome(pilha,tok.value,&ind);
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
				size = atoi(tok.value);				
				set_tamanho(pilha,size,&ind);
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,"]")){
					ind++;                
				    return 1;
                }else return SINTAX_ERROR;
            }else return SINTAX_ERROR;
        }else{
            por_de_volta(tok);
			ind++;
            return 1;
        }
    }else return SINTAX_ERROR;
}

int cmd(FILE* ptr){
    extern token fila_tokens[TAM_FILA];
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
	//printf("val = %s\n",tok.value);
    if(!strcmp(tok.value,"if")){
		//printf("CMD IF\n");
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"(")){
			//printf("CMD (\n");
            flag = expr(ptr);
			if(flag != 1) return flag;
			if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,")")){
				//printf("CMD )\n");
                //if(indice_fila > 0){
                //    get_token_fila(&tok);
                //}else{
                //    flag = nextTokens(ptr,&tok);
                //    if(flag != 1) return flag;
                //}
                flag = cmd(ptr);
				if(flag != 1) return flag;
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,"else")){
					//printf("CMD ELSE\n");
                    flag = cmd(ptr);
					if(flag != 1) return flag;
                    return 1;
                }else{
                    por_de_volta(tok);
                    return 1;
                }
            }else return SINTAX_ERROR;
        }else return SINTAX_ERROR;
    }else if(!strcmp(tok.value,"while")){
		//printf("CMD WHILE\n");
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"(")){
			//printf("CMD (\n");
            flag = expr(ptr);
			if(flag != 1) return flag;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,")")){
				//printf("CMD )\n");
                flag = cmd(ptr);
				if(flag != 1) return flag;
                return 1;
            }else return SINTAX_ERROR;
        }else return SINTAX_ERROR;
    }else if(!strcmp(tok.value,"for")){
		//printf("CMD FOR\n");
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"(")){
			//printf("CMD (\n");
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,";")){
				//printf("CMD ;\n");
                por_de_volta(tok);
                flag = atrib(ptr);
				if(flag != 1) return flag;
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,";")) return SINTAX_ERROR;
            }
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,";")){
				//printf("CMD != ;\n");
                por_de_volta(tok);
                flag = expr(ptr);
				if(flag != 1) return flag;
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,";")) return SINTAX_ERROR;
            }
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,")")){
				//printf("CMD )\n");
                por_de_volta(tok);
                flag = atrib(ptr);
				if(flag != 1) return flag;
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(strcmp(tok.value,")")) return SINTAX_ERROR;
            }
            flag = cmd(ptr);
			if(flag != 1) return flag;
            return 1;
        }else return SINTAX_ERROR;
    }else if(!strcmp(tok.value,"return")){
		//printf("CMD return\n");
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(strcmp(tok.value,";")){
			//printf("CMD != ;\n");
			por_de_volta(tok);
            flag = expr(ptr);
			if(flag != 1) return flag;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,";"))return SINTAX_ERROR;
            else return 1;
        }else return 1;
    }else if(tok.type == 11){
		//printf("CMD ID\n");
        taux = tok;
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(strcmp(tok.value,"(")){
			//printf("CMD (\n");
            por_de_volta(tok);
            por_de_volta(taux);
            flag = atrib(ptr);
			if(flag != 1) return flag;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,";")) return 1;
            else return SINTAX_ERROR;
        }else{
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,")")){
				//printf("CMD != )\n");
                por_de_volta(tok);
                do{
                    flag = expr(ptr);
					if(flag != 1)return flag;
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }while(!strcmp(tok.value,","));
                if(!strcmp(tok.value,")")){
					//printf("CMD )\n");
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                    if(!strcmp(tok.value,";")){
						//printf("cmd ;\n");
                        return 1;
                    }else return SINTAX_ERROR;
                }else return SINTAX_ERROR;
            }else{
                if(indice_fila > 0){
                    get_token_fila(&tok);
                }else{
                    flag = nextTokens(ptr,&tok);
                    if(flag != 1) return flag;
                }
                if(!strcmp(tok.value,";")){
                    return 1;
                }else return SINTAX_ERROR;
            }
        }
    }else if(!strcmp(tok.value,"{")){
		//printf("CMD {\n");
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        while(strcmp(tok.value,"}")){
			//printf("CMD }\n");            
			por_de_volta(tok);
            flag = cmd(ptr);
			if(flag != 1) return flag;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
        }
        return 1;
    }else if(!strcmp(tok.value,";")){
        //printf("CMD ;\n");
        return 1;
    }else return SINTAX_ERROR;

}

int expr(FILE* ptr){
    extern token fila_tokens[TAM_FILA];
    extern int indice_fila;
    int flag;
    token tok;
    printf("ENTROU EXPR\n");
    flag = expr_simp(ptr);
	if(flag != 1) return flag;    
	if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
	//printf("val = %s\n",tok.value);
    if( (!strcmp(tok.value,"==")) || (!strcmp(tok.value,"!=")) || (!strcmp(tok.value,"<")) || (!strcmp(tok.value,"<=")) || (!strcmp(tok.value,">"))  || (!strcmp(tok.value,">=")) ){
        flag = expr_simp(ptr);
		if(flag != 1) return flag;
        return 1;
    }else{
        por_de_volta(tok);
        return 1;
    }
}

int expr_simp(FILE* ptr){
    extern token fila_tokens[TAM_FILA];
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
	//printf("EXSIM read 1 val = %s\n",tok.value);
    if(!strcmp(tok.value,"+") || !strcmp(tok.value,"-")){
		//printf("EXPSIM +-\n");
        flag = termo(ptr);
		if(flag != 1)return flag;
    }else{
		//printf("EXPSIM s/ +-\n");
        por_de_volta(tok);
        flag = termo(ptr);
		if(flag != 1)return flag;
    }
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    while((!strcmp(tok.value,"+")) || (!strcmp(tok.value,"-")) || (!strcmp(tok.value,"||")) ){
		//printf("EXPSIM while +-||\n");        
		flag = termo(ptr);
		if(flag != 1) return flag;
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
    extern token fila_tokens[TAM_FILA];
    extern int indice_fila;
    int flag;
    token tok;
	printf("ENTROU TERMO\n");
    flag = fator(ptr);
	if(flag != 1) return flag;    
	if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
	//printf("TERM %s\n",tok.value);
    while((!strcmp(tok.value,"*")) || (!strcmp(tok.value,"/")) || (!strcmp(tok.value,"&&")) ){
		flag = fator(ptr);
		if(flag != 1) return flag;
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
    extern token fila_tokens[TAM_FILA];
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
	//printf("FAT val = %s\n",tok.value);
    if(tok.type == 11){
		//printf("id found\n");        
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
					//printf("entrou do\n");
                    flag = expr(ptr);
					if(flag != 1)return flag;
                    if(indice_fila > 0){
                        get_token_fila(&tok);
                    }else{
                        flag = nextTokens(ptr,&tok);
                        if(flag != 1) return flag;
                    }
                }while(!strcmp(tok.value,","));
				if(strcmp(tok.value,")")) return SINTAX_ERROR;
                return 1;
            }else return 1;
        }else if((!strcmp(tok.value,"["))){
            flag = expr(ptr);
			if(flag != 1)return flag;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(!strcmp(tok.value,"]")) return 1;
            else return SINTAX_ERROR;
        }else{
            por_de_volta(tok);
            return 1;
        }
    }else if(!strcmp(tok.value,"(")){
		//printf("( found\n");
        flag = expr(ptr);
		if(flag != 1)return flag;
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,")")) return 1;
        else return SINTAX_ERROR;
    }else if(!strcmp(tok.value,"!")){
		//printf("! found\n");
        flag = fator(ptr);
		if(flag != 1) return flag;        
		return 1;
    }else if(tok.type == 9){ //intcon
		//printf("FAT intcon\n");
        return 1;
    }else if(tok.type == 25){ //realcon
		//printf("25 found\n");
        return 1;
    }else if(tok.type == 22){ //charcon
		//printf("22 found\n");
        return 1;
    }else{ 
		//printf("Sintax error\n");	
		return SINTAX_ERROR;
	}
}

int atrib(FILE* ptr){
    extern token fila_tokens[TAM_FILA];
    extern int indice_fila;
    int flag;
    token tok;
    printf("ENTROU ATRIB\n");
	//imprimir_fila();
    if(indice_fila > 0){
        get_token_fila(&tok);
    }else{
        flag = nextTokens(ptr,&tok);
        if(flag != 1) return flag;
    }
    if(tok.type == 11){ 
		//printf("ATT ID\n");
        if(indice_fila > 0){
            get_token_fila(&tok);
        }else{
            flag = nextTokens(ptr,&tok);
            if(flag != 1) return flag;
        }
        if(!strcmp(tok.value,"[")){
			//printf("ATT [\n");				            
			flag = expr(ptr);
			if(flag != 1)return flag;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
            if(strcmp(tok.value,"]")) return SINTAX_ERROR;
            if(indice_fila > 0){
                get_token_fila(&tok);
            }else{
                flag = nextTokens(ptr,&tok);
                if(flag != 1) return flag;
            }
        }
        if(!strcmp(tok.value,"=")){
			//printf("ATT =\n");
            flag = expr(ptr);
			if(flag != 1)return flag;
            return 1;
        }else return SINTAX_ERROR;
    }else return SINTAX_ERROR;
}

void inicia_fila_tokens(){
    int i;
    extern token fila_tokens[TAM_FILA];
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
    extern token fila_tokens[TAM_FILA];
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
    extern token fila_tokens[TAM_FILA];
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
    extern token fila_tokens[TAM_FILA];
    fila_tokens[indice_fila].type = -1;
    strcpy(fila_tokens[indice_fila].value,"");
    indice_fila--;
    return;
}

void imprimir_fila(){
    extern int indice_fila;
    extern token fila_tokens[TAM_FILA];
    int i;
    if(indice_fila==0) 	("--- FILA  VAZIA ---\n");
    for(i = 0;i<indice_fila;i++){
        printf("-- %10s --\n",fila_tokens[i].value);
    }
    return;
}
