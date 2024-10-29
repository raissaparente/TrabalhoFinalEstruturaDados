#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[50];
    int quantidade;
    float preco;
}Fruta;

typedef struct lista {
    Fruta fruta; 
    struct lista *prox;
}Lista;

// FUNCOES PRINCIPAIS
Fruta* buscarFruta(Lista *lista, int codigo);
int cadastrarFruta(Lista **lista, Fruta fruta); 
void listarFrutas(Lista *lista);
void excluirFruta(Lista **lista, int codigo); 
int venderFruta(Lista *lista, int codigo, int quantidade);
void alterarFruta(Fruta *fruta);

// FUNCOES DE INTERFACE 
void interfaceBuscarFruta(Lista *lista);
void interfaceCadastrarFruta(Lista **lista); 
void interfaceExcluirFruta(Lista **lista); 
void interfaceVenderFruta(Lista *lista);
void interfaceAlterarFruta(Lista *lista);

Fruta* buscarFruta(Lista *lista, int codigo) {
    Lista *listaAux = lista;
    while (listaAux != NULL) {
        if (listaAux->fruta.id == codigo) {
            return &listaAux->fruta;
        }
        listaAux = listaAux->prox;
    }
    return NULL;
}

int cadastrarFruta(Lista **lista, Fruta fruta) {
    //checa se já tem essa fruta
    if (buscarFruta(*lista, fruta.id) != NULL) {
        printf("Erro: Código de fruta já cadastrado!\n");
        return 0;
    }

    Lista *novoNodo = (Lista*) malloc(sizeof(Lista));

    novoNodo->fruta = fruta;
    novoNodo->prox = *lista;
    *lista = novoNodo; //atualiza a lista

    printf("Fruta cadastrada com sucesso!\n");
    return 1;
}

void listarFrutas(Lista *lista) {
    Lista *listaAux = lista;

    //checa se a lista nao ta vazia
    if (listaAux == NULL) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    printf("Lista de frutas:\n");
    while (listaAux != NULL) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", 
               listaAux->fruta.id, listaAux->fruta.nome, 
               listaAux->fruta.quantidade, listaAux->fruta.preco);
        listaAux = listaAux->prox;
    }
}

void alterarFruta(Fruta *fruta) {

    printf("Digite o novo nome da fruta: ");
    scanf("%s", fruta->nome);
    printf("Digite a nova quantidade: ");
    scanf("%d", &fruta->quantidade);
    printf("Digite o novo preco: ");
    scanf("%f", &fruta->preco);

    printf("Fruta alterada com sucesso!\n");
}


void excluirFruta(Lista **lista, int codigo) {

    if (*lista == NULL) {
        printf("Erro: Não há fruta no mercado!\n");
        return;
    }
    Lista *anterior = NULL; 
    Lista *listaAux = *lista;

    while (listaAux != NULL && listaAux->fruta.id != codigo) {
        anterior = listaAux;
        listaAux = listaAux->prox;
    }

    //checa se fruta existe
    if (listaAux == NULL) {
        printf("Erro: Fruta não encontrada!\n");
        return;
    }

    //checa se é permitido excluir
    if (listaAux->fruta.quantidade > 0) {
        printf("Erro: Não é possível excluir uma fruta com estoque!\n");
        return;
    }

    if (anterior == NULL) {
        *lista = listaAux->prox;
    } else {
        anterior->prox = listaAux->prox;
    }

    free(listaAux);
    printf("Fruta excluída com sucesso!\n");
}

int venderFruta(Lista *lista, int codigo, int quantidade) {

    Fruta *fruta = buscarFruta(lista, codigo);
    if (fruta == NULL) {
        printf("Erro: Fruta não encontrada!\n");
        return 0;
    }


    if (quantidade > fruta->quantidade) {
        printf("Erro: Quantidade insuficiente em estoque!\n");
        return 0;
    }

    fruta->quantidade -= quantidade;

    //salvar venda
    FILE *arquivo = fopen("vendas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return 0;
    }
    fprintf(arquivo, "Venda: Fruta: %s, Quantidade: %d, Preço Total: %.2f\n", 
            fruta->nome, quantidade, fruta->preco * quantidade);
    fclose(arquivo);

    printf("Venda realizada com sucesso!\n");

    return 1;
}


//INTERFACE
void interfaceBuscarFruta(Lista *lista) {
    int id;
    Fruta *fruta;

    printf("---BUSCA DE FRUTA---\n");
    printf("Digite o id da fruta: ");
    scanf("%d", &id);

    fruta = buscarFruta(lista, id);
    printf("Fruta encontrada! ");
    printf("Codigo: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", 
               fruta->id, fruta->nome, 
               fruta->quantidade, fruta->preco);

}

void interfaceCadastrarFruta(Lista **lista) {
    Fruta novaFruta;

    printf("---CADASTRO DE FRUTA---\n");
    printf("Digite o id da fruta: ");
    scanf("%d", &novaFruta.id);
    printf("Digite o nome da fruta: ");
    scanf("%s", novaFruta.nome);
    printf("Digite a quantidade: ");
    scanf("%d", &novaFruta.quantidade);
    printf("Digite o preco: ");
    scanf("%f", &novaFruta.preco);

    cadastrarFruta(lista, novaFruta);
}

void interfaceExcluirFruta(Lista **lista) {
    int id;

    printf("---EXCLUSÃO DE FRUTA---\n");
    printf("Digite o id da fruta: ");
    scanf("%d", &id);
    excluirFruta(lista, id);
}

void interfaceVenderFruta(Lista *lista) {
    int id;
    int quantidade;

    printf("---VENDA DE FRUTA---\n");
    printf("Digite o id da fruta: ");
    scanf("%d", &id);

    printf("Digite a quantidade de frutas: ");
    scanf("%d", &quantidade);

    venderFruta(lista, id, quantidade);
}

void interfaceAlterarFruta(Lista *lista) {
    int id;
    Fruta *fruta;

    printf("---ALTERAÇÃO DE FRUTA---\n");
    printf("Digite o id da fruta: ");
    scanf("%d", &id);

    fruta = buscarFruta(lista, id);

    alterarFruta(fruta);
}