#include "ListaContatos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListaEncadeadaContatos* CriarListaContatos(){
    ListaEncadeadaContatos* NovaLista;
    NovaLista = (ListaEncadeadaContatos*) malloc(sizeof(ListaEncadeadaContatos));
    if(NovaLista!= NULL)
    {
        NovaLista->inicio = NULL;
        NovaLista->final  = NULL;
    }
    return NovaLista;
}

int InserirContato(ListaEncadeadaContatos* lista, Contato contato, int InicioFinal){
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->contato = contato;

    /* INICIO */
    if (InicioFinal == 1){
        novoNodo->proximo = lista->inicio;

        /*
            UNICA MANEIRA DE MUDAR O NODO FINAL NA INSERÇÃO INICIAL É SE
            ESTE SER O PRIMEIRO A SER INSERIDO, CASO CONTRARIO, O NODO
            FINAL SEMPRE SERÁ O MESMO, JÁ QUE ESTE NÃO MUDA NESTA CONDIÇÃO
        */
        if(lista->inicio == NULL){
            lista->final = novoNodo;
        }

        lista->inicio = novoNodo;

        printf("X------------------X\n");
        printf("| Contato inserido |\n");
        printf("X------------------X\n");

        return 1;
    } else {
    /* FINAL */
        /*
            QUANDO É O PRIMEIRO, INSERE PELO MÉTODO DE INICIO, JÁ QUE O RESULTADO SERÁ O MESMO
        */
        if (lista->inicio == NULL){
            InserirContato(lista, contato, 1);
        } else {
            Nodo* UltimoNodoAtual = lista->final;
            UltimoNodoAtual->proximo = novoNodo;
            lista->final = novoNodo;
            novoNodo->proximo = NULL;
        }
    }
}

void ImprimirContato(Contato* contato){
    printf("X---------------------X\n");
    printf("| Informacoes Contato |\n");
    printf("X---------------------X\n");

    printf("Nome..........: %s", contato->nome);
    printf("Sobrenome.....: %s", contato->sobrenome);
    printf("E-mail........: %s", contato->email);
    printf("Telefone......: %s", contato->telefone);
    printf("Profissao.....: %s", contato->profissao);
    printf("Dt. Nascimento: %d/%d/%d\n", contato->diaNascimento, contato->mesNascimento, contato->anoNascimento);
}

void ImprimirLista(ListaEncadeadaContatos* lista, int OpcaoConsulta, char* EmailConsulta, int* MesConsulta){
    /*
        OPCAOCONSULTA
        0 - IMPRESSAO GERAL
        1 - CONSULTA PELO EMAIL
        2 - CONSULTA PELO MES

    */
    if (lista != NULL){
        if (lista->inicio == NULL){
            printf("X----------------------------X\n");
            printf("| Nenhum contato cadastrado! |\n");
            printf("X----------------------------X\n");
        } else{
            Nodo* NodeLoop = lista->inicio;
            while(NodeLoop != NULL){
                Contato ContatoTestaConsulta = NodeLoop->contato;

                switch (OpcaoConsulta)
                {
                    case 0: /* IMPRESSAO GERAL */
                        ImprimirContato(&NodeLoop->contato);

                    case 1: /* CONSULTA EMAIL */
                        /* Contato TesteContato = NodeLoop->contato; */
                        if(strcmp(EmailConsulta, ContatoTestaConsulta.email) == 0){
                            LimparTela();
                            ImprimirContato(&NodeLoop->contato);
                            break;
                        }

                    case 2: /* CONSULTA MES */
                        if(*MesConsulta == ContatoTestaConsulta.mesNascimento){
                            ImprimirContato(&NodeLoop->contato);
                        }
                        break;

                }
                NodeLoop = NodeLoop->proximo;
            }
        }
    }
}

void DestruirListaEncadeadaContatos(ListaEncadeadaContatos** lista){

    if(*lista != NULL)
    {
        while((*lista)->inicio != NULL)
        {
            Nodo* nodo = (*lista)->inicio;
            (*lista)->inicio = nodo->proximo;
            free(nodo);
        }
        (*lista)->inicio = NULL;
        free(*lista);
    }
    *lista = NULL;
}

int RemoverContatoPorEmail(ListaEncadeadaContatos* lista, char EmailRemocao[]){
    if (lista != NULL){
        if (lista->inicio == NULL){
            printf("X----------------------------X\n");
            printf("| Nenhum contato cadastrado! |\n");
            printf("X----------------------------X\n");
        } else{
            Nodo* NodeLoop     = lista->inicio;
            Nodo* NodoAnterior = lista->inicio;

            while(NodeLoop != NULL){
                Contato ContatoTestaConsulta = NodeLoop->contato;
                if(strcmp(EmailRemocao, ContatoTestaConsulta.email) == 0){
                    /*
                        ANTES DE REMOVER, FAZ ALGUMAS VERIFICAÇÕES, COMO, SE O NODO ELIMINADO É O PRIMEIRO OU ULTIMO,
                        JA QUE TEM QUE ATUALIZAR AS PROPRIEDADES NA LISTA
                    */

                    /*
                        QUANDO ELIMINA O PRIMEIRO, SE É O UNICO DA LISTA, RESETA AMBAS AS PROPRIEDADES INICIAL E FINAL,
                        CASO CONTRARIO, SETA O SEGUNDO COMO PRIMEIRO.
                    */
                    if(lista->inicio == NodeLoop){
                        if(NodeLoop->proximo == NULL){  /* UNICO */
                            free(NodeLoop);
                            lista->inicio = NULL;
                            lista->final = NULL;
                        }else{
                            lista->inicio = NodeLoop->proximo;
                            free(NodeLoop);
                        }
                    }

                    /*
                        QUANDO ELIMINA O NODO FINAL, MUDA A PROPRIEDADE 'FINAL' NA LISTA PARA APONTAR AO NODO
                        ANTERIOR AO QUE ESTÁ SENDO ELIMINADO, (NodoAnterior) E FAZ COM QUE ESTE NÃO APONTE
                        A UM PROXIMO;
                    */
                    if (lista->final == NodeLoop){
                        lista->final = NodoAnterior;

                        NodoAnterior->proximo = NULL;

                        free(NodeLoop);

                        break;
                    }
                    /*
                        QUANDO REMOVER UM NODO DO MEIO, O ANTERIOR VAI APONTAR AO SEGUINTE AO NODO REMOVIDO, PREVININDO
                        QUE QUEBRE A LISTA.
                    */
                    /*
                        SE NÃO É O INICIAL NEM O FINAL, LÓGICAMENTE É UM DO MEIO
                    */
                    NodoAnterior->proximo = NodeLoop->proximo;
                    free(NodeLoop);


                }
                /*
                    SALVA UMA COPIA DO NODO, QUE VAI SER O ANTERIOR AO ATUAL DO LAÇO, UTILIZA QUANDO A REMOÇÃO É
                    NO MEIO OU FINAL.
                */
                NodoAnterior = NodeLoop;
                NodeLoop = NodeLoop->proximo;
            }
        }
    }

    return 0;
}

