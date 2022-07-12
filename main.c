#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "response.h"

int main() {
    char query[100] = "";

    printf("CPDB. C Pseudo Data Base\n\n");

    printf("Desenvolvido por Paulo Sergio, Jhonata Kumaki.\n");
    printf("Digite \\? para ajuda\n");

    do {
        printf("\nQuery>>> ");
        scanf(" %[^\n]s", query);

        response(query);
    } while(strcmp(query, "sair"));
}
