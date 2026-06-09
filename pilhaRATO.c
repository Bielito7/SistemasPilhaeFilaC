#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define PAREDES 220
#define RATO 6
#define CAMINHO 0
#define VISITADO 2
#define PAREDE 1
#define BECO 3
#define SAIDA 4

typedef struct Nodo{
    int valor;
    int coordenada;
    struct Nodo *prox;
 } Nodo;

// ===================================================== PILHA ===========================================================================

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

// ===================================================== LABIRINTO ===========================================================================

void preencher_borda(Nodo **labirinto) {
    for (int lin = 1; lin <= 30; lin++) {
        for (int col = 1; col <= 30; col++) {
            // Verifica se é a borda (linha 1, linha 30, coluna 1 ou coluna 30)
            if (lin == 1 || lin == 30 || col == 1 || col == 30) {
                // nao podemos obstruir a saida
                if(lin == 28 && col == 30){
                    push(labirinto, (lin * 100) + col, SAIDA);
                }
                else{
                    int coordenada = (lin * 100) + col;
                    push(labirinto, coordenada, 1);
                }
            }
        }
    }
}

void insere_paredes(Nodo **labirinto){
    for(int i = 0; i < PAREDES; i++){
        int linha = (rand() % 28) + 2;
        int coluna = (rand() % 28) + 2;

        if((linha == 28 && coluna == 29) || (linha == 2 && coluna == 2)){
            push(labirinto, (linha * 100) + coluna, CAMINHO);
        }else{
            push(labirinto, (linha * 100) + coluna, PAREDE);
        }
    }
}

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

void imprimir_labirinto(Nodo *lista){
    for(int lin = 1; lin <= 30; lin ++){
        for (int col = 1; col <= 30; col++){
            int val = buscar_elemento(lista, (lin * 100 + col));
            if (val == CAMINHO){
                printf("  ");
            }
            if(val == PAREDE){ 
                printf("%c%c", 219, 219);
            }
            if(val == RATO){
                printf("%c%c", 126, 64);
            }
            if(val == VISITADO){
                printf("%c%c", 46, 46);
            }
            if(val == BECO){
                printf("%c%c", 120, 120);
            }
            if(val == SAIDA){
                printf("%c%C", 115, 97);
            }
            
        }
        printf("\n");
    }
}

// ===================================================== RATO ===========================================================================

int andar_rato(Nodo **pilha, Nodo **labirinto){
    if(buscar_elemento(*labirinto, (*pilha)->coordenada+1) == SAIDA){
        // Altera a posicao anterior do rato para visitado
        push(labirinto, (*pilha)->coordenada, VISITADO);
        
        push(pilha, (*pilha)->coordenada + 1 , RATO);
        // Altera-se a matriz do labirinto de acordo com a pilha do rato
        push(labirinto, (*pilha)->coordenada, (*pilha)->valor);
        
        return 1; // Achou a saída, retorna 1 e encerra o loop do main
        
    } else {
        // Se o caminho a DIREITA estiver vazio
        if (buscar_elemento(*labirinto, (*pilha)->coordenada+1) == CAMINHO){
            push(labirinto, (*pilha)->coordenada, VISITADO);
            push(pilha, (*pilha)->coordenada + 1 , RATO);
            push(labirinto, (*pilha)->coordenada, (*pilha)->valor);

        } else if (buscar_elemento(*labirinto, (*pilha)->coordenada+100) == CAMINHO){   // BAIXO
            push(labirinto, (*pilha)->coordenada, VISITADO);
            push(pilha, (*pilha)->coordenada + 100 , RATO);
            push(labirinto, (*pilha)->coordenada, (*pilha)->valor);

        } else if (buscar_elemento(*labirinto, (*pilha)->coordenada-1) == CAMINHO){     // ESQUERDA
            push(labirinto, (*pilha)->coordenada, VISITADO);
            push(pilha, (*pilha)->coordenada - 1 , RATO);
            push(labirinto, (*pilha)->coordenada, (*pilha)->valor);
            
        } else if (buscar_elemento(*labirinto, (*pilha)->coordenada-100) == CAMINHO){     // CIMA
            push(labirinto, (*pilha)->coordenada, VISITADO);
            push(pilha, (*pilha)->coordenada - 100 , RATO);
            push(labirinto, (*pilha)->coordenada, (*pilha)->valor);
            
        } else { // Eh um BECO
            push(labirinto, (*pilha)->coordenada, BECO);
            pop(pilha); // Dá um passo para trás
            
            // --- PROTEÇÃO CONTRA CRASH
            if (*pilha == NULL) {
                printf("\nLABIRINTO SEM SAIDA! O rato ficou sem caminhos.\n");
                exit(0); // Encerra o programa em segurança
            }
            
            // Altera-se a matriz do labirinto de acordo com a pilha do rato
            push(labirinto, (*pilha)->coordenada, (*pilha)->valor);
        }
    }
    
    // --- RETORNO PADRÃO ---
    return 0; 
}



// ===================================================== MAIN ===========================================================================

int main(){
    srand(time(NULL));

    // Iniciando labirintode forma aleatoria
    Nodo *labirinto = NULL;
    preencher_borda(&labirinto);
    insere_paredes(&labirinto);

    // Pilha que determina a posicao do rato
    Nodo *pilha = NULL;
    // Posicao inicial
    push(&pilha, 202, 6);

    push(&labirinto, pilha->coordenada, pilha->valor);
    imprimir_labirinto(labirinto);
    
    int achou_saida = 0;
    
    while (achou_saida == 0) {
        //Limpa o terminal
        system("cls"); 
        
        //O rato da UM passo
        achou_saida = andar_rato(&pilha, &labirinto); 
        
        //Printa o labirinto atualizado
        imprimir_labirinto(labirinto); 
        
        Sleep(250); 
    }

    printf("\n\n ACHOU A SAIDA!\n\n");

    
}