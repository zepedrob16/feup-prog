#pragma once

#include <iostream>
#include <string>
#include <map>
#include<algorithm>
#include <iomanip>
#include <time.h>
#include <Windows.h>


#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"


using namespace std;

class VendeMaisMais{
 private:
  string loja; // nome da loja
  string fichClientes, fichProdutos, fichTransacoes; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
  bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas
  map<int, int> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<int, int> transacaoIdx; // multima para "traduzir" o identificador do
				   // cliente nos indices das suas
				   // transacoes no vetor de
				   // transacoes

 public:
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  void listarClientesOrdemAlfa() const;
  void listarProdutos() const;
  void verBottom10();
  string getClientes();
  string getTrans();
  void criarCliente(string nome);
  void mostraInformacaoCliente(string nome);
  void adicionarTran(string nome);
  void editarCliente(string name);
  void removerCliente(string nome);
  void mostraTransacoes();
  void mostraTransacaodia();
  void mostraTransacaocliente();
  void mostraTransacaoEntreDatas();
  void publicidade();
  void publicidade_bottom10();
  void saveChanges();
};
