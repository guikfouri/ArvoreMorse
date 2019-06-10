#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct elemento{
    char code[8];
    char dado;
    struct elemento * prox;
}t_elemento;

typedef struct lista{
    t_elemento * inicio;
    t_elemento * fim;
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
t_elemento * RetirarDoFim(t_lista * l);
void InserirNoFim(t_lista * l, t_elemento * new);
t_elemento * RetirarDoInicio (t_lista * l);
void InserirNoInicio(t_lista * l, t_elemento * new);
int EstaVazia(t_lista * l);
void zerar_array(char vetor[8]);
char pesquisar_lista(t_lista * l, char * codig);


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
    zerar_array(first->code);
    first->dado = 'x';
    list->inicio = first;
    list->fim = first;

    printf("\n -------- Decodificando a mensagem usando arvore --------\n\n");

    clock_gettime(CLOCK_MONOTONIC, &init_arv);

    t_no * raiz = (t_no *)malloc(sizeof(t_no));
    raiz->letra = 'x';
    preencher_arvore(raiz);
    code_to_text(raiz, text);
    for (j = 0; j < i; j++){
        printf("%c", text[j]);
    }
    printf("\n");

    clock_gettime(CLOCK_MONOTONIC, &fim_arv);
    time_arv =fim_arv.tv_nsec - init_arv.tv_nsec;
    printf("\n --- Tempo demorado usando arvore: %lf ---\n", time_arv);

    printf("\n -------- Decodificando a mensagem usando lista --------\n\n");

    clock_gettime(CLOCK_MONOTONIC, &init_l);
    preencher_lista(list);
    code_to_text_list(list, text_l);
    for (j = 0; j < k; j++){
        printf("%c", text_l[j]);
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
    int j = 0;
    char c = 'a';
    char letra;
    FILE * pont_arq;
    pont_arq = fopen("morse.txt", "r");
    c = getc(pont_arq);                     //Primeira letra
    atual_l = l->inicio;
    do{
        letra = c;
        j = 0;
        t_elemento * prox = (t_elemento *)malloc(sizeof(t_elemento));
        zerar_array(prox->code);
        prox->dado = letra;
        c = getc(pont_arq);                 //Pegar o ' '
        c = getc(pont_arq);                 //Primeiro simbolo
        while(c != '\n'){
            prox->code[j] = c;
            j++;
            c = getc(pont_arq);             //Resto do Código
        }
        InserirNoFim(l, prox);
        atual_l = prox;
        c = getc(pont_arq);                 //Letra
    }while (c != EOF);
    fclose(pont_arq);
    free(atual_l);
    return;
}

void code_to_text_list(t_lista * l, char * text_l){
    t_elemento * atual_l2 = (t_elemento *)malloc(sizeof(t_elemento));
    int j = 0;
    int entrou = 0;
    char codig[8] = {"xxxxxxxx"};
    atual_l2 = l->inicio;
    char c = 'a';

    FILE * pont_arq2;
    pont_arq2 = fopen("message.txt", "r");

    do{
        atual_l2 = l->inicio;
        j = 0;
        
        c = getc(pont_arq2);
        while( (c == '.') || (c == '-') ){
            if(c == '.'){
                codig[j] = '.';
                j++;
                entrou = 1;
            }
            else if(c == '-'){
                codig[j] = '-';
                j++;
                entrou = 1;
            }
            c = getc(pont_arq2);
        }
        if(entrou){
            entrou = 0;
            text_l[k] = pesquisar_lista(l, codig);
            k++;
            zerar_array(codig);
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

int EstaVazia(t_lista * l){
    if (l->inicio == NULL){
        return 1;
    }
        return 0;
}

void InserirNoInicio(t_lista * l, t_elemento * new){ //ponteiro para o elemento como parâmetro.
    new->prox = l->inicio;  
    if (!EstaVazia(l)){
        l->inicio = new;
    }
    else{
        l->inicio = new;
        l->fim = new;
    }
}

t_elemento * RetirarDoInicio (t_lista * l){ //retorna um ponteiro pra uma struct elemento.
    t_elemento * dado; 
    if (!EstaVazia(l)){
        dado = l->inicio;
        l->inicio = l->inicio->prox; //muda o início para o próximo elemento da lista
        if (l->inicio == NULL){ //só havia 1 elemento na lista
            l->fim = NULL;      //após retirado, não tem mais nenhum
        }
        return dado;            //retorna a struct toda do elemento inicial
    }
    else{
        printf("Lista já está vazia\n");
        return NULL; //retorna uma struct nula.
    }
}

void InserirNoFim(t_lista * l, t_elemento * new){
    new->prox = NULL;
    if(!EstaVazia(l)){
        l->fim->prox = new; //o último elemento passa a appontar para o novo.
    }
    else{
        l->inicio = new; //nesse caso, estamos inserindo o primeiro elemento da lista.
    }
    l->fim = new; //em ambas as situações, new é o novo último.
}    

t_elemento * RetirarDoFim(t_lista * l){
    if(!EstaVazia(l)){
        t_elemento * dado;
        if(l->inicio == l->fim){ //Apenas 1 elemento
            dado = l->inicio;
            l->inicio = NULL;
            l->fim = NULL;
            return dado; //retorna o único elemento e torna a lista vazia
        }
        else{ //mais de 1 elemento
            t_elemento * penultimo = l->inicio; //struct para percorrer a lista
            while(penultimo->prox != l->fim){ //enquanto a struct de referência não for de fato a penúltima.
                penultimo = penultimo->prox;  //percorre-se a lista.
            }
            dado = l->fim;
            l->fim = penultimo;  //O fim agora pertence ao penúltimo
            l->fim->prox = NULL; //o último se refere ao NULL
            return dado;
        }
    }
    else{
        printf("Lista já está vazia\n");
        return NULL;
    }
}

void zerar_array(char vetor[8]){
    int j;
    for(j = 0; j < 8; j++){
        vetor[j] = 'x';
    }
}

char pesquisar_lista(t_lista * l, char codig[]){
    t_elemento * aux= (t_elemento *)malloc(sizeof(t_elemento));
    aux = l->inicio->prox;
    int j = 0;
    int igual = 1;
    while(aux != NULL){
        while( (codig[j] == '-' || codig[j] == '.' || aux->code[j] == '.' || aux->code[j] == '-') && (igual == 1) ){
            if(codig[j] != aux->code[j]){
                igual = 0;
            }
            j++;
        }
        if(igual == 1)
            return aux->dado;
        igual = 1;
        j = 0;
        aux = aux->prox;
    }
}