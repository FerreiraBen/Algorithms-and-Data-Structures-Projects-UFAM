
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct {
	int chave;
	int dia,mes,ano;/*(dd/mm/aa)*/
	int id_produto;/*(1000<9999)*/
	int valor;/*(s� inteiros)*/
	int forma_pagamento,parcelas,valor_parcelas;/*FP(1/2/3)P(2<10)VP(valor/parcelas)*/
}dados_venda;

long int codificar(dados_venda nova_venda){
	 int codigo = 0;
	if(nova_venda.dia<10){
		if(nova_venda.mes<10){
			codigo = (codigo+(nova_venda.dia*10000000));
			codigo = (codigo+(nova_venda.mes*1000000));
			codigo = (codigo+(nova_venda.ano*10000));
			codigo = (codigo+(nova_venda.id_produto));
		}
		else{
			codigo = (codigo+(nova_venda.dia*100000000));
			codigo = (codigo+(nova_venda.mes*1000000));
			codigo = (codigo+(nova_venda.ano*10000));
			codigo = (codigo+(nova_venda.id_produto));
		}
	}
	else{
		if(nova_venda.mes<10){
			codigo = (codigo+(nova_venda.dia*10000000));
			codigo = (codigo+(nova_venda.mes*1000000));
			codigo = (codigo+(nova_venda.ano*10000));
			codigo = (codigo+(nova_venda.id_produto));
		}
		else{
			codigo = (codigo+(nova_venda.dia*100000000));
			codigo = (codigo+(nova_venda.mes*1000000));
			codigo = (codigo+(nova_venda.ano*10000));
			codigo = (codigo+(nova_venda.id_produto));
		}

	}

	return codigo;
}


#define O 300 // ORDEM
#define M ((2*O)-1) // M�ximo de chaves por p�gina
#define m (O-1) // M�nimo de chaves por p�gina

// VARIAVEIS GLOBAIS




//=================================================================|
//-------------------  PARTE ESTRUTURAL DA ARVORE  ----------------|

typedef struct pagina{
    int quantidade;
    dados_venda dados[M];
    struct pagina *filhos[M+1];
} arvB;

//-----------------------------------------------------------------



//=================================================================|
//-------------------  FUN��O CRIA ARVORE  ------------------------|

// Aloca mem�ria para o tipo arvB e setta(to set) todos os filhos para NULL
arvB *criarArvB(){
    arvB *raiz=(arvB*)malloc(sizeof(arvB));
    raiz->quantidade=0;
    int i = 0;
    while(i<=M){
		raiz->filhos[i]=NULL;
		i++;
	}
    return raiz;
}

//-----------------------------------------------------------------



//=================================================================|
//-------------------  FUN��O DE BUSCA BIN�RIA  -------------------|

/* A Fun��o de busca bin�ria abaixo sugere onde o elemento buscado
se encontra, ou onde ele deve ser inserido caso ainda n�o esteja.*/
int busca_binaria(arvB *pagina, int valor){
    int principio, fim, meio;
    if(pagina->quantidade == 0){

		return 0;
	}
    principio = 0;
    fim = pagina->quantidade - 1;

    while(principio <= fim){
        meio = (principio + fim)/2;
        if(valor == pagina->dados[meio].chave){
			return meio;
		}
        else if(valor<pagina->dados[meio].chave){
            fim = (meio-1);
        }
        else principio = meio+1;
    }
    return principio;
}

//-----------------------------------------------------------------



//=================================================================|
//-------------------  FUN��ES AUXILIARES  ------------------------|

//Retorna o m�ximo de chaves que uma determinada arvore a partir da
//altura m�xima que � submetida a crescer, e a quantidade m�xima
//de chaves que cada pagina pode conter.
int maxChaves(int maxAltura, int max){
	int i;
	int somador=0;
	for(i=0; i<maxAltura; i++) somador+=((somador+1)*max);
    return somador;
}

//Verifica se a p�gina � folha
short int ehFolha(arvB *pagina){
    if(pagina->filhos[0] == NULL) return 1;
    return 0;
}

//Procura a Maior chave (MdM)
dados_venda maiorChave(arvB *pagina){
    if(ehFolha(pagina)){
		return pagina->dados[pagina->quantidade-1];
	}
    else{
		return maiorChave(pagina->filhos[pagina->quantidade]);
	}
}

//Procura a Menor chave (MdM)
dados_venda menorChave(arvB *pagina){
    if(ehFolha(pagina)){
		return pagina->dados[0];
	}
    else{
		return menorChave(pagina->filhos[0]);
	}
}

//Imprime �rvore
void impressao(arvB *raiz, int nivel){
	int i,j;
    if(raiz == NULL){
		return ; //Vazio
	}
 	i = 0;
    while(i<raiz->quantidade){
        impressao(raiz->filhos[i], nivel+1);
        j = 0;
        while(j<nivel){
        	printf("CODIGO:%d \n", raiz->dados[i].chave);
        	printf("DATA:%d/%d/%d \n", raiz->dados[i].dia, raiz->dados[i].mes, raiz->dados[i].ano);
        	printf("ID PRODUTO:%d \n", raiz->dados[i].id_produto);
        	printf("VALOR:%d \n", raiz->dados[i].valor);
        	printf("FORMA DE PAGAMENTO:%d \n", raiz->dados[i].forma_pagamento);
        	printf("PARCELAS:%d \n", raiz->dados[i].parcelas);
        	printf("VALOR PARCELAS:%d \n", raiz->dados[i].valor_parcelas);
        	j++;
		}
    	i++;
    }
    impressao(raiz->filhos[raiz->quantidade], nivel+1);
}

//Impress�o 2.0 - IMPRIME TODOS OS ELEMENTOS DA ARVORE
void imprimirArvB(arvB *raiz){
    if(raiz==NULL) return;
    int i = 0;
    while(i<raiz->quantidade){
        imprimirArvB(raiz->filhos[i]);
        printf("CODIGO:%d \n", raiz->dados[i].chave);
  		printf("DATA:%d/%d/%d \n", raiz->dados[i].dia, raiz->dados[i].mes, raiz->dados[i].ano);
  		printf("ID PRODUTO:%d \n", raiz->dados[i].id_produto);
  		printf("VALOR:%d \n", raiz->dados[i].valor);
  		if(raiz->dados[i].forma_pagamento == 1){
			  printf("CARTÃO DE CRÉDITO\n");
		}
  		if(raiz->dados[i].forma_pagamento == 2){
			  printf("CARTÃO DE DÉBITO\n");
		}
  		if(raiz->dados[i].forma_pagamento == 3){
			  printf("DINHEIRO\n");
		}
  		printf("PARCELAS:%d \n", raiz->dados[i].parcelas);
  		printf("VALOR PARCELAS:%d \n", raiz->dados[i].valor_parcelas);
  		printf("-----------------------------\n");
  		i++;
	}
	imprimirArvB(raiz->filhos[raiz->quantidade]);
}

int contador = 0;
//-----------------------------------------------------------------
int conta_nos(arvB *raiz){
    if(raiz==NULL) return 0;
    int i=0;

    while(i<raiz->quantidade){
        conta_nos(raiz->filhos[i]);
  		contador++;
        i++;
	}
	conta_nos(raiz->filhos[raiz->quantidade]);
	return contador;
}


//=================================================================|
//--------------  FUN��O DE BUSCA POR EXISTENCIA  -----------------|

// Retorna 1 se a �rvore possui o elemento, e 0 caso contr�rio.
int buscarArvB(arvB *raiz, int chave){
	int i;
	i=0;
    if(raiz == NULL){
		return 0;
	}
    while((i < raiz->quantidade)&&(chave > raiz->dados[i-1].chave)){
		i++;
    	if(raiz->dados[i-1].chave == chave) return 1; //ACHOU!!
	}
    if(chave < raiz->dados[i-1].chave){
		buscarArvB(raiz->filhos[i-1], chave);
	}
    else{
		buscarArvB(raiz->filhos[i], chave);
	}
}

//-----------------------------------------------------------------



//=================================================================|
//-------------------  FUN��O SPLIT  ------------------------------|

/* Ap�s a inser��o de um elemento nos limites da capacidade de uma
pagina, eleva-se o elemento central e divide a pagina em dois filhos.
// m = m�nimo de chaves
// M = m�ximo de chaves*/

void split(arvB *pagina, int i){
	int j;
    arvB *page1 = criarArvB();
    arvB *page2 = pagina->filhos[i];
    page1->quantidade = m;
    j = 0;
    while(j<m){
        page1->dados[j] = page2->dados[m+j+1];
        page1->filhos[j] = page2->filhos[m+j+1];
		j++;
    }
    page1->filhos[m] = page2->filhos[M];
	j = pagina->quantidade;

    while(j>i){
        pagina->dados[j] = pagina->dados[j-1];
        pagina->filhos[j+1] = pagina->filhos[j];
		j--;
    }
    pagina->filhos[i+1] = page1;
    pagina->dados[i] = page2->dados[m];
    pagina->quantidade++;
    page2->quantidade = m;
}

//-----------------------------------------------------------------



//=================================================================|
//---------------  FUN��O INSER��O PARA P�GINA COM ESPA�O  --------|


void inserirArvoreComEspaco(arvB *pagina, dados_venda novo) {
	int i;
    i = pagina->quantidade;
    if(ehFolha(pagina)){
        while((i>0)&&(pagina->dados[i-1].chave > novo.chave)){
            pagina->dados[i] = pagina->dados[i-1];
            i--;
        }
        pagina->dados[i].chave = novo.chave;
        pagina->dados[i].dia = novo.dia;
        pagina->dados[i].mes = novo.mes;
        pagina->dados[i].ano = novo.ano;
        pagina->dados[i].id_produto = novo.id_produto;
        pagina->dados[i].valor = novo.valor;
        pagina->dados[i].forma_pagamento = novo.forma_pagamento;
        pagina->dados[i].parcelas = novo.parcelas;
        pagina->dados[i].valor_parcelas = novo.valor_parcelas;
        pagina->quantidade++;
    }
    else{
        i = busca_binaria(pagina, novo.chave);
        if(pagina->filhos[i]->quantidade == M){
            split(pagina, i);
            if(novo.chave > pagina->dados[i].chave) i++;
        }
        inserirArvoreComEspaco(pagina->filhos[i], novo);
    }
}

//-----------------------------------------------------------------



//=================================================================|
//-------------------  FUN��O INSER��O OFICIAL  -------------------|

void inserirArvB(arvB **raiz, dados_venda novo){
    if((*raiz)->quantidade == M){
        arvB *s = criarArvB();
        s->filhos[0] = *raiz;
        *raiz = s;
        split(s, 0);
        inserirArvoreComEspaco(s, novo);
    }
    else inserirArvoreComEspaco(*raiz, novo);
}

//-----------------------------------------------------------------



//=================================================================|
//----------------  FUN��O REMO��O SIMPLES EM P�GINA  -------------|

void removerChave(arvB *no, int posicao){
    int i;
    for(i=posicao; i<no->quantidade; i++){
        no->dados[i] = no->dados[i+1];
        no->filhos[i+1]=no->filhos[i+2];
    }
    no->quantidade--;
}

//-----------------------------------------------------------------



//=================================================================|
//--------------------------  FUN��O JOIN  ------------------------|

/* Faz um join e retorna a nova posicao da chave do meio.
join jun��o de dois filhos, redu��o do numero de chaves do pai. */
// faz um join e retorna a nova posicao da chave do meio

void join(arvB *filhoEsq, arvB *filhoDir, dados_venda dados){
	int i;
    filhoEsq->dados[filhoEsq->quantidade].chave = dados.chave;
    filhoEsq->dados[filhoEsq->quantidade].dia = dados.dia;
    filhoEsq->dados[filhoEsq->quantidade].mes = dados.mes;
    filhoEsq->dados[filhoEsq->quantidade].ano = dados.ano;
    filhoEsq->dados[filhoEsq->quantidade].id_produto = dados.id_produto;
    filhoEsq->dados[filhoEsq->quantidade].valor = dados.valor;
    filhoEsq->dados[filhoEsq->quantidade].forma_pagamento = dados.forma_pagamento;
    filhoEsq->dados[filhoEsq->quantidade].parcelas = dados.parcelas;
    filhoEsq->dados[filhoEsq->quantidade].valor_parcelas = dados.valor_parcelas;
    i=0;
    while(i<filhoDir->quantidade){
        filhoEsq->dados[filhoEsq->quantidade+i+1] = filhoDir->dados[i];
        filhoEsq->filhos[filhoEsq->quantidade+i+1] = filhoDir->filhos[i];
		i++;
    }
    filhoEsq->filhos[filhoEsq->quantidade+filhoDir->quantidade+1]=filhoDir->filhos[filhoDir->quantidade];
    filhoEsq->quantidade=(filhoEsq->quantidade)+(filhoDir->quantidade+1);
    free(filhoDir);
}

//-----------------------------------------------------------------



//=================================================================|
//-------------------  FUN��O REMO��O RECURSIVA  ------------------|

void remocaoRecursiva(arvB *pagina, dados_venda dados_remove){
	int i;
    int posicao = busca_binaria(pagina,dados_remove.chave);
    // verifica se no � uma folha
    // caso 1, eh folha e n > m
    if(ehFolha(pagina)){
        if(pagina->dados[posicao].chave == dados_remove.chave){
            removerChave(pagina, posicao);
        }
    }


    else{
        // caso2, � n� interno e chave est� no n�
        if(pagina->dados[posicao].chave == dados_remove.chave){
            arvB *fEsq = pagina->filhos[posicao];
            arvB *fDir = pagina->filhos[posicao+1];

            // caso 2.1 - o filho predecessor tem mais que o m�nimo de chave
            if(fEsq->quantidade>m){
                // substitui chave pelo predecessor
                dados_venda predecessor = maiorChave(fEsq);
                remocaoRecursiva(fEsq, predecessor);
                pagina->dados[posicao] = predecessor;
            }

            // caso 2.2 - filho sucessor tem mais que o m�nimo de chave
            else if(fDir->quantidade>m){
                // substitui chave pelo predecessor
                dados_venda sucessor = menorChave(fDir);
                remocaoRecursiva(fDir, sucessor);
                pagina->dados[posicao] = sucessor;
            }

            //  caso 2.3 - precisa juntar (join/merge)
            else{
                join(fEsq, fDir, dados_remove);
                for(i=posicao+1; i<pagina->quantidade; i++){
                    pagina->dados[i-1]=pagina->dados[i];
                    pagina->filhos[i]=pagina->filhos[i+1];
                }
                pagina->filhos[pagina->quantidade]=NULL;
                pagina->quantidade--;
                remocaoRecursiva(fEsq, dados_remove);
            }
        }


        // caso 3 - chave nao esta no no
        else{
            arvB *auxiliar=pagina->filhos[posicao];

            if(auxiliar->quantidade==m){
                arvB *esquerda=NULL;
                arvB *direita=NULL;

                if(posicao > 0) esquerda=pagina->filhos[posicao-1];

                if(posicao<M) direita=pagina->filhos[posicao+1];

                if(esquerda != NULL&&esquerda->quantidade>m){
                    // desce uma chave do no para auxiliar e sobe uma
                    dados_venda chave_desce = pagina->dados[posicao-1];
                    dados_venda chave_sobe = esquerda->dados[esquerda->quantidade-1];
                    arvB *filho_move = esquerda->filhos[esquerda->quantidade];

                    // desloca chaves  e filhos de auxiliar para direita
                    auxiliar->filhos[auxiliar->quantidade+1]=auxiliar->filhos[auxiliar->quantidade];
                    for(i=auxiliar->quantidade; i>0; i--){
                        auxiliar->dados[i]=auxiliar->dados[i-1];
                        auxiliar->filhos[i]=auxiliar->filhos[i-1];
                    }
                    auxiliar->dados[0] = chave_desce;
                    auxiliar->filhos[0]=filho_move;
                    auxiliar->quantidade++;

                    // sobe a chave da esquerda
                    pagina->dados[posicao-1]=chave_sobe;
                    esquerda->dados[esquerda->quantidade-1].chave = 0;
                    esquerda->dados[esquerda->quantidade-1].dia = 0;
                    esquerda->dados[esquerda->quantidade-1].mes = 0;
                    esquerda->dados[esquerda->quantidade-1].ano = 0;
                    esquerda->dados[esquerda->quantidade-1].id_produto = 0;
                    esquerda->dados[esquerda->quantidade-1].valor = 0;
                    esquerda->dados[esquerda->quantidade-1].forma_pagamento = 0;
                    esquerda->dados[esquerda->quantidade-1].parcelas = 0;
                    esquerda->dados[esquerda->quantidade-1].valor_parcelas = 0;

                    esquerda->filhos[esquerda->quantidade]=NULL;
                    esquerda->quantidade--;
                }

                else if(direita!=NULL&&direita->quantidade>m){
                    // desce uma chave do no para auxiliar e sobe uma
                    dados_venda chave_desce=pagina->dados[posicao];
                    dados_venda chave_sobe=direita->dados[0];
                    arvB *filho_move=direita->filhos[0];

                    // desce chave na ultima posicao de auxiliar
                    auxiliar->dados[auxiliar->quantidade]=chave_desce;
                    auxiliar->filhos[auxiliar->quantidade+1]=filho_move;
                    auxiliar->quantidade++;

                    // sobe a chave da direita
                    pagina->dados[posicao]=chave_sobe;

                    // desloca chaves da direita
                    for(i=0; i<direita->quantidade-1; i++){
                        direita->dados[i]=direita->dados[i+1];
                        direita->filhos[i]=direita->filhos[i+1];
                    }
                    direita->filhos[direita->quantidade-1]=direita->filhos[direita->quantidade];
                    direita->filhos[direita->quantidade]=NULL;
                    direita->quantidade--;
                }


                else{ //faz a jun��o (join/merge)
                    if(esquerda!=NULL){
                        join(esquerda, auxiliar, pagina->dados[posicao-1]);
                        // SHIFT
                        for(i=posicao; i<pagina->quantidade; i++){
                            pagina->dados[i-1]=pagina->dados[i];
                            pagina->filhos[i]=pagina->filhos[i+1];
                        }
                        pagina->filhos[pagina->quantidade]=NULL;
                        pagina->quantidade--;
                        auxiliar=esquerda;
                    }

                    else{
                        join(auxiliar, direita, pagina->dados[posicao]);
                        for(i=posicao+1; i<pagina->quantidade; i++){
                            pagina->dados[i-1]=pagina->dados[i];
                            pagina->filhos[i]=pagina->filhos[i+1];
                        }
                        pagina->filhos[pagina->quantidade]=NULL;
                        pagina->quantidade--;
                    }
                }
            }
            remocaoRecursiva(auxiliar, dados_remove);
        }
    }
}
//-----------------------------------------------------------------

dados_venda busca_remocao(arvB *raiz, int chave){
	int i = 0;
    if(raiz == NULL){
      dados_venda n;
		return n;
	}
    while((i<raiz->quantidade)&&(chave>raiz->dados[i-1].chave)){
		i++;
		if(raiz->dados[i-1].chave == chave){
			return raiz->dados[i-1];
		}//ACHOU!!

	}
	if(chave < raiz->dados[i-1].chave){
		buscarArvB(raiz->filhos[i-1], chave);
	}
    else buscarArvB(raiz->filhos[i], chave);
}

//=================================================================|
//-------------------  FUN��O REMO��O OFICIAL  --------------------|
void removerArvB(arvB **raiz, int valor){
	dados_venda dados_remove;
	dados_remove = busca_remocao(*raiz,valor);
    remocaoRecursiva(*raiz, dados_remove);
    if ((*raiz)->quantidade == 0) *raiz = (*raiz)->filhos[0];
}
//-----------------------------------------------------------------
/*Fun��es auxiliares, para a solu�a� do problema*/

int verifica_data(dados_venda dados){
	int bissexto = 12;
	int i_b = 0;
	if(dados.mes == 2){
		if((0 < dados.dia) && (dados.dia <= 28)){
			return 1;
		}
		else{
		while(i_b<20){
			if(dados.ano == bissexto){
				return 1;
			}
			else{
				bissexto = bissexto+4;
			}
			i_b++;
			}
			printf("DIA 29 DE FEVEREIRO S� EXISTE EM ANO BISSEXTO E 20%d N�O � BISSEXTO\n", dados.ano);
			return 0;
		}
	}
	else if(dados.mes == (4)||(6)||(9)||(11)){
		if((0 < dados.dia) && (dados.dia < 31)){
			return 1;
		}
		else{
			printf("ESSE M�S S� VAI AT� O DIA 30\n");
			return 0;
		}
	}
	else{
		if((0 < dados.dia) && (dados.dia < 32)){
			return 1;
		}
		else{
			printf("ESSE M�S S� VAI AT� O DIA 31\n");
			return 0;
		}
	}
	return 0;
}

/*Ler os dados a serem inseridos no caso de uma nova venda e retorna os dados usando a estrutura dados_venda*/
dados_venda ler_nova_venda(){
	int confirma = 0;
	dados_venda nova;
	while(confirma == 0){
		printf("INFORME A DATA(dd/mm/aa):");
 		scanf("%d/%d/%d",&nova.dia,&nova.mes,&nova.ano);
 		printf("A DATA É %d/%d/%d, CONFIRMA ?\n<1>SIM <0>NÃO\n",nova.dia,nova.mes,nova.ano);
 		scanf("%d",&confirma);
 		while(confirma > 1){
 			printf("<1>SIM <0>NÃO\n");
			 scanf("%d",&confirma);
		}
	}
	confirma = 0;
	while(confirma == 0){
		printf("INFORME O ID DO PRODUTO(1000 A 9999):");
		scanf("%d",&nova.id_produto);
		printf("O CÓDIGO DO PRODUTO É %d, CONFIRMA ?\n<1>SIM <0>NÃO\n",nova.id_produto);
 		scanf("%d",&confirma);
 		while(confirma > 1){
 			printf("<1>SIM <0>NÃO\n");
			 scanf("%d",&confirma);
		}
	}
	confirma = 0;
	while(confirma == 0){
		printf("INFORME O VALOR:");
		scanf("%d",&nova.valor);
		printf("O VALOR DO PRODUTO É %d, CONFIRMA ?\n<1>SIM <0>NÃO\n",nova.valor);
 		scanf("%d",&confirma);
 		while(confirma > 1){
 			printf("<1>SIM <0>NÃO\n");
			 scanf("%d",&confirma);
		}
	}

	printf("INFORME A FORMA DE PAGAMENTO:\n1-CREDITO\n2-DEBITO\n3-DINHEIRO\n");
	scanf("%d",&nova.forma_pagamento);
	if(nova.forma_pagamento == 1){
		printf("INFORME A QUANTIDADE DE PARCELAS:");
		scanf("%d",&nova.parcelas);
		nova.valor_parcelas=(nova.valor/nova.parcelas);
	}
	else{
		nova.parcelas = 0;
		nova.valor_parcelas = 0;
	}
	nova.chave = codificar(nova);
	return nova;
}

dados_venda simulacao_dados(){
	dados_venda simula_dados;
	simula_dados.chave = 0;
	simula_dados.dia = 0;
	simula_dados.mes = 0;
	simula_dados.ano = 0;
	simula_dados.id_produto = 0;
	simula_dados.valor=0;
	simula_dados.forma_pagamento = 0;
	simula_dados.parcelas = 0;
	simula_dados.valor_parcelas = 0;

	while(simula_dados.mes == 0){
		simula_dados.mes = rand()%13;
	}
	if(simula_dados.mes == 2){
		while(simula_dados.dia == 0){
			simula_dados.dia = rand()%29;
		}

	}
	else if(simula_dados.mes == (4)||(6)||(9)||(11)){
		while(simula_dados.dia == 0){
			simula_dados.dia = rand()%31;
		}
	}
	else{
		while(simula_dados.dia == 0){
			simula_dados.dia = rand()%32;
		}
	}
	while(simula_dados.ano <=17){
		simula_dados.ano = rand()%21;
	}

	while((simula_dados.id_produto <=999)||(simula_dados.id_produto>9999)){
		simula_dados.id_produto = rand()%10000;
	}

	while(simula_dados.valor == 0){
		simula_dados.valor = rand()%100000;
	}
	while(simula_dados.forma_pagamento == 0){
		simula_dados.forma_pagamento = rand()%4;
	}

	if(simula_dados.forma_pagamento == 1){
		while(simula_dados.parcelas == 0){
			simula_dados.parcelas = rand()%13;
		}
		simula_dados.valor_parcelas = (simula_dados.valor)/(simula_dados.parcelas);
	}

	simula_dados.chave = codificar(simula_dados);
	return simula_dados;
}


/*-----------------------------------------------------------------*/

arvB *janeiro;
arvB *fevereiro;
arvB *marco;
arvB *abril;
arvB *maio;
arvB *junho;
arvB *julho;
arvB *agosto;
arvB *setembro;
arvB *outubro;
arvB *novembro;
arvB *dezembro;
arvB *ano;

int data_atual_mes,data_atual_ano,data_atual_dia;

dados_venda nova;

void inserir_em_mes(dados_venda nova_venda){
	if(nova_venda.ano< data_atual_ano-1 || (nova_venda.ano== data_atual_ano-1 && nova_venda.mes<   data_atual_mes)){
			inserirArvB(&ano, nova_venda);
	}else{
	if(nova_venda.mes == 1){
		inserirArvB(&janeiro,nova_venda);
		return ;
	}
	else if(nova_venda.mes == 2){
		inserirArvB(&fevereiro, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 3){
		inserirArvB(&marco, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 4){
		inserirArvB(&abril, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 5){
		inserirArvB(&maio, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 6){
		inserirArvB(&junho, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 7){
		inserirArvB(&julho, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 8){
		inserirArvB(&agosto,nova_venda);
		return ;
	}
	else if(nova_venda.mes == 9){
		inserirArvB(&setembro, nova_venda);
		return ;
	}
	else if(nova_venda.mes == 10){
		inserirArvB(&outubro,nova_venda);
		return ;
	}
	else if(nova_venda.mes == 11){
		inserirArvB(&novembro, nova_venda);
		return ;
	}
	else{
		inserirArvB(&dezembro, nova_venda);
		return ;
	}

	}
	return ;
}
//imprime os valores acumulados pela funcao acumula_valores
void imprimeValoresAcumulados(arvB *raiz, int ano, int valor,int mes){
  if(valor!=0){
  if(mes==1)  printf("Janeiro 20%d: %d\n",ano,valor);
  if(mes==2)  printf("Fevereiro 20%d: %d\n",ano,valor);
  if(mes==3)  printf("Março 20%d: %d\n",ano,valor);
  if(mes==4)  printf("Abril 20%d: %d\n",ano,valor);
  if(mes==5)  printf("Maio 20%d: %d\n",ano,valor);
  if(mes==6)  printf("Junho 20%d: %d\n",ano,valor);
  if(mes==7)  printf("Julho 20%d: %d\n",ano,valor);
  if(mes==8)  printf("Agosto 20%d: %d\n",ano,valor);
  if(mes==9)  printf("Setembro 20%d: %d\n",ano,valor);
  if(mes==10)  printf("Outubro 20%d: %d\n",ano,valor);
  if(mes==11)  printf("Novembro 20%d: %d\n",ano,valor);
  if(mes==12)  printf("Dezembro 20%d: %d\n",ano,valor);
  if(mes==0)  printf("Contas de 20%d com mais de 1 ano: %d\n",ano,valor);
  }
}
//soma os valores de cada arvore, o parametro 'passado' determina se tais valores são passados( anterior ao mes e atual) ou futuro(posterior ou igual ao mes e ano atual)
int pegaTotais(arvB *raiz,int nivel,int passado){
  int valor=0,i =0;
  if(raiz==NULL) return 0;
  while(i<raiz->quantidade){
      valor+=pegaTotais(raiz->filhos[i],nivel+1,passado);
      if(passado == 1){
        if((raiz->dados[i].ano ==data_atual_ano && raiz->dados[i].mes<data_atual_mes) || raiz->dados[i].ano <data_atual_ano){
            valor+=raiz->dados[i].valor;
        }
      }else{
        if((raiz->dados[i].ano ==data_atual_ano && raiz->dados[i].mes>=data_atual_mes) || raiz->dados[i].ano >data_atual_ano){
            valor+=raiz->dados[i].valor;
        }
      }
  		  i++;
  }
  if(nivel==0){


    valor+=pegaTotais(raiz->filhos[i],nivel+1,passado);

  }
   return valor;
}
int acumula_valores(arvB *raiz, int nivel, int formPag,int mes){
    if(raiz==NULL) return 0;
    int i = 0,valor =0;
    static int anoRegistroAnterior=0;
    if(raiz==NULL) return 0;
    while(i<raiz->quantidade){
      valor+=acumula_valores(raiz->filhos[i],nivel+1,formPag,mes);
  		if(raiz->dados[i].forma_pagamento == formPag){
        if(anoRegistroAnterior!= raiz->dados[i].ano){
          if(anoRegistroAnterior!=0){
            imprimeValoresAcumulados(raiz,anoRegistroAnterior,valor,mes);
          }
          anoRegistroAnterior = raiz->dados[i].ano;
          valor = 0;
        }
        valor+=raiz->dados[i].valor;
		  }
  		i++;
	}
  if(nivel==0){
    valor+=acumula_valores(raiz->filhos[i],nivel+1,formPag,mes);
    imprimeValoresAcumulados(raiz,anoRegistroAnterior,valor,mes);
  }
  return valor;
}

void menu(){
	int opc;

	while(opc!=7){
		printf("[1]RODAR SIMULAÇÃO DE VENDAS\n[2]EXIBIR MESES\n[3]EXIBIR CONTAS DE 1 ANO\n[4]FAZER NOVA VENDA\n[5]REMOVER VENDA\n[6]ESTATÍSTICAS\n[7]SAIR\n");
		printf("DIGITE UMA OPÇÃO:");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				printf("DIGITE O TAMANHO DA AMOSTRA DE DADOS DA SIMULAÇÃO(EX:1000):\n");
				int amostra;
				scanf("%d",&amostra);
				int conta_amostra = 0;
				while(conta_amostra < amostra){
					nova = simulacao_dados();
					if(verifica_data(nova)==1){
						inserir_em_mes(nova);
						printf("VENDA FINALIZADA - Data:%d/%d/%d, Id do Produto:%d, Valor:%d, Forma de Pagamento:%d, parcelas:%d\n",nova.dia,nova.mes,nova.ano,nova.id_produto,nova.valor,nova.forma_pagamento,nova.parcelas);
						conta_amostra++;
					}
					else{
						conta_amostra--;
					}
				}
				system("pause");
				system("cls");
				break;
			case 2:
				printf("ESCOLHA UM MES PRA SER EXIBIDO:\n[1]JANEIRO\n[2]FEVEREIRO\n[3]MARÇO\n[4]ABRIL\n[5]MAIO\n[6]JUNHO\n");
				printf("[7]JULHO\n[8]AGOSTO\n[9]SETEMBRO\n[10]OUTUBRO\n[11]NOVEMBRO\n[12]DEZEMBRO\n[13]VOLTAR\n");
				int escolha;
				scanf("%d",&escolha);
				switch(escolha){
				case 1:
					imprimirArvB(janeiro);
					break;
				case 2:
					imprimirArvB(fevereiro);
					break;
				case 3:
					imprimirArvB(marco);
					break;
				case 4:
					imprimirArvB(abril);
					break;
				case 5:
					imprimirArvB(maio);
					break;
				case 6:
					imprimirArvB(junho);
					break;
				case 7:
					imprimirArvB(julho);
					break;
				case 8:
					imprimirArvB(agosto);
					break;
				case 9:
					imprimirArvB(setembro);
					break;
				case 10:
					imprimirArvB(outubro);
					break;
				case 11:
					imprimirArvB(novembro);
					break;
				case 12:
					imprimirArvB(dezembro);
					break;
				case 13:
					break;
				default:
					printf("##DIGITE UMA OPÇÃO VÁLIDA##\n");
					system("pause");
					system("cls");
					break;
				}
				break;

			case 3:
				printf("CONTAS A MAIS DE 1 ANO\n");
				imprimirArvB(ano);
				break;
			case 4:
				nova = ler_nova_venda();
				if(verifica_data(nova)==1){
					inserir_em_mes(nova);
					printf("VENDA FINALIZADA\n");
				}
				break;
			case 5:
				printf("DIGITE O MES QUE DESEJA BUSCAR:\n[1]JANEIRO\n[2]FEVEREIRO\n[3]MARÇO\n[4]ABRIL\n[5]MAIO\n[6]JUNHO\n");
				printf("[7]JULHO\n[8]AGOSTO\n[9]SETEMBRO\n[10]OUTUBRO\n[11]NOVEMBRO\n[12]DEZEMBRO\n[13]VOLTAR\n");

				int mes,valor,k,valoresSomados=0;
				scanf("%d", &mes);
				switch(mes){
				case 1:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&janeiro, valor);
					break;
				case 2:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&fevereiro, valor);
					break;
				case 3:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&marco, valor);
					break;
				case 4:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&abril, valor);
					break;
				case 5:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&maio, valor);
					break;
				case 6:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&junho, valor);
					break;
				case 7:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&julho, valor);
					break;
				case 8:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&agosto, valor);
					break;
				case 9:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&setembro, valor);;
					break;
				case 10:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&outubro, valor);
					break;
				case 11:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&novembro, valor);
					break;
				case 12:
					printf("DIGITE O CODIGO DA VENDA QUE DESEJA REMOVER:");
					scanf("%d",&valor);
					removerArvB(&dezembro, valor);
					break;
				case 13:
					break;
				default:
					printf("##DIGITE UMA OPÇÃO VÁLIDA##\n");
					system("pause");
					system("cls");
					break;
				}
				break;
			case 6:
        printf("\\----------------------Estatísticas----------------------/\n");
        k=1;
        //Impressao de todos os valores em crédito, débito e à vista
        while(k<=3){
          if(k==1) printf("-------Valores registrados em crédito:\n");
          if(k==2) printf("------Valores registrados em débito:\n");
          if(k==3) printf("-------Valores registrados à vista:\n");
          acumula_valores(janeiro,0,k,1);
          acumula_valores(fevereiro,0,k,2);
          acumula_valores(marco,0,k,3);
          acumula_valores(abril,0,k,4);
          acumula_valores(maio,0,k,5);
          acumula_valores(junho,0,k,6);
          acumula_valores(julho,0,k,7);
          acumula_valores(agosto,0,k,8);
          acumula_valores(setembro,0,k,9);
          acumula_valores(outubro,0,k,10);
          acumula_valores(novembro,0,k,11);
          acumula_valores(dezembro,0,k,12) ;
          acumula_valores(ano,0,k,0);
          k++;
        }
        //Impressao dos valores passados (quitados) e futuros (não quitados)
        k=1;
        while(k>=0){
        valoresSomados+=pegaTotais(janeiro,0,k);
        valoresSomados+=pegaTotais(fevereiro,0,k);
        valoresSomados+=pegaTotais(marco,0,k);
        valoresSomados+=pegaTotais(abril,0,k);
        valoresSomados+=pegaTotais(maio,0,k);
        valoresSomados+=pegaTotais(junho,0,k);
        valoresSomados+=pegaTotais(julho,0,k);
        valoresSomados+=pegaTotais(agosto,0,k);
        valoresSomados+=pegaTotais(setembro,0,k);
        valoresSomados+=pegaTotais(outubro,0,k);
        valoresSomados+=pegaTotais(novembro,0,k);
        valoresSomados+=pegaTotais(dezembro,0,k);
        valoresSomados+=pegaTotais(ano,0,k);
        if(k==1) printf("Valores quitados até o mês atual: %d\n",valoresSomados);
        else printf("Valores a serem quitados a partir deste mês: %d\n",valoresSomados);
        k--;valoresSomados=0;
        }
        printf("\\---------------------------- ------------------------------/\n");
				break;
			case 7:
				break;
			default:
			printf("##DIGITE UMA OPÇÃO VÁLIDA##\n");
			system("pause");
			system("cls");
			break;
		}

	}


}

int main(){
	setlocale(LC_ALL, "Portuguese");
	janeiro = criarArvB();
	fevereiro = criarArvB();
	marco = criarArvB();
	abril = criarArvB();
	maio = criarArvB();
	junho = criarArvB();
	julho = criarArvB();
	agosto = criarArvB();
	setembro = criarArvB();
	outubro = criarArvB();
	novembro = criarArvB();
	dezembro = criarArvB();
	ano = criarArvB();
	printf("INFORME A DATA ATUAL(dd/mm/aa):");
	scanf("%d/%d/%d",&data_atual_dia,&data_atual_mes,&data_atual_ano);

	printf("SISTEMA DE GESTÃO DE VENDAS COM SIMULAÇÃO\nALUNOS:JOSIAS BEN F. CAVALCANTE - 21753594\n       RAFAEL LÚCIO MARTINS - 21852709\n       VICTOR LUCAS B. DE BRITO - 21751502\n");
	menu();

	// imprimirArvB(teste);

	return 0;
}
