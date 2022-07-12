#include <stdio.h>
#include <stdlib.h>

void ajuda() {
    printf("\nComando\t\t\t\t\t\t\tDescricao\n\n");

    printf("create table <nome_tabela>\t\t\t\tCria tabelas.\n");
    printf("insert into <nome_tabela> VALUES <valores>\t\tInsere elementos em uma tabela.\n");
    printf("select * from <nome_tabela>\t\t\t\tSeleciona todos as tuplas e atributos de uma tabela.\n");
    printf("show tables \t\t\t\t\t\tMostra as tabelas presentes no banco de dados\n");
    printf("reset \t\t\t\t\t\t\tRedefine o banco de dados (Aviso: Exclui todas as tabelas e dados)");

    printf("\n\n");
    system("pause");
}
