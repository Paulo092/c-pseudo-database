#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library/ajuda.h"
#include "library/create.h"
#include "library/insert.h"
#include "library/select.h"
#include "library/reset.h"
#include "library/show.h"
#include "library/utilities.h"
#include "library/errors.h"
#include "tables\\tabelas.h"

int *strtolow(char *string) {
    int i = 0;
    char upp[100];

    do {
        upp[i] = tolower(*(string + i));
        *(string + i) = upp[i];
        // printf("%c\n", upp[i]);
        i++;
    } while(string[i] != '\0');

}

char response(char query[100]) {
    int i = 0, j = 0, er, qnt = 1;
    char atrib[50] = "", ver[50] = "", tabela[50] = "", condicao[100] = "", from[4] = "", queryRest[100] = "", valores[100] = "";
    char split[100][100] = {}, comando[100] = {};

    strcpy(comando, query);
    // strtolow(&comando);
    // printf("%s\n", comando);

    int splen = strsplit(comando, ' ', split);

    // strtolow(&comando);

    if (!strcmp("\\?", query)) {
        ajuda();
    } else if(!strcmp(split[0], "create") && !strcmp(split[1], "table")){
        create(split[2]);
        //tem que fazer os parentese
    }else if(!strcmp(split[0], "insert") && !strcmp(split[1], "into") && !strcmp(split[3], "values")){
        for (i = 4; i < splen; i++) {
            strcat(valores, split[i]);
        }

        er = insert(split[2], valores);

        if (er != 0) {
            printf("%s", errors(er));
        }

        printf("Aviso: Tupla inserida com sucesso!!\n");
    } else if(!strcmp(split[0], "select")){
        char pathSelect[50] = "tables\\";
        i = 0;

        //guardar os atributos na var atrib
        do{
            memset(ver, 0, sizeof(ver));
            while(query[j] != ' '){
                ver[i] = query[j];
                j++;
                i++;
            }
            j++;
            if(strcmp(ver, "from") != 0 && strcmp(ver, "select") != 0){
                strcat(atrib, ver);
                strcat(atrib, " ");
            }
            i = 0;
        }while(strcmp(ver, "from") != 0);
        strcpy(from, ver);

        //guardar o restante na var queryRest
        memset(queryRest, 0, sizeof(queryRest));
        while(query[j] != '\0'){
            queryRest[i] = query[j];
            j++;
            i++;
            if(query[j] == ' '){
                qnt++;
            }
        }

        //guardar a tabela na var tabela
        if(qnt == 1){
            i = 0, j = 0;
            while(queryRest[j] != '\0'){
                tabela[i] = queryRest[j];
                j++;
                i++;
            }

        }else{
            i = 0, j = 0;
            while(queryRest[j] != ' '){
                tabela[i] = queryRest[j];
                j++;
                i++;
            }
        }

        //criando o caminho do arquivo
        strcat(pathSelect, tabela);
        strcat(pathSelect, ".dat");

        FILE *arqSelect;
        arqSelect = fopen(pathSelect, "rb");

        //verificar se o arquivo existe
        if(arqSelect != NULL){
            if(qnt == 1){
                //query sem condição
                select(atrib, tabela, condicao, qnt, pathSelect);
            }else if(qnt == 2){
                //query com condição não especificada, ERROR
                printf("%s", errors(5));
            }else{
                //query com condição
                j++;
                i = 0;
                //guardar where na var ver
                while(queryRest[j] != ' '){
                    ver[i] = queryRest[j];
                    j++;
                    i++;
                }
                j++;
                //verificar se foi escrito "where" corretamente
                if(strcmp(ver, "where") == 0){
                    i = 0;
                    while(queryRest[j] != '\0'){
                        condicao[i] = queryRest[j];
                        j++;
                        i++;
                    }

                    select(atrib, tabela, condicao, qnt, pathSelect);
                }else{
                    printf("%s", errors(5));
                }
            }
        }else{
            printf("%s", errors(2));
        }

        fclose(arqSelect);
    } else if (!strcmp(split[0], "show") && !strcmp(split[1], "tables")) {
        show();
    } else if (!strcmp(split[0], "reset")) {
        reset();
    } else if(!strcmp("sair", query)) {
        printf("Adeus!!\n");
    } else if(!strcmp("clear", query)) {
        system("cls");

        printf("CPDB. C Pseudo Data Base\n\n");

        printf("Desenvolvido por Paulo Sergio, Jhonata Kumaki.\n");
        printf("Digite \\? para ajuda\n");

    } else {
        printf("%s", errors(1));
    }


    //printf("%d\n", splen);

    // for (i = 0; i < strlen(split); i++) {
    //     // printf("%s\n", split[i]);
    //     printf("%d\n", i);
    // }

    // printf("%d\n", strinsen("paulo", split));

    //limpar vetor string
    for(i=0;i<6;i++){
        strcpy(split[i], "666");
    }
}
