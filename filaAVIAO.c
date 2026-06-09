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

void inserir_no_fim(aviao **inicio, aviao **fim, int id_func, char nome [20], char origem [20], char destino [20], char modelo [20]){
    aviao *aux, *novo;
    novo = cria_aviao();
    novo -> id = id_func;
    novo -> prox = NULL;
    strcpy(novo->nome, nome);
    strcpy(novo->origem, origem);
    strcpy(novo->destino, destino);
    strcpy(novo->modelo, modelo);

    if (*inicio == NULL){
        *inicio = novo;
        *fim = novo;
    } else{

       (*fim)->prox = novo;
       *fim = novo;
    }

    id += 1;
}

void imprime_fila(aviao *inicio){
    aviao *aux;
    aux = inicio;

    if (inicio == NULL) {
        printf("Fila vazia!\n");
        return; 
    }

    while (aux->prox != NULL)
    {
        printf("[ %d | %s | %s | %s | %s] <-- ", aux->id, aux->nome, aux->origem, aux-> destino, aux->modelo);
        aux = aux -> prox;
    }
    
    printf("[ %d | %s | %s | %s | %s]", aux->id, aux->nome, aux->origem, aux-> destino, aux->modelo);

}

int contar_avioes(aviao *inicio) {
    int contador = 0;
    
    aviao *aux = inicio;
    
    while (aux != NULL) {
        contador++;           
        aux = aux->prox;    
    }
    
    // 3. Retorna o total
    return contador;
}

int autorizar_aviao(aviao **inicio, aviao **fim) {
    // Verifica se tem aviao para decolar
    if (*inicio == NULL) {
        printf("Nenhum aviao na fila!\n");
        return -1;
    }

    aviao *aux = *inicio;

    *inicio = (*inicio)->prox;

    if (*inicio == NULL) {
        *fim = NULL;
    }

    free(aux);

}

int main(){
    aviao *fila_decolagem_inicio = NULL;
    aviao *fila_decolagem_fim = NULL;

    aviao *fila_pouso_inicio = NULL;
    aviao *fila_pouso_fim = NULL;

    char nome [20];
    char origem [20];
    char destino [20];
    char modelo [20];

    int resposta = 0;
    do{
        printf("\n\n=== MENU ===\n\n");
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

            inserir_no_fim(&fila_decolagem_inicio, &fila_decolagem_fim, id, nome, origem, destino, modelo);
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
            inserir_no_fim(&fila_pouso_inicio, &fila_pouso_fim,id, nome, origem, destino, modelo);

            break;

        // listar avioes esperando para decolar
        case 3:
            imprime_fila(fila_decolagem_inicio);
            break;
        // listar avioes esperando para pousar
        case 4:
            imprime_fila(fila_pouso_inicio);
            break;
        // autorizar decolagem do proximo aviao
        case 5:
            resposta = 2;
            printf("Deseja autorizar a decolagem do aviao?\nid: %d\nnome: %s\norigem: %s\ndestino: %s\nmodelo: %s\n", fila_decolagem_inicio->id, fila_decolagem_inicio->nome, fila_decolagem_inicio->origem, fila_decolagem_inicio->destino, fila_decolagem_inicio->modelo);
            do{
                printf("\nResposta(1 para sim, 0 para nao): ");
                scanf("%d", &resposta);
            
            } while(resposta != 1 && resposta != 0);
            if (resposta == 1){
                autorizar_aviao(&fila_decolagem_inicio, &fila_decolagem_fim);
            } else{
                printf("\nAutorizacao cancelada\n");
            }
            break;
        // autorizar pouso do proximo aviao
        case 6:
            resposta = 2;
            printf("Deseja autorizar o pouso do aviao:\nid: %d\nnome: %s\norigem: %s\ndestino: %s\nmodelo: %s", fila_pouso_inicio->id, fila_pouso_inicio->nome, fila_pouso_inicio->origem, fila_pouso_inicio->destino, fila_pouso_inicio->modelo);
            do{
                printf("\nResposta(1 para sim, 0 para nao): ");
                scanf("%d", &resposta);
            } while(resposta != 1 && resposta != 0);
            if (resposta == 1){
                autorizar_aviao(&fila_pouso_inicio, &fila_pouso_fim);
            } else{
                printf("\nAutorizacao cancelada\n");
            }
            break;
        // listar o numero de avioes esperando para decolar
        case 7:
            printf("Quantidade de avioes esperando para decolar: %d",contar_avioes(fila_decolagem_inicio));
            break;
        // listar o numero de avioes esperando para pousar
        case 8:
            printf("Quantidade de avioes esperando para pousar: %d", contar_avioes(fila_pouso_inicio));
            break;
        
        case 0:
            printf("Saindo...\n");
            break;
        
        default:
            break;
        }
    } while(resposta != 0);
}