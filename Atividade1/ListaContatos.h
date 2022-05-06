typedef struct{
	char nome[100];
	char sobrenome[100];
	char email[100];
	char telefone[100];
	int diaNascimento;
	int mesNascimento;
	int anoNascimento;
	char profissao[100];
}Contato;

typedef struct Nodo{
    Contato contato;
    struct Nodo* proximo;
}Nodo;

typedef struct{
    Nodo* inicio;
    Nodo* final;
}ListaEncadeadaContatos;

ListaEncadeadaContatos* CriarListaContatos();
int InserirContato(ListaEncadeadaContatos* lista, Contato contato, int InicioFinal);
void DestruirListaEncadeadaContatos(ListaEncadeadaContatos** lista);
void ImprimirContato(Contato* contato);
void ImprimirLista(ListaEncadeadaContatos* lista, int OpcaoConsulta, char* EmailConsulta, int* MesConsulta);
void DestruirListaEncadeadaContatos(ListaEncadeadaContatos** lista);
int RemoverContatoPorEmail(ListaEncadeadaContatos* lista, char EmailRemocao[]);
