#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
}No;

No *raiz = NULL;

No *busca(int x, No *aux){ //Função auxiliar para executar a busca
    if(aux == NULL){
        return NULL;
    }else if(x == aux->chave){
        return aux;
    }else if(x<aux->chave){
        if(aux->esquerda != NULL){
            return busca(x, aux->esquerda);
        }else{
            return aux;
        }
    }else{
        if(aux->direita != NULL){
            return busca(x, aux->direita);
        }else{
            return aux;
        }
    }
}

void add(int x){
    No *resp = busca(x, raiz);
    if(resp == NULL || resp != x){ //Está vazia ou eu posso adicionar
        No *novo = malloc(sizeof(No));
        novo->chave = x;
        novo->pai = resp;
        novo->esquerda = NULL;
        novo->direita = NULL;
        if(resp == NULL){ //Adiciona na raiz
            raiz = novo;
        }else{
            if(x < resp->chave){
                resp->esquerda = novo;
            }else{
                resp->direita = novo;
            }
        }
    }else if(resp == x){ //Chave duplicada, nao permitir adicionar
        printf("Adicao invalida. Chave duplicada");
    }
}

No *remover(No *aux, int x){
    if(aux == NULL){
        return NULL;
    }else if(aux->chave > x){
        aux->esquerda = remover(aux->esquerda, x);
    }else if(aux->chave < x){
        aux->direita = remover(aux->direita, x);
    }else{
        if(aux->esquerda == NULL && aux->direita == NULL){ //Folhas
            free(aux);
            aux = NULL;
        }else if(aux->esquerda == NULL){ //Nó com só um filho â direita
            No *t = aux;
            aux = aux->direita;
            free(t);
        }else if(aux->direita == NULL){ //Nó com só um filho â esquerda
            No *t = aux;
            aux = aux->esquerda;
            free(t);
        }else{ //Nó com dois filhos
            No *f = aux->esquerda;
            while(f->direita !=NULL){
                f = f->direita;
            }
            aux->chave = f->chave; //Troca de informações
            f->chave = x;
            aux->esquerda = remover(aux->esquerda, x);
        }
    }
    return aux;
}

No *busca_arvore(int x){
    No *resp = busca(x, raiz);
    if(resp == NULL){
        return NULL; //Valor não encontrado
    }else{
        if(resp->chave == x){ //Valor encontrado
           return resp;
        }else{
            return NULL;
        }
    }
}

void in_ordem(No *aux){
    if(aux->esquerda != NULL){
        in_ordem(aux->esquerda);
    }
    printf("%d ", aux->chave);
    if(aux->direita != NULL){
        in_ordem(aux->direita);
    }
}

int main()
{
    add(11); //raiz
    add(8); //1 filho
    add(12); //2 filhos
    add(7); //folha
    add(9); //folha
    add(10); //2 filhos
    add(13); //folha
    add(14); //folha
    printf("Imprimindo arvore em ordem: ");
    in_ordem(raiz);
    printf("\n");
    printf("Removemos no com 1 filho: ");
    remover(raiz,8); // removendo nó com 1 filho
    in_ordem(raiz);
    printf("\n");
    printf("Removemos uma folha: ");
    remover(raiz,7); // removendo folha
    in_ordem(raiz);
    printf("\n");
    printf("Removemos um no com 2 filhos: ");
    remover(raiz,12); // removendo nó com 2 filhos
    in_ordem(raiz);
    printf("\n");
    return 0;
}
