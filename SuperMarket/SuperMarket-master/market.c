#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// FUNÇÕES DIVERSAS
void secondsToDate(int tempo){
  int horas, horas_seg, minutos, segundos;
  tempo = tempo%86400;
   horas_seg=3600;
   horas = (tempo/horas_seg); //resultado da hora
   minutos = (tempo -(horas_seg*horas))/60;
   segundos = (tempo -(horas_seg*horas)-(minutos*60));
   printf("%02d:%02d:%02d",horas,minutos,segundos);
}
          // DECLARAÇÕES DE ASSINATURAS
// LISTA
typedef struct lista TLista;
TLista *criarLista();
void inserirInicioLSE(TLista *lst, void *e_carganova);
void inserirFinalLSE(TLista *lst, void *e_carganova);
void* removerInicioLSE(TLista *lst);
void* removerFinalLSE(TLista *lst);

// FILA
typedef struct fila TFila;
TFila *criarFila();
void enfileirar(TFila *f, void *novoElem);
void *desenfileirar(TFila *f);

// Comparador
typedef int (*TComparador)(void*,void*);

// Impressor
typedef void (*TImpressora)(void*);
void imprimirLSE(TLista *lst, TImpressora impressora);
typedef void (*TImpressora)(void*);


// DECLARAÇÕES DE FUNÇÕES

// LISTA
typedef struct elemento{
  void *carga;
  struct elemento *prox;
} TElemento;
struct lista{
  int nroElementos;
  TElemento *inicio;
  TElemento *final;
};
TLista *criarLista(){
  TLista *e_lista = malloc(sizeof(TLista));
  e_lista->nroElementos = 0;
  e_lista->inicio=NULL;
  e_lista->final = NULL;
  return e_lista;
}
void inserirInicioLSE(TLista *lst, void *e_carganova){
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;
    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    TElemento *elem = malloc(sizeof(TElemento));
    elem->prox = lst->inicio;
    elem->carga = e_carganova;
    lst->inicio = elem;
    lst->nroElementos++;
  }
}
void inserirFinalLSE(TLista *lst, void *e_carganova){
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;
    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    TElemento *elem = malloc(sizeof(TElemento));
    lst->final->prox = elem;
    elem->carga = e_carganova;
    elem->prox = NULL;
    lst->final = elem;
    lst->nroElementos++;
  }
}
void* removerInicioLSE(TLista *lst){
  void *carga=NULL;
  if (lst->inicio != NULL){
    TElemento *prim = lst->inicio;
    TElemento *e_novoInicio = prim->prox;
    carga = prim->carga;
    free(prim);
    lst->inicio = e_novoInicio;
    lst->nroElementos--;
    if (lst->inicio == NULL)
      lst->final = NULL; 
  return carga;
}
void* removerFinalLSE(TLista *lst){
  void *carga=NULL;
  if(lst->inicio != NULL){
    TElemento *anterior=NULL;
    TElemento *caminhador = lst->inicio;
    while(caminhador->prox!=NULL){
      anterior = caminhador;
      caminhador = caminhador->prox;
    }
    carga = lst->final->carga;
    free(lst->final);
    lst->final = anterior;
    if (lst->final == NULL){
      lst->inicio=NULL;
    }else{
      lst->final->prox = NULL;
    }
    lst->nroElementos--;
  return carga;
}
int vaziaLSE(TLista *lst){
  return (lst->inicio == NULL);
}
void imprimirLSE(TLista *lst, TImpressora impressora){
  if (lst->inicio != NULL){
      TElemento *caminhador=lst->inicio;
    while(caminhador != NULL){
      impressora(caminhador->carga);
      caminhador = caminhador->prox;
    }
  }
}
void inserirOrdenadoLSE(TLista *lst, void *e_carganova, TComparador compara){
  TElemento *anterior = NULL;
  TElemento *caminhador = lst->inicio;
  while ((caminhador!=NULL) && (compara(e_carganova, caminhador->carga) >= 0)){
    anterior = caminhador;
    caminhador = caminhador->prox;
  }
  if (anterior==NULL){
    inserirInicioLSE(lst, e_carganova);
  }else if(caminhador == NULL){
    inserirFinalLSE(lst,e_carganova);
  } else{
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = caminhador;
    anterior->prox = elem;
    lst->nroElementos++;
  }
}

// FILA
struct fila{
  int tamanho;
  TLista *lista;
};
TFila *criarFila(){
  TFila *f = malloc(sizeof(TFila));
  f->tamanho = 0;
  f->lista = criarLista();
  return f;
}
void enfileirar(TFila *f, void *novoElem){
  inserirFinalLSE(f->lista, novoElem);
  f->tamanho++;
}
void *desenfileirar(TFila *f){
  void *elemento = removerInicioLSE(f->lista);
  if(elemento != NULL)
    f->tamanho--;
  return elemento;
}

// EVENTO
typedef struct evento{
  double marcaTempo; //HHMMSS
  int tipoEvento;
  int itens;
  int tipoCliente;
  int tempogasto;
  void *e_carga;

} TEvento;
TEvento *criarEvento( int marcaTempo, int tipo, void *e_carga){
  TEvento *e = malloc(sizeof(TEvento));
  e->marcaTempo = marcaTempo;
  e->tipo = tipo;
  e->e_carga = e_carga;
  return e;
}
void imprimirEvento(void *e){
  TEvento *ee = e;
  int t = ee->marcaTempo;
  secondsToDate(t);
  printf(" %d\n", ee->tipo);
}
int comparaEvento(void *e1, void *e2){
  TEvento *ee1 = e1;
  TEvento *ee2 = e2;
  if(ee1->marcaTempo == ee2->marcaTempo){
    return 0;
  }
  else if( ee1->marcaTempo < ee2->marcaTempo){
    return -1;
  }
  else{
    return 1;
  }
}

// AGENDA
typedef struct Agenda{
  int dia, mes, ano;
  TLista *eventos;

} TAgenda;
TAgenda *criarAgenda(int dia, int mes, int ano){
  TAgenda *a = malloc(sizeof(TAgenda));
  a->dia = dia;
  a->mes = mes;
  a->ano = ano;
  a->eventos = criarLista();
  return a;
}
void agendamento(TAgenda *a, TEvento *e){
  inserirOrdenadoLSE(a->eventos, e, comparaEvento);
}
void imprimirAgenda(TAgenda *a){
  imprimirLSE(a->eventos,imprimirEvento);
}
TEvento* proximoEventoAgenda(TAgenda *a){
  TEvento *e = removerInicioLSE(a->eventos);
  return e; 
}
int temEventoAgenda(TAgenda *a){
  return ! vaziaLSE(a->eventos);
}

typedef struct aula{
  char codigo[7];
} TAula;
void imprimirAula(TAula *a){
  printf("%s\n",a->codigo);
}

// PESSOA
typedef struct pessoa{
  int senha;
  int hora;
  int servico;
  int tipo_de_pessoa;
  int forma_pagamento;
} TPessoa;
TPessoa *criarPessoa(int senha){
  TPessoa *p = malloc(sizeof(TPessoa));
  p->senha = senha;
  return p;
}

// CAIXA
typedef struct caixa{
  int FatorAgil; // [1,10], onde 1 caracteriza agilidade máxima.
  double tmedio;
} TCaixa;


int main(){

/////////////////// INITIAL_SETUP ///////////////////
  // Primeira Linha de Leitura
    // Nro de PVDs já existentes
  int existentPVDs;
  scanf("%d",&existentPVDs);

    // Fator de Agilidade de cada um dos PVDs
  int i;
  int faExist[existentPVDs];
  for(i=0;i<existentPVDs;i++){
    scanf("%d",&faExist[i]);
  }


  // Segunda Linha de Leitura
    // Nro de PVDs novos
  int newPVDs;
  scanf("%d",&newPVDs);
  
    // Fator de Agilidade de cada um dos PVDs novos
  int faNews[newPVDs];
  for(i=0;i<newPVDs;i++){
    scanf("%d",&faNews[i]);
  }

  // Terceira linha de Leitura
    // Intervalo por tratamento de produtos (em milisegundos)
  double intervaloPerProduct;
  scanf("%lf",&intervaloPerProduct);

  // Quarta Linha de Leitura
    // Referente ao tipo de cliente:
    // Tipo 1: Vai esperar o tempo que for necessário pra comprar.
    // Tipo 2: Vai esperar no maximo X minutos no Expresso (Fila + atendimento).
    // Tipo 3: Vai esperar no maximo Y minutos na FILA, e no maximo Z minutos no atendimento
    // A Leitura se dá por: X Y Z
  int x,y,z;
  scanf("%d %d %d",&x,&y,&z);
/////////////////////////////////////////////////////

/////////////////// SEQUENCIA DE LEITURAS - MASSA DE DADOS ///////////////////
  // Evento no formato: A B C D E
    // Se A = "C"
    // A - Tipo de Evento ; B - Tempo de Chegada ; C - Quantidade de Itens ; D - Tipo de Cliente ; E - Tempo Gasto em função da Forma de Pagamento ;

    // Se A = "S"
    // A - Tipo de Evento ; B - Inicio da Suspensão ; C - ID do PVD ; D - Duração da Suspensão em Minutos ; Dispensada a Variavel E neste caso ;

    // Diversas leituras deste formato, onde a condição de parada é que A = "F"
//////////////////////////////////////////////////////////////////////////////


}

