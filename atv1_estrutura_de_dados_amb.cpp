#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX 50

typedef struct {
    int posicao;
    int capacidade;
    int* elementos;   
} Lista;

void preencherLista(Lista &lista) {     // Utilizei essa função apenas para preeencher automaticamente a lista
    for (int i = 0; i < lista.posicao; i++) {
        lista.elementos[i] = i + 1;
    }
}

void adicionarElementos(Lista &lista, int quantidade) {  // ADICIONAR elementos na lista

    while (lista.posicao + quantidade > lista.capacidade) {
        lista.capacidade *= 2;  // Caso a adição de novos elementos na lista ultrapasse a capacidade máxima, dobra a capacidade
        lista.elementos = (int*) realloc(lista.elementos, lista.capacidade * sizeof(int));  // procura um novo espaço onde caiba a lista
        if (lista.elementos == NULL) {  
            cout << "Falha ao realocar memória." << endl;
            exit(1);
        }
    }

    for (int i = lista.posicao; i < lista.posicao + quantidade; i++) {
            lista.elementos[i] = i + 1;
    }
    lista.posicao += quantidade;

    cout << "Lista: ";
    for (int i = 0; i < lista.posicao; i++) {
        cout << lista.elementos[i] << " ";
    }
    cout << endl;
    cout << "Tamanho máximo da lista: " << lista.capacidade << endl;
}

void removerElementos(Lista &lista, int quantidade) {       //REMOVER elementos da lista
    if (quantidade >= lista.posicao) {
        cout << "Não é possível remover mais elementos do que os têm na lista." << endl;
        return;
    }

    lista.posicao -= quantidade;

    if (lista.posicao < lista.capacidade / 4 && lista.capacidade > MAX) {   // Se a lista tiver menos de 25% da sua capacidade, reduz a capacidade pela metade
        lista.capacidade /= 2;  
        lista.elementos = (int*) realloc(lista.elementos, lista.capacidade * sizeof(int));  // realoca em um espaço de memória mais adequado
        if (lista.elementos == NULL) {  
            cout << "Falha ao realocar memória." << endl;
            exit(1);
        }
    }

    cout << "Lista: ";
    for (int i = 0; i < lista.posicao; i++) {
        cout << lista.elementos[i] << " ";
    }
    cout << endl;
    cout << "Tamanho máximo da lista: " << lista.capacidade << endl;  // Capacidade máxima da lista
}

int main() {
    Lista lista;
    lista.posicao = 0;
    lista.capacidade = MAX;
    lista.elementos = (int*) malloc(lista.capacidade * sizeof(int));  // ALOCAÇÃO da lista

    if (lista.elementos == NULL) {
        cout << "Falha ao alocar memória." << endl;
        exit(1);
    }

    lista.posicao = MAX;
    preencherLista(lista);

    cout << "Lista inicial: ";
    for (int i = 0; i < lista.posicao; i++) {
        cout << lista.elementos[i] << " ";
    }
    cout << endl;
    cout << "Tamanho máximo da lista: " << lista.capacidade << endl; 

    int opcao = 0;  // Inicializa a variável 'opcao' antes do loop
    while (opcao != 3) {  // A condição agora é verificada no início
        cout << "\nMenu: \n";
        cout << "1. Adicionar elementos\n";
        cout << "2. Remover elementos\n";
        cout << "3. Sair\n" << endl;
        cout << "Escolha uma opção: " << endl;
        cin >> opcao;

        if (opcao == 1) {
            int quantidade;
            cout << "Quantos elementos serão adicionados? ";
            cin >> quantidade;
            adicionarElementos(lista, quantidade);
        } else if (opcao == 2) {
            int quantidade;
            cout << "Quantos elementos deseja remover? ";
            cin >> quantidade;
            removerElementos(lista, quantidade);
        } else if (opcao == 3) {
            cout << "Fim do programa" << endl;
        } else {
            cout << "Opção inválida. Escolha entre 1, 2 ou 3." << endl;
        }
    }

    free(lista.elementos);
    return 0;
}