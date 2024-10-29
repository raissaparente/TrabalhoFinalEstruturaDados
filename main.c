#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metodos.h"

int main() {
    Lista *lista = NULL;
    int opcao;

    do {
        printf("\n1. Cadastrar fruta\n2. Listar frutas\n3. Buscar fruta\n4. Alterar fruta\n5. Excluir fruta\n6. Vender fruta\n7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                interfaceCadastrarFruta(&lista);
                break;
            case 2:
                listarFrutas(lista);
                break;
            case 3:
                interfaceBuscarFruta(lista);
                break;
            case 4:
                interfaceAlterarFruta(lista);
                break;
            case 5:
                interfaceExcluirFruta(&lista);
                break;
            case 6:
                interfaceVenderFruta(lista);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}
