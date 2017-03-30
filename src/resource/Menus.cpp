#include "Menus.h"

void ok()
{
	string ok;
	bool acabar = false;
	cout << "Digite 'ok' para continuar.\n\n";
	while (acabar == false) {
		getline(cin, ok);
		if (ok != "ok" && ok != "Ok" && ok != "oK" && ok != "OK") {
			cout << "Escolha invalida\n";
		}
		else if (ok == "ok" || ok == "Ok" || ok == "oK" || ok == "OK") {
			acabar = true;
		}
	}
}

bool infoInicial(string & loja, string & fichClients, string & fichProducts, string & fichTransactions)
{
	cout << "Clients file : ";
	getline(cin, fichClients);

	cout << "Products file : ";
	getline(cin, fichProducts);

	cout << "Transactions file : ";
	getline(cin, fichTransactions);

	fstream c(fichClients);
	fstream p(fichProducts);
	fstream t(fichTransactions);

	if (c.fail() || p.fail() || t.fail())
	{
		c.close();
		p.close();
		t.close();
		return false;
	}
	else
	{
		c.close();
		p.close();
		t.close();
		return true;
	}
}

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int menuGestaoClientes(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Gestao Clientes" << endl;
  cout << endl;
  cout << TAB << "1 - Listar clientes" << endl;
  cout << TAB << "2 - Ver informacao cliente" << endl;
  cout << TAB << "3 - Criar Cliente" << endl;
  cout << TAB << "4 - Editar cliente" << endl;
  cout << TAB << "5 - Remover cliente" << endl;
  cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
 
  opcao = leUnsignedShortInt(1, 5);

  if(opcao == 6)
    return 0;

  return opcao;
}

void opcoesGestaoClientes(VendeMaisMais & supermercado) {
	unsigned int opcao;
	string nome;

	while ((opcao = menuGestaoClientes()))
		switch (opcao) {
		case 1: supermercado.listarClientesOrdemAlfa();
			ok();
			break;
		case 2: cout << "Qual o nome do cliente: ";
			getline(cin, nome);
			supermercado.mostraInformacaoCliente(nome);
			ok();
			break;
		case 3:cout << "Qual o nome do cliente: ";
			getline(cin, nome);
			supermercado.criarCliente(nome);
			break;
		case 4:cout << "Qual o nome do cliente: ";
			cin.ignore();
			getline(cin, nome);
			supermercado.editarCliente(nome);
			break;
		case 5:cout << "Qual o nome do cliente: ";
			cin.ignore();
			getline(cin, nome);
			supermercado.removerCliente(nome);
			break;
		}
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuGestaoTransacoes(){
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Gestao Transacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Listar transacoes" << endl;
	cout << TAB << "2 - Listar transacoes de um cliente" << endl;
	cout << TAB << "3 - Listar transacoes de um dia" << endl;
	cout << TAB << "4 - Listar transacoes entre dias" << endl;
	cout << TAB << "5 - Adicionar transacoes a um cliente" << endl;
	cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leUnsignedShortInt(1, 6);

	if (opcao == 6)
		return 0;

	return opcao;
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
  unsigned int opcao;
  string nome;

  while((opcao = menuGestaoTransacoes()))
    switch (opcao){
	case 1:supermercado.mostraTransacoes();
		ok();
      break;
	case 2:supermercado.mostraTransacaocliente();
		ok();
      break;
	case 3:supermercado.mostraTransacaodia();
		ok();
      break;
	case 4:supermercado.mostraTransacaoEntreDatas();
		ok();
      break;
	case 5: cout << "Qual o nome do cliente ?";
		getline(cin, nome);
		supermercado.adicionarTran(nome);
    }
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuRecomendacao(){
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Recomendacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Os 10 piores clientes (Bottom 10)" << endl;
	cout << TAB << "2 - Recomendacao a um cliente" << endl;
	cout << TAB << "3 - Recomendacao Bottom10"<<endl,
	cout << TAB << "4 - Voltar ao menu inicial" << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leUnsignedShortInt(1, 4);

	if (opcao == 4)
		return 0;

	return opcao;
}

void opcoesRecomendacao(VendeMaisMais & supermercado){
	unsigned int opcao;

  while ((opcao = menuRecomendacao()))
	  switch (opcao) {
	  case 1: supermercado.verBottom10();
		  ok();
		  break;
	  case 2: supermercado.publicidade();
		  ok();
		  break;
	  case 3:supermercado.publicidade_bottom10();
		  ok();
		  break;
	  }
}

/******************************************
 * Menu Inicial
 ******************************************/
unsigned short int menuInicial(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Inicial" << endl;
  cout << endl;
  cout << TAB << "1 - Gestao de clientes" << endl;
  cout << TAB << "2 - Lista produto disponiveis" << endl;
  cout << TAB << "3 - Gestao de transacoes" << endl;
  cout << TAB << "4 - Recomendacoes" << endl;
  cout << TAB << "5 - Sair do programa" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(1, 5);

  if(opcao == 5)
    return 0;

  return opcao;
}

void opcoesIniciais(VendeMaisMais & supermercado){
	unsigned int opcao;


  while((opcao = menuInicial()))
    switch (opcao){
    case 1: opcoesGestaoClientes(supermercado);
      break;
    case 2: supermercado.listarProdutos();
		ok();
      break;
    case 3: opcoesGestaoTransacoes(supermercado);
      break;
    case 4: opcoesRecomendacao(supermercado);
      break;
    }

  supermercado.saveChanges();
}
