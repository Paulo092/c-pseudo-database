#include <stdio.h>
#include <stdlib.h>

int show() {
    int i;
    FILE *metarch;
    metadata meta[100] = {};
    metarch = fopen("tables\\__meta.dat", "rb");

    fread(meta, sizeof(metadata), 100, metarch);
    fclose(metarch);

    printf("+-------------------------------------------------+\n");
    printf("|                TABELAS DO BANCO                 |\n");
    printf("+-------------------------------------------------+\n");
    for (i = 0; i < sizeof(meta)/sizeof(metadata); i++) {
        if (!strcmp(meta[i].nome, "")) {
            break;
        }
        printf("|  %s\n", meta[i].nome);

    }
    printf("+-------------------------------------------------+\n");
}
