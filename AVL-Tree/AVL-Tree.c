#include <stdio.h>
#include <stdlib.h>

// MAIOR ENTRE DOIS INTEIROS
int maior(int a, int b){
    if(a>b) return a; return b;
}
// ESTRUTURA DA ARVORE BINARIA DE BUSCA

typedef struct arvorebinaria{

// ESTRUTURA COMPOSTA POR DUAS ARVORES BINARIAS
    int chave;
    struct arvorebinaria *filhoEsq, *filhoDir;
} ABB;
typedef struct doisponteiros{
    ABB *pai, *filho;
    char lado;
} Pai_Filho;
// CRIAR UM KNOT
ABB *criaNo(int valor){
    ABB *novo;
    novo = malloc(sizeof(ABB));
    novo->chave= valor;
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;
    return novo;
}
// INSERIR KNOT NA ARVORE BINARIA DE BUSCA
ABB *inserirNoABB(ABB *novo, ABB *pai){
    if(pai==NULL) return novo;
    if(pai->chave > novo->chave) pai->filhoEsq = inserirNoABB(novo, pai->filhoEsq);
    if(pai->chave < novo->chave) pai->filhoDir = inserirNoABB(novo, pai->filhoDir);
    return pai;
}

// REMOVER KNOT DA ARVORE BINARIA DE BUSCA
    // Caso 1) Árvore nula.
    // Caso 2) Árvore com apenas um nó.
    // Caso 3) Nó a remover é folha.
    // Caso 4) Nó a remover possui um filho.
    // Caso 5) Nó a remover possui dois filhos.
ABB *removedorAuxiliar(ABB *defunto){ // Tratando dos casos 3, 4 e 5. Função que trata do defunto.
    ABB *anterior, *atual; // Trata do caso 3 e 4 ao mesmo tempo assumino que o filho da direita possa ser tanto null quanto um nó existente
    if(defunto->filhoEsq == NULL){
        atual = defunto->filhoDir;
        free(defunto);
        return atual;
    } // Trata o caso 5, quando o nó defunto é um nó intermediário.
    anterior = defunto;
    atual = defunto->filhoEsq;
    // Procura o MdM
    while(atual->filhoDir!=NULL){
        anterior = atual;
        atual = atual->filhoDir;
    }
    // Passo o MdM para o lugar onde o defunto deixará.
    if(anterior != defunto){
        anterior->filhoDir = atual->filhoEsq;
        atual->filhoEsq = defunto->filhoEsq;
    }
    atual->filhoDir = defunto->filhoDir;
    // Tchauzinho defunto, vá com Deus, ou não.
    free(defunto);
    return atual;
}
ABB *removerNoABB(ABB *raiz, int chave){
    if(raiz==NULL) return NULL; // Árvore Vazia
    ABB *raizz = raiz;
    ABB *pai=NULL, *filho=raiz; // Variaveis auxiliares
    // Atenção sempre necessário manter em conhecimento o Pai do defundo.
    while(filho!=NULL){ // BuscandoOoOo
        if(filho->chave == chave){ // ACHOU
            if(raiz==filho) raiz = removedorAuxiliar(filho);
            else{ // SE NÃO É A RAIZ, OU É O DA DIREITA OU O DA ESQUERDA
                if(pai->filhoDir == filho) pai->filhoDir = removedorAuxiliar(filho);
                else pai->filhoEsq = removedorAuxiliar(filho);
            }
            return raizz;
        }
        // Não achou ainda... A luta (busca) continua. Anda.
        pai = filho;
        if(chave > filho->chave) filho = filho->filhoDir;
        else filho = filho->filhoEsq;
    }
}


// BUSCA ELEMENTO A PARTIR DE UMA CHAVE NO FORMATO PAI-FILHO
Pai_Filho *buscaPF(ABB *raiz, Pai_Filho *dpoints, int chave){
    if(raiz==NULL) return NULL;
    if(chave == raiz->chave) return dpoints;
    if(chave< raiz->chave){
        dpoints->pai = dpoints->filho;
        dpoints->filho = raiz->filhoEsq;
        dpoints->lado = 'E';
        return buscaPF(raiz->filhoEsq,dpoints,chave);
    }
    else{
        dpoints->pai = dpoints->filho;
        dpoints->filho = raiz->filhoDir;
        dpoints->lado = 'D';
        return buscaPF(raiz->filhoDir,dpoints,chave);
    }
}

// VERIFICA SE UM NÓ É UMA FOLHA (AMBOS FILHOS NULL)
int ehfolha(ABB *no){
    if(no->filhoEsq == no->filhoDir) return 1;
    return 0;
}
char qualFilho(ABB *pai, ABB *filho){
    if(pai->chave > filho->chave) return 'E';
    return 'D';
}
// IMPRIME ELEMENTOS DE UMA ARVORE BINARIA EM ORDEM CRESCENTE.
void exibeABB(ABB *raiz){
    if(raiz!=NULL){
        exibeABB(raiz->filhoEsq);
        printf("%d\n",raiz->chave);
        exibeABB(raiz->filhoDir);
    }
}

/*
int maiorDifAltura(ABB *raiz, int M){
    int altEsq, altDir, dif;
    if(raiz == NULL) return 0;
    altEsq = maiorDifAltura(raiz->filhoEsq, M);
    altDir = maiorDifAltura(raiz->filhoDir, M);
    dif = altEsq - altDir;
    if(abs(dif) > 0) return M = dif;
    return (1 + maior(altEsq, altDir));
}
*/

//ESTRUTURA DA ARVORE DE ADELSON VOLSKII LANDIS (AVL)

// AS FUNÇÕES DA ARVORE AVL SÃO IDENTICAS AS DA ARVORE BINARIA DE BUSCA, APENAS COM EXCESSÃO DAS FUNÇÕES DE INSERÇÃO E REMOÇÃO
//LOGO, NESTE BLOCO ESTAREI DECLARANDO AS FUNÇÕES INSERIR E REMOVER, JUNTAMENTE COM AS FUNÇÕES DE ROTAÇÃO E OUTRAS.

// DADOS QUE CADA NO IRÃO CARREGAR SOBRE A RESERVA NO COLSUNTORIO;
typedef struct dados{
    int consultorio;
    int dia;
    int hora;
    int paciente;
    int psicologo;
} Dados;


// PARA EVITAR DE PERCORRER EXAUSTIVAMENTE A ARVORE EM BUSCA DA ALTURA DE DERMINADO NO, A ESTRUTURA SERÁ ADAPTADA DA SEGUINTE FORMA.
typedef struct arvoreavl{
    Dados *DATA;
    int chave;
    int alt; // será a altura de determinado nó;
    struct arvoreavl *filhoDir, *filhoEsq;
} AVL;

// FUNÇÃO INTEIRA QUE ACESSA A ALTURA DE UM NÓ E A RETORNA.
int alturaDoNo(AVL *knot){
    if (knot == NULL) return -1;
    return knot->alt;
}

// BUSCAR ELEMENTO A PARTIR DE UMA CHAVE
AVL *buscaNo(AVL *raiz, int chave){
    if(raiz==NULL) return NULL;
    if(chave == raiz->chave) return raiz;
    if(chave < raiz->chave) return buscaNo(raiz->filhoEsq, chave);
    else return buscaNo(raiz->filhoDir, chave);
}
// ALTURA DE UMA ARVORE
int altura(AVL *raiz){
    if(raiz==NULL) return -1;
    return 1 + maior(altura(raiz->filhoEsq),altura(raiz->filhoDir));
}

// MAIOR ELEMENTO DE UMA ARVORE (A MAIOR CHAVE DA ARVORE)
AVL *maiorNo(AVL *raiz){
    if(raiz == NULL) return NULL;
    if(raiz->filhoDir == NULL) return raiz;
    maiorNo(raiz->filhoDir);
}

// MENOR ELEMENTO DE UMA ARVORE (A MENOR CHAVE DA ARVORE)
AVL *menorNo(AVL *raiz){
    if(raiz == NULL) return NULL;
    if(raiz->filhoEsq == NULL) return raiz;
    menorNo(raiz->filhoEsq);
}

// QUANTIDADE DE NÓS DE UMA ARVORE
int quantosNos(AVL *raiz){
    if(raiz==NULL) return -1;
    return 2 + quantosNos(raiz->filhoEsq) + quantosNos(raiz->filhoDir);
}

// AS ROTAÇÕES SÃO RECURSOS LOGISTICOS IMPORTANTES PARA O BALANÇEAMENTO DA ARVORE AVL
// O FATOR DE BALANCEAMENTO DOS NÓS É O QUE DEFINE QUAIS ROTAÇÕES USAR.
int fatorDeBalanceamento(AVL *knot){
    return abs( alturaDoNo(knot->filhoEsq) - alturaDoNo(knot->filhoDir));
}

//   ROTAÇÕES  RSD (SIMPLES A DIREITA), RSE (SIMPLES A ESQUERDA), RDE (DIREITA-ESQUERDA), RED(ESQUERDA-DIREITA)
//   DETERMINANDO O TIPO DE ROTAÇÃO A SER USADA:
    // CONSIDERANDO QUE C FOI INSERIDO COMO FILHO DE B, E QUE B É FILHO DE UM A, VERIFICAMOS O FATOR DE BALANCEAMENTO DE A E B DA SEGUINTE FORMA:
        // Afat = +2 e Bfat = +1 a rotação é a RSD
        // Afat = -2 e Bfat = -1 a rotaçãp é a RSE
        // Afat = +2 e Bfat = -1 a rotação é a RED
        // Afat = -2 e Bfat = +1 a rotação é a RDE

// ROTAÇÃO SIMPLES A DIREITA
void RSD(AVL *pai){
    AVL *filho = pai->filhoEsq;
    pai->filhoEsq = filho->filhoDir;
    filho->filhoDir = pai;
    pai->alt = 1 + maior( alturaDoNo(pai->filhoEsq), alturaDoNo(pai->filhoDir) );
    filho->alt = 1 + maior( alturaDoNo(filho->filhoEsq), pai->alt );
    pai = filho;
}
// ROTAÇÃO SIMPLES A ESQUERDA
void RSE(AVL *pai){
    AVL *filho = pai->filhoDir;
    pai->filhoDir = filho->filhoEsq;
    filho->filhoEsq = pai;
    pai->alt = 1 + maior( alturaDoNo(pai->filhoEsq), alturaDoNo(pai->filhoDir));
    filho->alt = 1 + maior(alturaDoNo(filho->filhoEsq), pai->alt);
    pai = filho;
}
// ROTAÇÃO DUPLA (ESQUERDA-DIREITA)
void RED(AVL *pai){
    RSE(pai->filhoEsq);
    RSD(pai);
}
// ROTAÇÃO DUPLA (DIREITA-ESQUERDA)
void RDE(AVL *pai){
    RSD(pai->filhoDir);
    RSE(pai);
}


void exibeAVL(AVL *raiz){
    if(raiz!=NULL){
        exibeAVL(raiz->filhoEsq);
        printf("%d\n",raiz->chave);
        exibeAVL(raiz->filhoDir);
    }
}

// INSERÇÃO EM UMA ARVORE AVL - CASOS A VERIFICAR.
// CASO 1) SE A RAIZ FOR NULA, INSERIR O NÓ E ESTE SERÁ A RAIZ.
// CASO 2) SE O NO INSERIDO FOR MENOR QUE A RAIZ, IR PARA A SUB-ARVORE A ESQUERDA DA RAIZ.
// CASO 3) SE O NO INSERIDO FOR MAIOR QUE A RAIZ, IR PARA A SUB-ARVORE A DIREITA DA RAIZ.
// SERÁ APLICADO O MÉTODO COM RECURSÃO. VOLTANDO DA RECURSAO, RECALCULAREI A ALTURA DE CADA SUBARVORE.
// APLICAREI A ROTAÇÃO SE FOR NECESSÁRIO (FATOR DE BALANCEAMENTO PASSA A SER +2 OU -2.

int insereAVL(AVL *raiz, int chave, Dados *d){
    AVL *auxiliar;
    auxiliar = malloc(sizeof(AVL));
    int resposta;
    if(raiz==NULL){ // CASO A ARVORE FOR NULA OU O NÓ É FOLHA
        auxiliar->chave = chave;
        auxiliar->alt = 0;
        auxiliar->filhoEsq = NULL;
        auxiliar->filhoDir = NULL;
        auxiliar->DATA = d;
        raiz = auxiliar;
        return 1;
    }
    auxiliar = raiz;
    if(chave < auxiliar->chave){
        if( (resposta=insereAVL(auxiliar->filhoEsq,chave, d)) == 1 ){
            if( fatorDeBalanceamento(auxiliar) >=2 ){
                if(chave < raiz->filhoEsq->chave) RSD(raiz);
                else RED(raiz);
            }
        }
    }
    else{
        if(chave>auxiliar->chave){
            if(  (resposta = insereAVL(auxiliar->filhoDir, chave, d)) == 1 ){
                if(fatorDeBalanceamento(auxiliar) >=2){
                    if(raiz->filhoDir->chave < chave) RSE(raiz);
                    else RDE(raiz);
                }
            }
        }
        else return 0;
    }
    auxiliar->alt = 1 + maior( altura(auxiliar->filhoEsq), altura(auxiliar->filhoDir));
    return resposta;
}

//REMOÇÃO DE UM NO DE UMA ARVORE AVL - CASOS A VERIFICAR
// CASO 1) O NÓ A SER REMOVIDO É UMA FOLHA (POSSUI FILHOS IGUAIS / AMBOS NULOS)
// CASO 2) O NÓ A SER REMOVIDO POSSUI UM FILHO
// CASO 3) O NÓ A SER REMOVIDO POSSUI DOIS FILHOS
// Removendo um nó da sub-árvore a direita, será necessário balancear à esquerda, e vice-versa.

int removeAVL(AVL *raiz, int chave){
    if(raiz==NULL) return 0; // Arvore inicialmente vazia ou valor não encontrado
    int resposta;
    if(chave < raiz->chave){
        if( (resposta = removeAVL(raiz->filhoEsq,chave))== 1){
            if(fatorDeBalanceamento(raiz)>=2){
                if(alturaDoNo(raiz->filhoDir->filhoEsq) <= alturaDoNo(raiz->filhoDir->filhoDir))
                    RSE(raiz);
                else
                    RDE(raiz);
            }
        }
    }
    if(raiz->chave < chave){
        if((resposta = removeAVL(raiz->filhoDir,chave))==1){
            if(fatorDeBalanceamento(raiz)>=2){
                if(altura(raiz->filhoEsq->filhoDir) <= altura(raiz->filhoEsq->filhoEsq))
                    RSD(raiz);
                else
                    RED(raiz);
            }
        }
    }
    if(raiz->chave == chave){
        if(raiz->filhoEsq == NULL || raiz->filhoDir == NULL){ // Caso o nó tenha 1 filho ou nenhum (folha)
            AVL *antigo = raiz;
            if(raiz->filhoEsq !=NULL) raiz = raiz->filhoEsq;
            else raiz = raiz->filhoDir;
            free(antigo);
        }
        else{ // Caso o nó tenha 2 filhos, entra MdM
            AVL *varTemporaria = menorNo(raiz->filhoDir);
            raiz->chave = varTemporaria->chave;
            removeAVL(raiz->filhoDir, raiz->chave);
            if(fatorDeBalanceamento(raiz)>=2){
                if(altura(raiz->filhoEsq->filhoDir) <= altura(raiz->filhoEsq->filhoEsq))
                    RSD(raiz);
                else
                    RED(raiz);
            }
        }
        return 1;
    }
    return resposta;
}

int arvoreCheia(AVL *raiz){
    if(quantosNos(raiz)>=240) return 1;
    else return 0;
}

int chaveNo(AVL *no){
    return (no->DATA->dia)*1000 + (no->DATA->hora) *10 + (no->DATA->consultorio);
}


int main(){

    AVL *arvoreSemana[5];

    int option=1, semana=1, populacao;
    int dia=-1,hora=-1,sala=-1;
    int chave;
    int inseriu = 0, flag=0;


    printf("                    CLINICA DE PSICOLOGIA\n");
    printf("    (1) Simular insercao de agendamentos aleatorios\n");
    printf("    (2) Remover agendamentos\n");
    printf("    (3) Consultar um agendamento\n");
    printf("    (4) Exibir todos os agendamentos\n");
    printf("    (5) Terminar\n");
    printf("Por favor, digite a opcao que desejar:\n");
    scanf("%d",&option);


    while(option!=5){
        while(option<1 || option>5){
            system("cls");
            printf("                    CLINICA DE PSICOLOGIA\n");
            printf("    (1) Simular insercao de agendamentos aleatorios\n");
            printf("    (2) Remover agendamentos\n");
            printf("    (3) Consultar um agendamento\n");
            printf("    (4) Exibir todos os agendamentos\n");
            printf("    (5) Terminar\n");
            printf("Por favor, digite a opcao que desejar:\n");
            scanf("%d",&option);
        }
        if(option == 1){
            while(semana <1 || semana>4){
                system("cls");
                printf("Inserir em que semana? (1/2/3/4)\n");
                scanf("%d",&semana);
            }

            printf("\n");
            printf("Gerar quantos dados aleatorios?\n");
            scanf("%d",&populacao);
            Dados *dad;
            AVL *no;
            inseriu = 0;
            while(populacao>0 && arvoreCheia(arvoreSemana[semana])!=1){
                dad = malloc(sizeof(Dados));
                no = malloc(sizeof(AVL));
                dia=-1,hora=-1,sala=-1;
                while(dia>5||dia<1){
                    dia = 1 + rand() % 4;
                }
                while(hora<9||hora>21){
                    hora = 9 + rand() % 11;
                }
                while(sala<0||sala>4){
                    sala = 1 + rand() % 3;
                }

                dad->consultorio = sala;
                dad->dia = dia;
                dad->hora = hora;
                dad->paciente = 1+ rand()%200;
                dad->psicologo = 1 + rand() % 1000;

                no->DATA = dad;
                no->filhoEsq = NULL;
                no->filhoDir = NULL;
                no->alt = 0;

                chave = chaveNo(no);
                flag = insereAVL(arvoreSemana[semana], chave, no);
                if(flag==1) inseriu++;
                flag = 0;
                populacao --;
            }
            printf("\n\tForam inseridos %d registros.",inseriu);


        }

    }


}
