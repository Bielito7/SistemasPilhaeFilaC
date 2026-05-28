#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int valor;
    int coordenada;
    struct Nodo *prox;
 } Nodo;

typedef struct dimensao {
    int linhas;
    int colunas;
} dimensao;

int buscar_elemento(Nodo *matriz, int coordenada) {        
    Nodo *aux = matriz;
    while(aux != NULL) {
        if(aux->coordenada / 100 == coordenada / 100 && aux->coordenada % 100 == coordenada % 100) {
            return aux->valor;
        }
        aux = aux->prox;
    }
    return 0;
}

void imprimir_matriz(Nodo *lista){
    for(int lin = 1; lin <= 30; lin ++){
        for (int col = 1; col <= 30; col++){
            int val = buscar_elemento(lista, (lin * 100 + col));
            if (val == 0) printf("\t %d", 0);
            else printf("\t%d", val);
        }
        printf("\n");
    }
}

Nodo *cria_pilha(){
    Nodo *p;
    p = (Nodo *) malloc(sizeof(struct Nodo)); // [ ? | ?]
    
    if(!p)
        {
        printf("Problemas na Alocação!\n");
        exit(0);
    }
    return p;
}

void push(Nodo **topo, int coordenada, int valor){
    Nodo *novo;
    novo = cria_pilha();
    novo -> valor = valor;
    novo -> coordenada = coordenada;
    novo -> prox = *topo;
    *topo = novo;
}

int pop(Nodo **topo){
    
    if(!*topo){
        printf("A pilha esta vazia!\n");
        return -1;
    }

    Nodo *aux;
    aux = *topo;
    *topo = aux -> prox;
    free(aux);
}

void imprime_pilha(Nodo *topo){
    Nodo *aux;
    aux = topo;

    while (aux != NULL)
    {
        printf("[ %d | %d | %p ] --> ", aux->valor, aux->coordenada, aux->prox);
        aux = aux -> prox;
    }
    
}

int main(){
    Nodo *pilha = NULL;

    for(int i = 0; i < 10; i++){
        push(&pilha, i*101, i*10);
    }

    pop(&pilha);
    pop(&pilha);
    pop(&pilha);
    pop(&pilha);
    pop(&pilha);



    Nodo *matriz = NULL;

    for (int i = 100; i < 3000; i+100){
        for (int j = 1; j < 30; j++){
            if(i == 100 || i == 3000 || j == 1 || j == 30)
                push(&matriz, (i+j), 1);
        }
    }


    imprimir_matriz(matriz);
    
}