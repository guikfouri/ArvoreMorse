#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct elemento{
    char dado;
    struct elemento * prox_ponto;
    struct elemento * prox_traco;
}t_elemento;

typedef struct lista{
    t_elemento * init;
    t_elemento * end;
}t_lista;

typedef struct no
{
    struct no * esq;
    struct no * dir;
    char letra;
}t_no;

int i = 0, k = 0;                                      //Contador da quantidade de caracteres

void preencher_arvore(t_no * raiz);
void code_to_text(t_no * raiz, char * text);
void preencher_lista(t_lista * l);
void code_to_text_list(t_lista * l, char * text_l);


int main(void){
    char text[1000];
    char text_l[1000];
    int j;
    struct timespec init_arv;
    struct timespec fim_arv;
    struct timespec init_l;
    struct timespec fim_l;
    double time_arv;
    double time_l;

    t_lista * list = (t_lista *)malloc(sizeof(t_lista));
    t_elemento * first = (t_elemento *)malloc(sizeof(t_elemento));
    first->prox_ponto = NULL;
    first->prox_traco = NULL;
    first->dado = 'x';
    list->init = first;

    printf("\n -------- Decodificando a mensagem usando arvore --------\n\n");

    clock_gettime(CLOCK_MONOTONIC, &init_arv);

    t_no * raiz = (t_no *)malloc(sizeof(t_no));
    raiz->letra = 'x';
    preencher_arvore(raiz);
    code_to_text(raiz, text);
    for (j = 0; j < i; j++){
        printf("%c ", text[j]);
    }
    printf("\n");

    clock_gettime(CLOCK_MONOTONIC, &fim_arv);
    time_arv =fim_arv.tv_nsec - init_arv.tv_nsec;
    printf("\n --- Tempo demorado usando arvore: %lf ---", time_arv);

    printf("\n -------- Decodificando a mensagem usando lista --------\n\n");

    clock_gettime(CLOCK_MONOTONIC, &init_l);
    preencher_lista(list);
    code_to_text_list(list, text_l);
    for (j = 0; j < k; j++){
        printf("%c ", text[j]);
    }
    printf("\n");

    clock_gettime(CLOCK_MONOTONIC, &fim_l);
    time_l =fim_l.tv_nsec -  init_l.tv_nsec;
    printf("\n --- Tempo demorado usando lista: %lf ---\n", time_l);

    return 0;

}

void preencher_arvore(t_no * raiz){
    t_no * atual = (t_no *)malloc(sizeof(t_no));
    char c = 'a';
    char letra;
    FILE * pont_arq;
    pont_arq = fopen("morse.txt", "r");
    c = getc(pont_arq);
    do{
        atual = raiz;
        letra = c;
        while(c != '\n'){
            c = getc(pont_arq);
            if(c == '.'){
                if(atual->esq == NULL){
                    t_no * esq = (t_no *)malloc(sizeof(t_no));
                    atual->esq = esq;
                }
                atual = atual->esq;
            }
            else if (c == '-'){
                if(atual->dir == NULL){
                    t_no * dir = (t_no *)malloc(sizeof(t_no));
                    atual->dir = dir;
                }
                atual = atual->dir;
            }
        }
        atual->letra = letra;
        c = getc(pont_arq);        
    }while (c != EOF);
    fclose(pont_arq);
    free(atual);
    return;
}

void code_to_text(t_no * raiz, char * text){
    t_no * atual2 = (t_no *)malloc(sizeof(t_no));
    atual2 = raiz;
    char c = 'a';
    FILE * pont_arq2;
    pont_arq2 = fopen("message.txt", "r");
    do{
        atual2 = raiz;
        c = getc(pont_arq2);
        while( (c == '.') || (c == '-') ){
            if(c == '.'){
                atual2 = atual2->esq;
            }
            else if(c == '-'){
                atual2 = atual2->dir;
            }
            c = getc(pont_arq2);
        }
        if(atual2->letra != 'x'){
            text[i] = atual2->letra;
            i++;
        }
        if (c == '/'){
            text[i] = ' ';
            i++;
        }
    }while(c != EOF);
    fclose(pont_arq2);
    free(atual2);
    return;
}

void preencher_lista(t_lista * l){
    t_elemento * atual_l = (t_elemento *)malloc(sizeof(t_elemento));
    char c = 'a';
    char letra;
    FILE * pont_arq;
    pont_arq = fopen("morse.txt", "r");
    c = getc(pont_arq);
    do{
        atual_l = l->init;
        letra = c;
        while(c != '\n'){
            c = getc(pont_arq);
            if(c == '.'){
                if(atual_l->prox_ponto == NULL){
                    t_elemento * ponto = (t_elemento *)malloc(sizeof(t_elemento));
                    ponto->prox_ponto = NULL;
                    ponto->prox_traco = NULL;
                    atual_l->prox_ponto = ponto;
                }
                atual_l = atual_l->prox_ponto;
            }
            else if (c == '-'){
                if(atual_l->prox_traco == NULL){
                    t_elemento * traco = (t_elemento *)malloc(sizeof(t_elemento));
                    traco->prox_ponto = NULL;
                    traco->prox_traco = NULL;
                    atual_l->prox_traco = traco;
                }
                atual_l = atual_l->prox_traco;
            }
        }
        atual_l->dado = letra;
        c = getc(pont_arq);        
    }while (c != EOF);
    fclose(pont_arq);
    free(atual_l);
    return;
}

void code_to_text_list(t_lista * l, char * text_l){
    t_elemento * atual_l2 = (t_elemento *)malloc(sizeof(t_elemento));
    atual_l2 = l->init;
    char c = 'a';
    FILE * pont_arq2;
    pont_arq2 = fopen("message.txt", "r");
    do{
        atual_l2 = l->init;
        c = getc(pont_arq2);
        while( (c == '.') || (c == '-') ){
            if(c == '.'){
                atual_l2 = atual_l2->prox_ponto;
            }
            else if(c == '-'){
                atual_l2 = atual_l2->prox_traco;
            }
            c = getc(pont_arq2);
        }
        if(atual_l2->dado != 'x'){
            text_l[k] = atual_l2->dado;
            k++;
        }
        if (c == '/'){
            text_l[k] = ' ';
            k++;
        }
    }while(c != EOF);
    fclose(pont_arq2);
    free(atual_l2);
    return;

}