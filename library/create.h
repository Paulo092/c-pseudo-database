#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\\tables\\__meta.h"

int create(char tabela[50]) {
    char atributos[100][100], atr, palavra[100], *pp;
    int x = 0, a = 0, k;
    FILE *ctb;

    pp = palavra;

    printf("\nCREATE TABLE %s (\n", tabela);

    ctb = fopen("tables\\tabelas.h", "a");
    fprintf(ctb, "typedef struct {\n");

    do {
        printf("\t");
        scanf(" %[^\n]s\n", palavra);
        if (strcmp(palavra, ");")) {
            inverte(palavra);
            fprintf(ctb, "\t%s;\n", palavra);
            strcpy(atributos[a], palavra);
            a++;
        }
    } while(strcmp(palavra, ");"));

    fprintf(ctb, "} tab_%s;\n", tabela);

    fprintf(ctb, "tab_%s %s[100];\n", tabela, tabela);
    fprintf(ctb, "//%s", tabela);
    for(k = 0; k <= a; k++){
        fprintf(ctb, " %s", atributos[k]);
    }
    fprintf(ctb, "\n\n");

    fclose(ctb);

    char path[50] = {"tables\\"};
    strcat(path, tabela);
    strcat(path, ".dat");

    ctb = fopen(path, "wb");
    fclose(ctb);


    int i;
    FILE *metarch;
    metadata meta[100] = {};
    metarch = fopen("tables\\__meta.dat", "rb");

    fread(meta, sizeof(metadata), 100, metarch);

    for (i = 0; i < sizeof(meta)/sizeof(metadata); i++) {
        if (strcmp(meta[i].nome, "") == 0) {
            break;
        }
    }

    fclose(metarch);

    metarch = fopen("tables\\__meta.dat", "wb");

    strcpy(meta[i].nome, tabela);
    meta[i].qtd_tuplas = 0;
    fwrite(meta, sizeof(metadata), i+1, metarch);

    fclose(metarch);
}

int inverte(char *pal) {
    char nome[50], dominio[50], sentenca[100];
    int i = 0, j = 0;

    while (*(pal + i) != ' ') {
        nome[j] = *(pal + i);
        i++;
        j++;
    }

    nome[j] = '\0';

    j = 0;
    i++;

    while (*(pal + i) != '\0') {
        dominio[j] = *(pal + i);
        i++;
        j++;
    }

    dominio[j] = '\0';

    if (!strcmp(dominio, "varchar")) {
        strcpy(dominio, "char");
        strcat(nome, "[100]");
    }

    strcat(sentenca, dominio);
    strcat(sentenca, " ");
    strcat(sentenca, nome);

    i = 0;
    while (sentenca[i] != '\0') {
        *(pal + i) = sentenca[i];
        i++;
    }

}
