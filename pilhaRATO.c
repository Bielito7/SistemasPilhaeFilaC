#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAREDES 125

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
            if (val == 0){
                printf("  ");
            }
            if(val == 1){ 
                printf("%c%c", 219, 219);
            }
            if(val == 6){
                printf("%c%c", 126, 64);
            }
            
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

void preencher_borda(Nodo **matriz) {
    for (int lin = 1; lin <= 30; lin++) {
        for (int col = 1; col <= 30; col++) {
            // Verifica se é a borda (linha 1, linha 30, coluna 1 ou coluna 30)
            if (lin == 1 || lin == 30 || col == 1 || col == 30) {
                // nao podemos obstruir a saida
                if(lin == 28 && col == 30){
                    push(matriz, (lin * 100) + col, 0);
                }
                else{
                    int coordenada = (lin * 100) + col;
                    push(matriz, coordenada, 1);
                }
            }
        }
    }
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

void insere_paredes(Nodo **matriz){
    for(int i = 0; i < PAREDES; i++){
        int linha = (rand() % 28) + 2;
        int coluna = (rand() % 28) + 2;

        if((linha == 28 && coluna == 29) || (linha == 2 && coluna == 2)){
            push(matriz, (linha * 100) + coluna, 0);
        }else{
            push(matriz, (linha * 100) + coluna, 1);
        }
    }
}

int verifica_posicao(Nodo *matriz, int linha, int coluna)
{
    if(buscar_elemento(matriz, linha*100 + (coluna+1)) == 0)
        return linha*100 + (coluna+1);

    if(buscar_elemento(matriz, (linha+1)*100 + coluna) == 0)
        return (linha+1)*100 + coluna;

    if(buscar_elemento(matriz, linha*100 + (coluna-1)) == 0)
        return linha*100 + (coluna-1);

    if(buscar_elemento(matriz, (linha-1)*100 + coluna) == 0)
        return (linha-1)*100 + coluna;

    return -1;
}

int main(){
    srand(time(NULL));
    Nodo *pilha = NULL;
    Nodo *matriz = NULL;
    
    
    preencher_borda(&matriz);
    insere_paredes(&matriz);

    push(&matriz, 202, 6);



    imprimir_matriz(matriz);
    
}