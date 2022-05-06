#include "ListaContatos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MenuPrincipal();
void MenuInserirContato(ListaEncadeadaContatos* Lista);
void MenuImprimirLista(ListaEncadeadaContatos* Lista, int OpcaoConsulta);
void LimparTela();
void CarregarEmailConsulta(char* EmailConsulta, int Operacao);
void CarregarMesConsulta(int* MesConsulta);
void RemoverContato(Lista);

int main()
{
    int Menu;
    ListaEncadeadaContatos* Lista = CriarListaContatos();

    do{
        LimparTela();
        MenuPrincipal();
        Menu = 0;
        scanf("%d", &Menu);

        switch (Menu)
        {
            /* SAI DO MENU */
                case 9:
                break;

            /* INSERIR CONTATO */
                case 1:
                    MenuInserirContato(Lista);
                    break;

            /* CONSULTA PELO EMAIL */
                case 2:
                    MenuImprimirLista(Lista, 1);
                    break;

            /* CONSULTA PELO MES DE ANIVERSARIO */
                case 3:
                    MenuImprimirLista(Lista, 2);
                    break;

            /* CONSULTA PELO MES DE ANIVERSARIO */
                case 4:
                    RemoverContato(Lista);
                    break;

            /* IMPRESSAO GERAL */
                case 5:
                    MenuImprimirLista(Lista, 0);
                    break;

            /* OPCAO INVALIDA */
                default:
                    printf("Opcao Invalida\n");
                    fflush(stdin);
                    break;
        }
    }while (Menu != 9);

    DestruirListaEncadeadaContatos(&Lista);
    return 0;
}


void MenuPrincipal(){
    printf("X-- Atividade 1 ---------------------------------X\n");
    printf("| 1 - Inserir contato                            |\n");
    printf("| 2 - Consultar contato pelo e-Mail              |\n");
    printf("| 3 - Consultar contatos pelo mes de aniversario |\n");
    printf("| 4 - Eliminar contato pelo e-mail               |\n");
    printf("| 5 - Impressao geral                            |\n");
    printf("|                                                |\n");
    printf("| 9 - Sair                                       |\n");
    printf("X------------------------------------------------X\n");
}

void MenuInserirContato(ListaEncadeadaContatos* Lista){
    Contato NovoContato;
    int InsercaoLista = 9;

    do{
        LimparTela();
        printf("X------------------------------X\n");
        printf("| Posicao de Insercao na Lista |\n");
        printf("X-----------X------------------X\n");
        printf("|1 - Inicio |\n");
        printf("|2 - Final  |\n");
        printf("X-----------X\n");
        scanf("%d", &InsercaoLista);
        fflush(stdin);

    }while(InsercaoLista != 1 && InsercaoLista != 2);

    LimparTela();

    printf("X------------------X\n");
    printf("| Dados do Contato |\n");
    printf("X------------------X\n");

    fflush(stdin);

    printf("Nome......: ");
    fgets(NovoContato.nome, 100, stdin);
    fflush(stdin);

    printf("Sobrenome.: ");
    fgets(NovoContato.sobrenome, 100, stdin);
    fflush(stdin);

    printf("E-mail....: ");
    fgets(NovoContato.email, 100, stdin);
    fflush(stdin);

    printf("Telefone..: ");
    fgets(NovoContato.telefone, 100, stdin);
    fflush(stdin);

    printf("Profissao.: ");
    fgets(NovoContato.profissao, 100, stdin);
    fflush(stdin);

    printf("\nData de Nascimento\n");
    fflush(stdin);

    printf("Dia: ");
    char DiaDtNascimento[3];
    fgets(DiaDtNascimento, 3, stdin);
    NovoContato.diaNascimento = atoi(DiaDtNascimento);
    fflush(stdin);

    printf("Mes: ");
    char MesDtNascimento[3];
    fgets(MesDtNascimento, 3, stdin);
    fflush(stdin);
    NovoContato.mesNascimento = atoi(MesDtNascimento);

    printf("Ano: ");
    char AnoDtNascimento[5];
    fgets(AnoDtNascimento, 5, stdin);
    fflush(stdin);
    NovoContato.anoNascimento = atoi(AnoDtNascimento);

    InserirContato(Lista, NovoContato, InsercaoLista);

    printf("\nPressione ENTER para continuar...\n");
    getch();
    fflush(stdin);
}

void MenuImprimirLista(ListaEncadeadaContatos* Lista, int OpcaoConsulta){
    LimparTela();

    /*
        OPCAOCONSULTA
        0 - IMPRESSAO GERAL
        1 - CONSULTA PELO EMAIL
        2 - CONSULTA PELO MES
    */

    char* EmailConsulta = (char*)malloc(100);
    int* MesConsulta = (int*)malloc(3);

    /* CARREGA O EMAIL PARA CONSULTA */
    if (OpcaoConsulta == 1){
        CarregarEmailConsulta(EmailConsulta, 1);
    }

    /* CARREGA O MES PARA CONSULTA */
    if (OpcaoConsulta == 2){
         CarregarMesConsulta(MesConsulta);
    }

    ImprimirLista(Lista, OpcaoConsulta, EmailConsulta, MesConsulta);

    free(EmailConsulta);
    free(MesConsulta);

    printf("\nPressione ENTER para continuar...\n");
    getch();
    fflush(stdin);
}

void RemoverContato(Lista){
        char* EmailConsulta = (char*)malloc(100);

        CarregarEmailConsulta(EmailConsulta, 2);

        RemoverContatoPorEmail(Lista, EmailConsulta);

        printf("Pressione ENTER para continuar...\n");
        getch();
}

void CarregarEmailConsulta(char* EmailConsulta, int Operacao){
    LimparTela();

    /*
        Operacao
        1 - CONSULTA
        2 - REMOCAO
        (SÓ MUDA O CABEÇALHO DO MENU)
    */

    if (Operacao == 1){
        printf("X----------------------X\n");
        printf("| E-mail para consulta |\n");
        printf("X----------------------X\n");
    } else {
        printf("X---------------------X\n");
        printf("| E-mail para remocao |\n");
        printf("X---------------------X\n");
    }

    printf("E-mail: ");

    fflush(stdin);
    fgets(EmailConsulta, 100, stdin);
}

void CarregarMesConsulta(int* MesConsulta){
    LimparTela();

    printf("X-------------------X\n");
    printf("| Mes para consulta |\n");
    printf("X-------------------X\n\n");
    printf("Mes: ");

    fflush(stdin);
    char AuxMesDtNascimento[3];
    fgets(AuxMesDtNascimento, 3, stdin);


    *MesConsulta = atoi(AuxMesDtNascimento);

}

void LimparTela(){
    #ifdef _WIN32
    system("cls");

    #elif __linux__
    system("clear");

    #endif
}
