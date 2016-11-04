#include "analex.h"


FILE* abrir_arquivo(char* arquivo){
    FILE *ptr;
    ptr = fopen(arquivo,"rt");
    if(ptr == NULL){
        printf("ERRO DE LEITURA DE ARQUIVO.\n");
        return NULL;
    }else{
        printf("ARQUIVO ABERTO\n");
        return ptr;
    }

}

int nextTokens(FILE *arquivo,token *lexema){
    char caracter_lido, token[20];
    int estado,indice_token;

    indice_token = 0;
    estado = 0;

    while(feof(arquivo) != EOF){
    caracter_lido = fgetc(arquivo);
        switch (estado){
            case  0:
                indice_token = 0;
                strcpy(token,"");
                if(isalpha(caracter_lido)){
                    token[indice_token++] = caracter_lido;
                    estado = 11;
                }else if(isdigit(caracter_lido)){
                    token[indice_token++] = caracter_lido;
                    estado = 9;
                }else if( caracter_lido == '['){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    lexema->type =1;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == ']'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =2;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '}'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type = 19;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '{'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =18;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '.'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =17;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '+'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =4;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '-'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =4;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '*'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =3;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '"'){
                    token[indice_token++] = caracter_lido;
                    estado = 27;
                }else if( caracter_lido == '\''){
                    token[indice_token++] = caracter_lido;
                    estado = 34;
                }else if( caracter_lido == ')'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =21;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '('){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =22;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '&'){
                    token[indice_token++] = caracter_lido;
                    estado = 32;
                }else if( caracter_lido == '|'){
                    token[indice_token++] = caracter_lido;
                    estado = 33;
                }else if( caracter_lido == ','){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =16;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if( caracter_lido == '>'){
                    token[indice_token++] = caracter_lido;
                    estado = 5;
                }else if( caracter_lido == '<'){
                    token[indice_token++] = caracter_lido;
                    estado = 5;
                }else if( caracter_lido == '='){
                    token[indice_token++] = caracter_lido;
                    estado = 24;
                }else if( caracter_lido == '/'){
                    token[indice_token++] = caracter_lido;
                    estado = 13;
                }else if( caracter_lido == '!'){
                    token[indice_token++] = caracter_lido;
                    estado = 7;
                }else if( caracter_lido == ';'){
                    token[indice_token++] = caracter_lido;
                    token[indice_token] = '\0';
                    (*lexema).type =23;
                    strcpy((*lexema).value,token);
                    return 1;
                }else if(caracter_lido == ' '){
                    estado = 0;
                }else if(caracter_lido == '\t'){
                    estado = 0;
                }else if(caracter_lido == '\n'){
                    estado = 0;
                }else if(caracter_lido == EOF){
                    return 0;
                }else{
                    return ERROR;
                }
            break;
            case  5:
                if(caracter_lido == '='){
                    token[indice_token++] = caracter_lido;
                    estado = 6;
                }else{
                    token[indice_token] = '\0';
                    (*lexema).type = estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case  6:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case  7:
                if(caracter_lido == '='){
                    token[indice_token++] = caracter_lido;
                    estado = 8;
                }else{
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case  8:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case  9:
                if(isdigit(caracter_lido)){
                    token[indice_token++] = caracter_lido;
                    estado = 9;
                }else if(caracter_lido == '.'){
                    token[indice_token++] = caracter_lido;
                    estado = 28;
                }else{
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case 10:
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                break;
            case 11:
                if(isalnum(caracter_lido)||(caracter_lido  == '_')){
                    token[indice_token++] = caracter_lido;
                    estado = 11;
                }else{
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case 12:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
		nextTokens(arquivo,lexema);                
		return 1;
                break;
            case 13:
                if(caracter_lido == '*'){
                    token[indice_token++] = caracter_lido;
                    estado = 29;
                }else{
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case 14:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case 15:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case 22:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case 23:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case 24:
                if(caracter_lido == '='){
                    token[indice_token++] = caracter_lido;
                    estado = 25;
                }else{
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case 25:
                if(isdigit(caracter_lido)){
                    token[indice_token++] = caracter_lido;
                    estado = 25;
                }
                else{
                    token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
                    return 1;
                }
                break;
            case 26:
                token[indice_token] = '\0';
                (*lexema).type =estado;
                strcpy((*lexema).value,token);
                ungetc(caracter_lido,arquivo);
                return 1;
                break;
            case 27:
                if((caracter_lido > 31) && (caracter_lido != '"')){
                    token[indice_token++] = caracter_lido;
                    estado = 27;
                }else if(caracter_lido == '"'){
                    token[indice_token++] = caracter_lido;
                    estado = 10;
                }else{
                    return ERROR;
                }
                break;
            case 28:
                if(isdigit(caracter_lido)){
                    token[indice_token++] = caracter_lido;
                    estado = 25;
                }else{
                    return ERROR;
                }
                break;
            case 29:
                if(caracter_lido == '*'){
                    token[indice_token++] = caracter_lido;
                    estado = 30;
                }else{
                    token[indice_token++] = caracter_lido;
                    estado = 31;
                }
                break;
            case 30:
                if(caracter_lido == '*'){
                    token[indice_token++] = caracter_lido;
                    estado = 30;
                }else if(caracter_lido == '/'){
                    token[indice_token++] = caracter_lido;
                    estado = 12;
                }
                break;
            case 31:
                if(caracter_lido == '*'){
                    token[indice_token++] = caracter_lido;
                    estado = 30;
                }else{
                    token[indice_token++] = caracter_lido;
                    estado = 31;
                }
                break;
            case 32:
                if(caracter_lido == '&'){
                    token[indice_token++] = caracter_lido;
                    estado = 14;
                }else{
		    		token[indice_token] = '\0';
                    (*lexema).type =estado;
                    strcpy((*lexema).value,token);
                    ungetc(caracter_lido,arquivo);
		    return 1;
                }
                break;
            case 33:
                if(caracter_lido == '|'){
                    token[indice_token++] = caracter_lido;
                    estado = 15;
                }else{
                    return ERROR;
                }
            break;
            case 34:
                if(caracter_lido == '\\'){
                    token[indice_token++] = caracter_lido;
                    estado = 36;
                }else if(isprint(caracter_lido)){
                    token[indice_token++] = caracter_lido;
                    estado = 35;
                }else {
                    return ERROR;
                }
                break;
            case 35:
                if(caracter_lido == '\''){
                    token[indice_token++] = caracter_lido;
                    estado = 22;
                }else{
                    return ERROR;
                }
                break;
            case 36:
                if((caracter_lido == 'n') || (caracter_lido == '0')){
                    token[indice_token++] = caracter_lido;
                    estado = 37;
                }else{
                    return ERROR;
                }
                break;
            case 37:
                if(caracter_lido == '\''){
                    token[indice_token++] = caracter_lido;
                    estado = 22;
                }else{
                    return ERROR;
                }
                break;
        }
    }
    return 1;
}

void porEmArrayDeTokens(char* token,int estado){
    strcpy(array_tokens[indice_token].value,token);
    array_tokens[indice_token].type = estado;
    indice_token++;
}

void imprimirArrayTokens(){
    int i;
    for(i = 0;i<indice_token;i++){
        printf("%c %-16s| %-26s | estado = %2d %c\n",186,estados_finais[array_tokens[i].type],array_tokens[i].value,array_tokens[i].type,186);
        printf("%c------------------------------------------------------------%c\n",200,188);
    }
}

