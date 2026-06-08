#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int id= 0;

typedef struct aviao
{
    int id;
    char nome [20];
    char origem [20];
    char destino [20];
    char modelo [20];
    struct aviao *prox;
} aviao;

aviao *cria_aviao(){
    aviao *novo;
    novo = (aviao *) malloc(sizeof(struct aviao)); // [ ? | ?]
    
    if(!novo)
        {
        printf("Problemas na Alocação!\n");
        exit(0);
    }
    return novo;
}

void inserir_no_fim(aviao **fila, int id, char nome [20], char origem [20], char destino [20], char modelo [20]){
    aviao *aux, *novo;
    novo = cria_aviao();
    novo -> id = id;
    novo -> prox = NULL;
    strcpy(novo->nome, nome);
    strcpy(novo->origem, origem);
    strcpy(novo->destino, destino);
    strcpy(novo->modelo, modelo);

    if (*fila == NULL){
        *fila = novo;
    } else{

        aux = *fila;
        while (aux->prox != 0)
        {
            aux = aux -> prox;
        }

        aux -> prox = novo;
    }

    id += 1;
}

void imprime_fila(aviao *topo){
    aviao *aux;
    aux = topo;

    while (aux->prox != NULL)
    {
        printf("[ %d | %s | %s | %s | %s] <-- ", aux->id, aux->nome, aux->origem, aux-> destino, aux->modelo);
        aux = aux -> prox;
    }
    
    printf("[ %d | %s | %s | %s | %s]", aux->id, aux->nome, aux->origem, aux-> destino, aux->modelo);

}

int main(){
    aviao *fila_decolagem = NULL;
    aviao *fila_pouso = NULL;

    int id = id;
    char nome [20];
    char origem [20];
    char destino [20];
    char modelo [20];

    int resposta = 0;
    do{
        printf("=== MENU ===\n\n");
        printf("1 - adicionar aviao a fila de decolagem\n");
        printf("2 - adicionar aviao a fila de pouso\n\n");

        printf("3 - listar avioes esperando para decolar\n");
        printf("4 - listar avioes esperando para pousar\n\n");

        printf("5 - autorizar decolagem do proximo aviao\n");
        printf("6 - autorizar pouso do proximo aviao\n\n");

        printf("7 - listar o numero de avioes esperando para decolar\n");
        printf("8 - listar o numero de avioes esperando para pousar\n\n");

        printf("0 - sair\n");

        printf("Resposta: ");
        scanf("%d", &resposta);

        switch (resposta)
        {
        // Adicionar aviao a fila de decolagem
        case 1:
            printf("\nDigite o nome do aviao: ");
            scanf("%s", &nome);

            printf("\nDigite o local de origem do aviao: ");
            scanf("%s", &origem);

            printf("\nDigite o destino do aviao: ");
            scanf("%s", &destino);

            printf("\nDigite o modelo do aviao: ");
            scanf("%s", &modelo);

            inserir_no_fim(&fila_decolagem, id, nome, origem, destino, modelo);
            break;

        // adicionar aviao a fila de pouso
        case 2:
            printf("\nDigite o nome do aviao: ");
            scanf("%s", &nome);

            printf("\nDigite o local de origem do aviao: ");
            scanf("%s", &origem);

            printf("\nDigite o destino do aviao: ");
            scanf("%s", &destino);

            printf("\nDigite o modelo do aviao: ");
            scanf("%s", &modelo);
            inserir_no_fim(&fila_pouso, id, nome, origem, destino, modelo);

            break;

        // listar avioes esperando para decolar
        case 3:
            imprime_fila(fila_decolagem);
            break;
        // listar avioes esperando para pousar
        case 4:
            imprime_fila(fila_pouso);
            break;
        // autorizar decolagem do proximo aviao
        case 5:
            
            break;
        // autorizar pouso do proximo aviao
        case 6:
            
            break;
        // listar o numero de avioes esperando para decolar
        case 7:
            
            break;
        // listar o numero de avioes esperando para pousar
        case 8:
            
            break;
        
        case 0:
            printf("Saindo...\n");
            break;
        
        default:
            break;
        }
    } while(resposta != 0);
}