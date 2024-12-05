#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TABELA 10
//Matheus Grego do Amaral

typedef struct Contato {
    char nome[100];
    char telefone[20];
    struct Contato* proximo;
} Contato;

Contato* tabela[MAX_TABELA];

int hash(char* nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % MAX_TABELA;
}

void adicionarContato() {
    char nome[100], telefone[20];
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Telefone: ");
    scanf(" %[^\n]", telefone);

    int indice = hash(nome);
    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = NULL;

    if (tabela[indice] == NULL) {
        tabela[indice] = novoContato;
    } else {
        Contato* temp = tabela[indice];
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoContato;
    }
    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char nome[100];
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    int indice = hash(nome);
    Contato* temp = tabela[indice];
    clock_t inicio = clock();

    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, temp->telefone, tempo);
            return;
        }
        temp = temp->proximo;
    }
    printf("Contato não encontrado.\n");
}

void removerContato() {
    char nome[100];
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    int indice = hash(nome);
    Contato* temp = tabela[indice];
    Contato* anterior = NULL;

    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            if (anterior == NULL) {
                tabela[indice] = temp->proximo;
            } else {
                anterior->proximo = temp->proximo;
            }
            free(temp);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = temp;
        temp = temp->proximo;
    }
    printf("Contato não encontrado.\n");
}

void exibirContatos() {
    for (int i = 0; i < MAX_TABELA; i++) {
        Contato* temp = tabela[i];
        while (temp != NULL) {
            printf("Nome: %s, Telefone: %s\n", temp->nome, temp->telefone);
            temp = temp->proximo;
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
