#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "..\\tables\\tabelas.h"

int select(char atrib[100], char tabela[100], char condicao[100], int x, char pathSelect[100]) {
    // printf("atrib: %s\ntabela: %s\n", atrib, tabela);
    // printf("x: %d\n", x);
    FILE *arqSelect = fopen(pathSelect, "rb");
    FILE *arqTabelas = fopen("tables\\tabelas.h", "r");
    int i = 0, j = 0, k = 0, qntAtrib = 0, a = 0, b = 0, z = 0;
    char structTabela[50] = "tab_", tipoAtrib[20][20] = {}, varAtributo[50][50] = {}, ver[50] = "", palavra[100] = "";
    strcat(structTabela, tabela);


    FILE *metarch;
    metadata meta[100] = {};
    char path[50] = {};
    metarch = fopen("tables\\__meta.dat", "rb");

    fread(meta, sizeof(metadata), 100, metarch);
    fclose(metarch);

    for (i = 0; i < sizeof(meta)/sizeof(metadata); i++) {
        if (!strcmp(meta[i].nome, tabela)) {
            z = meta[i].qtd_tuplas;
            break;
        } else if (!strcmp(meta[i].nome, "")) {
            break;
        }

    }


    if(x == 1){
        if(strcmp(atrib, "* ") == 0){

            while(feof(arqTabelas) == 0 && strcmp(ver, tabela) != 0){
                memset(palavra, 0, sizeof(palavra));
                memset(ver, 0, sizeof(ver));
                fscanf(arqTabelas, " %[^\n]s", palavra);
                if(palavra[0] == '/'){
                    i = 2, j = 0;
                    while(palavra[i] != ' '){
                        ver[j] = palavra[i];
                        i++;j++;
                    }
                }
            }
            i++;
            j = i;
            while(palavra[i] != '\0'){
                if(palavra[i] == ' '){
                    qntAtrib++;
                }
                i++;
            }
            i = j;
            j = 0;
            k = qntAtrib / 2;
            while(k != 0){
                a = 0, b = 0;
                while(palavra[i] != ' '){
                    tipoAtrib[j][a] = palavra[i];
                    i++;
                    a++;
                }
                i++;
                while(palavra[i] != ' '){
                    varAtributo[j][b] = palavra[i];
                    i++;
                    b++;
                    if(palavra[i] == '['){
                        i+=5;
                    }
                }
                i++;
                j++;
                k--;
            }
            k = qntAtrib / 2;

            i = 0, j = 0;
            FILE *arqTempSelect;
            arqTempSelect = fopen("temp.c", "w");


            fprintf(arqTempSelect, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include \"tables\\\\tabelas.h\"\n\nint main(){\n");
            fprintf(arqTempSelect, "\tint i;\n");
            fprintf(arqTempSelect, "\tFILE *arqSelect = fopen(\"tables\\\\%s.dat\", \"rb\");\n", tabela);
            fprintf(arqTempSelect, "\tfread(%s, sizeof(%s), 100, arqSelect);\n", tabela, structTabela);

            //automatizar essa parte
            fprintf(arqTempSelect, "\tfor(i = 0; i <= 100; i++){\n");

            fprintf(arqTempSelect, "\t\tif(");
            for(i = 0; i < k; i++){
                if(i != k - 1){
                    if(strcmp(tipoAtrib[i], "char") == 0){
                        fprintf(arqTempSelect, "strcmp(%s[i].%s, \"\") != 0 || ", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "int") == 0){
                        fprintf(arqTempSelect, "%s[i].%s != 0 || ", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "double") == 0){
                        fprintf(arqTempSelect, "%s[i].%s != 0.0 || ", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "float") == 0){
                        fprintf(arqTempSelect, "%s[i].%s != 0.0 || ", tabela, varAtributo[i]);
                    }
                }else{
                    if(strcmp(tipoAtrib[i], "char") == 0){
                        fprintf(arqTempSelect, "strcmp(%s[i].%s, \"\") != 0", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "int") == 0){
                        fprintf(arqTempSelect, "%s[i].%s != 0", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "double") == 0){
                        fprintf(arqTempSelect, "%s[i].%s != 0.0", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "float") == 0){
                        fprintf(arqTempSelect, "%s[i].%s != 0.0", tabela, varAtributo[i]);
                    }
                }
            }
            fprintf(arqTempSelect, "){\n");


            for(i = 0; i < k; i++){
                if(i != k - 1){
                    if(strcmp(tipoAtrib[i], "char") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%s\\t\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "int") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%d\\t\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "double") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%.2f\\t\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "float") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%.2f\\t\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }
                }else{
                    if(strcmp(tipoAtrib[i], "char") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%s\\n\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "int") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%d\\n\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "double") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%.2f\\n\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }else if(strcmp(tipoAtrib[i], "float") == 0){
                        fprintf(arqTempSelect, "\t\t\tprintf(\"\%\%.2f\\n\", %s[i].%s);\n", tabela, varAtributo[i]);
                    }
                }
            }

            fprintf(arqTempSelect, "\t\t}\n");
            fprintf(arqTempSelect, "\t}\n");

            fprintf(arqTempSelect, "\tfclose(arqSelect);\n");
            fprintf(arqTempSelect, "}");

            fclose(arqTempSelect);

            if(z != 0){
                printf("\n");
                for(i = 0; i < k; i++){
                    printf("| %s ", varAtributo[i]);
                }

                printf("|\n\n");

                system("gcc temp.c -o temp");
                system("temp.exe");
                remove("temp.c");
                system("del temp.exe");
            }else{
                printf("Aviso: Nenhuma tupla retornada\n");
            }

        }
        // printf("atrib: %s\ntabela: %s\n", atrib, tabela);
    }else{
        printf("atrib: %s\ntabela: %s\ncondicao: %s\n", atrib, tabela, condicao);
    }

    printf("");
    fclose(arqTabelas);
    fclose(arqSelect);
}
