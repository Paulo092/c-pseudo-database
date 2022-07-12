#include <stdio.h>
#include <stdlib.h>

char *errors(int num) {
    switch (num) {
        case 1:
            return "Erro 01: Comando nao existente\n";
            break;

        case 2:
            return "Erro 02: Tabela nao existe\n";
            break;
        case 3:
            return "Erro 03: Erro de sintaxe, faltando ';'\n";
            break;
        case 4:
            return "Erro 04: Esta tabela ja existe!\n";
            break;
            case 5:
            return "Erro 05: Erro de sintaxe!\n";
            break;

    }
}
