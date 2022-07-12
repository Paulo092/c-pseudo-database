#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reset() {

    int i;
    FILE *metarch;
    metadata meta[100] = {};
    char path[50] = {};
    metarch = fopen("tables\\__meta.dat", "rb");

    fread(meta, sizeof(metadata), 100, metarch);
    fclose(metarch);

    for (i = 0; i < sizeof(meta)/sizeof(metadata); i++) {
        if (!strcmp(meta[i].nome, "")) {
            break;
        }
        strcpy(path, "tables\\");
        strcat(path, meta[i].nome);
        strcat(path, ".dat");

        remove(path);
    }

    metarch = fopen("tables\\tabelas.h", "w");
    fprintf(metarch, "");
    fclose(metarch);

    metarch = fopen("tables\\__meta.dat", "w");
    fprintf(metarch, "");
    fclose(metarch);

    printf("Aviso: Banco de dados redefinido\n");
}
