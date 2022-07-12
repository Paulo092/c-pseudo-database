#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valsplit(char string[100], char dl, char *splt) {
    int i = 0, j = 0, k = 0, splen = 0;

    for (i = 0; i < strlen(string); i++) {
        if (string[i] != dl) {
            *(splt + k) = string[i];
            k++;
        } else {
            *(splt + k) = '\0';
            splen++;
            j += 100;
            k = j;
        }
    }

    splen++;
    return splen;
}

int remchar(char *string, char ch) {
    int i = 0, x = 0;
    char ax;

    do {
        if (*(string + i) == ch) {
            x = 1;
            ax = *(string + i);
            *(string + i) = *(string + i + 1);
            *(string + i + 1) = ax;
        } else {
            i++;
        }
    } while(*(string + i) != '\0');

    return x;
}

int countpl(char nome[100]) {
    FILE *arq;
    int i;
    metadata resultado[100] = {};

    arq = fopen("tables\\__meta.dat", "rb");

    fread(resultado, sizeof(metadata), 100, arq);

    for (i = 0; i < 100; i++) {
        if (strcmp(resultado[i].nome, nome) == 0) {
            return resultado[i].qtd_tuplas;
        }
    }
}

int insert(char tabela[100], char valores[100]) {
    int i;
    FILE *iti, *temp;
    char path[50] = {"tables\\"}, tipo[50] = {}, comando[500] = {}, vals[100][100] = {};

    int splen = valsplit(valores, ',', vals);
    remchar(vals[0], '(');
    remchar(vals[splen-1], ')');

    strcat(path, tabela);
    strcat(path, ".dat");
    if (fopen(path, "r") == NULL) {
        return 2;
    } else if(remchar(vals[splen-1], ';') != 1) {
        return 3;
    }

    int qtpl = countpl(tabela);

    temp = fopen("temp.c", "w");

    fprintf(temp, "#include \"tables\\\\tabelas.h\"\n#include <stdio.h>\n#include <stdlib.h>\n", comando);
    fprintf(temp, "int main(){\ntab_%s %s[100] = {};", tabela, tabela);
    fprintf(temp, "\ntab_%s resposta = {", tabela);

    for (i = 0; i < splen; i++) {
        fprintf(temp, "%s", vals[i]);

        if (i != splen-1) {
            fprintf(temp, ", ");
        }
    }

    fprintf(temp, "};\n\n");
    fprintf(temp, "int i;\nFILE *arq;\narq = fopen(\"tables\\\\%s.dat\", \"rb\");\n\n", tabela);
    fprintf(temp, "fread(%s, sizeof(tab_%s), 100, arq);", tabela, tabela);
    fprintf(temp, "\nfclose(arq);\n\n");
    fprintf(temp, "%s[%d] = resposta;\n\n", tabela, qtpl);
    fprintf(temp, "arq = fopen(\"tables\\\\%s.dat\", \"wb\");\n", tabela);
    fprintf(temp, "fwrite(%s, sizeof(tab_%s), %d, arq);", tabela, tabela, qtpl+1);
    fprintf(temp, "\nfclose(arq);}");

    fclose(temp);


    system("gcc temp.c -o temp");
    system("temp.exe");
    remove("temp.c");
    system("del temp.exe");

    FILE *metarch;
    metadata meta[100] = {};
    metarch = fopen("tables\\__meta.dat", "rb");

    fread(meta, sizeof(metadata), 100, metarch);

    for (i = 0; i < sizeof(meta)/sizeof(metadata); i++) {
        if (strcmp(meta[i].nome, tabela) == 0) {
            meta[i].qtd_tuplas++;
        } else if (strcmp(meta[i].nome, "") == 0){
            break;
        }
    }

    fclose(metarch);

    metarch = fopen("tables\\__meta.dat", "wb");

    fwrite(meta, sizeof(metadata), i, metarch);

    fclose(metarch);

    return 0;
}
