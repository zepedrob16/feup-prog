#include "Vende++.h"

void setcolor(unsigned int color){
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

vector<Produto>products_vector(ifstream &file)
{
	vector<Produto>pro;
	string b;
	getline(file, b);
	while (!file.eof())
	{
		getline(file, b);
		pro.push_back(Produto(b));
	}
	file.close();
	return pro;
}

vector<Transacao>transactions_vector(ifstream &file)
{
	vector<Transacao>trans;
	string b;
	getline(file, b);
	while (!file.eof())
	{
		getline(file, b);
		trans.push_back(Transacao(b));
	}
	file.close();
	return trans;
}

vector<Cliente>clients_vector(ifstream &file)
{
	vector<Cliente>c;
	string b;
	getline(file, b);
	while (!file.eof())
	{
		getline(file, b);
		c.push_back(Cliente(b));
	}
	file.close();
	return c;
}

VendeMaisMais::VendeMaisMais(string store, string fichClients, string fichProducts, string fichTransactions) {

	this->loja = store;
	this->fichClientes = fichClients;
	this->fichProdutos = fichProducts;
	this->fichTransacoes = fichTransactions;

	ifstream c(fichClients);
	ifstream p(fichProducts);
	ifstream t(fichTransactions);

	clientes = clients_vector(c);
	produtos = products_vector(p);
	transacoes = transactions_vector(t);

	c.close();
	p.close();
	t.close();


	this->transacoesAlterdas = false;
	this->clientesAlterados = false;
}

string VendeMaisMais::getClientes() {
	return fichClientes;
}

string VendeMaisMais::getTrans() {
	return fichTransacoes;
}

/*********************************
* Gestao de Clientes
********************************/

struct ClientNameComparator {
	bool operator() (Cliente c1, Cliente c2) {
		return c1.getNome() < c2.getNome();
	}
} clientNameComparator;

// lista os cleinets por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const {

	vector<Cliente>Alfa_V_Cli = clientes;

	sort(Alfa_V_Cli.begin(), Alfa_V_Cli.end(), clientNameComparator);

	cout << setw(2) << "ID" << setw(18) << "Nome" << setw(15) << "Data" << setw(20) << "Valor de Compras" << endl;
	cout << "------------------------------------------------------" << endl;

	for (unsigned int i = 0; i < Alfa_V_Cli.size(); i++)
	{
		cout << Alfa_V_Cli[i] << endl;
	}
}

struct ClientValueComparator {
	bool operator() (Cliente c1, Cliente c2) {
		return c1.getVolCompras() < c2.getVolCompras();
	}
} clientValueComparator;

void VendeMaisMais::verBottom10() {
	vector<Cliente>bottom10 = clientes;

	sort(bottom10.begin(), bottom10.end(), clientValueComparator);

	cout << setw(2) << "ID" << setw(18) << "Nome" << setw(15) << "Data" << setw(20) << "Valor de Compras" << endl;
	cout << "------------------------------------------------------" << endl;

	if (bottom10.size() > 10) {
		bottom10.erase(bottom10.begin() + 10, bottom10.end());
	}
	for (unsigned int i = 0; i < bottom10.size(); ++i) {
		cout << bottom10[i] << endl;
	}
}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome) {
	unsigned int i = 0;
	do {
		if (nome == clientes[i].getNome()) {
			cout << setw(2) << "ID" << setw(18) << "Nome" << setw(15) << "Data" << setw(20) << "Valor de Compras" << endl;
			cout << "------------------------------------------------------" << endl;
			cout << clientes[i] << endl;
			i = clientes.size();
		}
		else if (i + 1 == clientes.size()) {
			cout << "Esse cliente nao existe\n\n";
		}
		++i;
	} while (i < clientes.size());
}

void VendeMaisMais::criarCliente(string nome)
{
	Cliente novo;
	novo.setid((clientes[clientes.size() - 1].getId()) + 1);
	novo.setnome(nome);
#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;

	Data c;
	c.setDia(day);
	c.setMes(month);
	c.setAno(year);

	novo.setdate(c);
	novo.setvalue(0.0);

	clientes.push_back(novo);
	clientesAlterados = true;

	cout << "\nD"; Sleep(100); cout << "o"; Sleep(100); cout << "n"; Sleep(100); cout << "e"; Sleep(100); cout << "!\n";

	Sleep(100);

}

void VendeMaisMais::editarCliente(string nome) {
	unsigned int i = 0;
	string novonome;

	do {
		if (nome == clientes[i].getNome()) {
			cout << endl << "Novo nome: ";
			getline(cin, novonome);
			clientes[i].setnome(novonome);
			i = clientes.size();
			clientesAlterados = true;
		}
		else if (i + 1 == clientes.size()) { //It doesn't belong in the list
			cout << "Nao ha nenhum cliente com esse nome.";
		}
		++i;
	} while (i < clientes.size());
}

void VendeMaisMais::removerCliente(string nome) {
	unsigned int i = 0;
	string answer;

	do {
		if (clientes[i].getNome() == nome) {
			cout << "Tem a certeza de que quer apagar o cliente?(s/n): ";
			cin >> answer;
			if (answer == "s" || answer == "S" || answer == "Sim" || answer == "sim") { //The client wants to erase the client
				clientes.erase(clientes.begin() + i);
				cout << "\nCliente eliminado com sucesso.\n";
				i = clientes.size();
				clientesAlterados = true;
			}
			else {
				cout << "\nCancelamos a eliminacao.\n"; //The client picked no
				i = clientes.size();
			}
		}
		else if (i + 1 == clientes.size()) {
			cout << "Nao ha nenhum cliente com esse nome";
		}
		++i;
	} while (i < clientes.size());
}

/*********************************
* Gestao de Produtos
********************************/

// lisat os produto por ordem alfabetica crescente
struct ProductNameComparator {
	bool operator() (Produto p1, Produto p2) {
		return p1.getNome() < p2.getNome();
	}
} ProductNameComparator;

void VendeMaisMais::listarProdutos() const {

	vector<Produto>Alfa_V_Pro = produtos;

	sort(Alfa_V_Pro.begin(), Alfa_V_Pro.end(), ProductNameComparator);

	cout << setw(20) << "Nome do Produto" << setw(8) << "Custo" << endl;
	cout << "     -----------------------" << endl;

	for (unsigned int i = 0; i < produtos.size(); i++)
	{
		cout << Alfa_V_Pro[i] << endl;
	}
}

void VendeMaisMais::adicionarTran(string nome) {
	unsigned int clientid, addedtran = 0, i2;
	unsigned int i, iespecial = 0;  //iterator for the clients position
	vector<string> temporary;
#pragma warning(disable : 4996)
	time_t ti = time(0);
	struct tm * now = localtime(&ti);
	unsigned int year = 1900 + now->tm_year, month = 1 + now->tm_mon, day = now->tm_mday;
	string date, prodcomp, input;
	string prodnovos = "";

	cout << nome;

	do {
		if (nome == clientes[iespecial].getNome()) { //The client exists
			cout << "\nAqui estao os produtos disponiveis.\n\n";
			cout << setw(20) << "Nome do Produto" << setw(8) << "Custo" << endl;
			cout << "     -----------------------" << endl;
			for (i2 = 0; i2 < produtos.size(); i2++) {
				cout << produtos[i2] << endl;
			}
			cout << "\nQue produto quer comprar?(Escreva 'Feito' para acabar a transacao) \n\n";
			while (true) {
				i = 0;
				cin.clear();
				getline(cin, prodcomp);
				if (prodcomp == "Feito" || prodcomp == "feito") {
					setcolor(10); cout << "\nT"; Sleep(100); cout << "e"; Sleep(100); cout << "r"; Sleep(100); cout << "m"; Sleep(100); cout << "i"; Sleep(100); cout << "n"; Sleep(100); cout << "a"; Sleep(100); cout << "d"; Sleep(100); cout << "o"; Sleep(100); cout << "!"; setcolor(7);
					break;
				}
				do {
					if (prodcomp == produtos[i].getNome()) {
						temporary.push_back(prodcomp);
						addedtran += produtos[i].getCusto();
						setcolor(10); cout << "Adicionado" << endl; setcolor(7);
						break;
					}
					else if (i + 1 == produtos.size()) {
						setcolor(12); cerr << "\aEsse produto nao existe.\n"; setcolor(7);
						break;
					}
					++i;
				} while (i < produtos.size());
			}
			if (temporary.empty()) {
				setcolor(14); cout << "[Cuidado] Nenhuma transacao foi adicionada ao cliente.\n"; setcolor(7);
				break;
			}
			if (!(temporary.size() == 0)) {
				transacoesAlterdas = true;
			}

			Data t;
			t.setDia(day);
			t.setMes(month);
			t.setAno(year);

			Transacao novo;
			novo.setid(clientes[iespecial].getId());
			novo.setdate(t);
			novo.setvector_products(temporary);

			transacoes.push_back(novo);


			clientes[iespecial].setvalue(clientes[iespecial].getVolCompras() + addedtran);
			iespecial = clientes.size();
		}

		else if (iespecial + 1 == clientes.size()) {
			cout << "\nEste cliente ainda nao existe.\n";
		}
		++iespecial;
	} while (iespecial < clientes.size());

	Sleep(1500);

}

void VendeMaisMais::mostraTransacoes()
{
	cout << setw(4) << "ID" << setw(20) << "Data" << setw(40) << "Lista de Produtos" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		cout << transacoes[i] << endl;
	}
}

void VendeMaisMais::mostraTransacaodia()
{
	string b;
	cout << "Data (dd/MM/AAAA): ";
	getline(cin, b);
	Data c = Data(b);

		bool correct = false;

		for (unsigned int i = 0; i < transacoes.size(); i++)
		{
			if (transacoes[i].getData() == c)
				correct = true;
		}
		if (correct)
		{
			cout << setw(2) << "ID" << setw(15) << "Date" << setw(40) << "Lista de Podutos" << endl;
			cout << "---------------------------------------------------------------------------------" << endl;
			for (unsigned int i = 0; i < transacoes.size(); i++)
			{
				if (transacoes[i].getData() == c)
				{
					cout << transacoes[i] << endl;
				}
			}
		}
		else
			cout << "Nenhuma Transacao foi efetuada entre essas datas!" << endl;
}

void VendeMaisMais::mostraTransacaocliente()
{
	string nome;
	unsigned int id;
	cout << "Qual o nome do Cliente ? ";
	getline(cin, nome);
	bool correct = false;

	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (nome == clientes[i].getNome())
		{
			correct = true;
			id = clientes[i].getId();
		}
	}

	if (correct)
	{
		correct = false;
		for (unsigned int i = 0; i < transacoes.size(); i++)
		{
			if (transacoes[i].getIdCliente() == id)
				correct = true;
		}
		if (correct)
		{
			cout << setw(2) << "ID" << setw(15) << "Date" << setw(40) << "Lista de Podutos" << endl;
			cout << "---------------------------------------------------------------------------------" << endl;
			for (unsigned int i = 0; i < transacoes.size(); i++)
			{
				if (id == transacoes[i].getIdCliente())
				{
					cout << transacoes[i] << endl;
				}
			}
		}
		else
			cout << "No transactions made by this Cliente!" << endl;
	}
	else
		cout << "Incorrect ID! " << endl;
}

void VendeMaisMais::mostraTransacaoEntreDatas()
{
	string d1, d2;
	cout << "Primeira Data (DD/MM/AAAA) : ";
	getline(cin, d1);
	Data D1 = Data(d1);
	cout << "Segunda Data (DD/MM/AAAA) : ";
	getline(cin, d2);
	Data D2 = Data(d2);


		bool correct = false;

		for (unsigned int i = 0; i < transacoes.size(); i++)
		{
			if (transacoes[i].getData() <= D2 && D1 <= transacoes[i].getData())
				correct = true;
		}
		if (correct)
		{
			cout << setw(2) << "ID" << setw(15) << "Date" << setw(40) << "Lista de Podutos" << endl;
			cout << "---------------------------------------------------------------------------------" << endl;

			for (unsigned int i = 0; i < transacoes.size(); i++)
			{
				if (transacoes[i].getData() <= D2 && D1 <= transacoes[i].getData())
				{
					cout << transacoes[i] << endl;
				}
			}
		}
		else
			cout << "Nenhuma Transacao foi efetuada entre essas datas!" << endl;
}

void VendeMaisMais::publicidade()
{
	int id_alvo = -1;
	string nome_alvo;
	cout << "Qual o nome do Cliente: ";
	getline(cin, nome_alvo);

	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (nome_alvo == clientes[i].getNome())
			id_alvo = clientes[i].getId(); // encontra id do cliente
	}
	if (id_alvo == -1)
		return;                      //para se cliente nao existir

	vector<int>all_clientes;

	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		if (find(all_clientes.begin(), all_clientes.end(), transacoes[i].getIdCliente()) == all_clientes.end()) //verifica se o id da transaçao na posiçao i ja existe no vetor all_clientes
		{
			all_clientes.push_back(transacoes[i].getIdCliente()); //adiciona se nao existir
		}
	}

	for (unsigned int i = 0; i < all_clientes.size(); i++)//adiciona valores ao map clienteIdx
	{
		clienteIdx.insert(make_pair(all_clientes.at(i), i));
	}

	for (unsigned int i = 0; i < produtos.size(); i++) //adiciona valores ao map produtoIdx
	{
		produtoIdx.insert(make_pair(produtos.at(i).getNome(), i));
	}


	vector<vector<bool>>matriz(all_clientes.size(), vector<bool>(produtos.size(), false)); //Cria a matriz

	for (unsigned int i = 0; i < transacoes.size(); i++) // preenche a matriz de true nos produtos adquiridos por cada cliente
	{
		for (unsigned int j = 0; j < transacoes[i].getvector().size(); j++)
		{
			matriz[clienteIdx[transacoes[i].getIdCliente()]][produtoIdx[transacoes[i].getvector().at(j)]] = true;
		}
	}

	//display matriz
	/*for (int i = 0; i < matriz.size(); i++)
	{
	for (int a = 0; a < matriz[i].size(); a++)
	{
	cout << matriz[i][a];
	}
	cout << endl;
	}*/

	vector<int>num_t(all_clientes.size(), 0);
	vector<int>num_nt(all_clientes.size(), 0);

	for (unsigned int i = 0; i < all_clientes.size(); i++)
	{
		for (unsigned int j = 0; j < produtos.size(); j++)
		{
			if (matriz[clienteIdx[id_alvo]][j] && matriz[i][j])
				num_t[i] = num_t[i] + 1;
			else if (!matriz[clienteIdx[id_alvo]][j] && matriz[i][j])
				num_nt[i] = num_nt[i] + 1;
		}
	}

	/*//mostra num_t
	for (int i = 0; i < num_t.size(); i++)
	{
	cout << num_t[i] << "---------" << num_nt[i] << endl;
	}*/


	int n_p = produtos.size();
	vector<int>pos_semelhante; //guarda posicao do cliente semelhante;
	bool verificado = false;

	for (unsigned int j = 0; j < produtos.size(); j++)
	{
		for (unsigned int i = 0; i < all_clientes.size(); i++)
		{
			if (num_t[i] == n_p && num_nt[i] != 0)
			{
				pos_semelhante.push_back(i);
				verificado = true;
			}
		}

		if (!verificado)
			n_p--;
		else
			break;
	}

	vector<int> coluna(produtos.size(), 0); //vetor para ver quantas trues ha numa coluna

	for (unsigned int i = 0; i < pos_semelhante.size(); i++)
	{
		for (unsigned int j = 0; j < produtos.size(); j++)
		{
			if (!matriz[clienteIdx[id_alvo]][j] && matriz[pos_semelhante[i]][j])
				coluna[j] = coluna[j] + 1;
		}
	}

	int a; //Produto mais comprado pelo cliente semelhante e nao comprado pelo cliente alvo
	int b; //Posicao no vetor dos produtos


	if (pos_semelhante.size() == 0) {
		cout << "Nao ha produto sugerido para esse cliente."<<endl;
	}
	else {
		for (unsigned int i = 0; i < coluna.size(); i++)
		{
			if ((i + 1) == coluna.size() && coluna[i] > coluna[i - 1]) {
				a = coluna[i];
				b = i;
			}
			else if ((i + 1) == coluna.size()) {
				break;
			}
			else if (coluna[i] > coluna[i + 1]) {
				a = coluna[i];
				b = i;
			}
		}
		cout << "O produto sugerido ao cliente " << nome_alvo << " e " << produtos[b].getNome() << endl;
	}
}

void VendeMaisMais::publicidade_bottom10()
{
	vector<Cliente>bottom10 = clientes;
	vector<int>bottom10_ids;
	vector<Transacao>bottom10_trans;
	vector<Cliente>interessantes;
	vector<int> interessantes_ids;
	vector<Transacao>interessantes_trans;

	sort(bottom10.begin(), bottom10.end(), clientValueComparator);

	//coloca preenche o vetor de interessantes de clientes interessantes
	if (bottom10.size() > 10)
	{
	for (unsigned int i = 10; i < bottom10.size();i++)
		interessantes.push_back(bottom10[i]);             

		bottom10.erase(bottom10.begin() + 10, bottom10.end());
	}

	//preenche o bottom10_ids
	for (unsigned int i = 0; i < bottom10.size(); i++)
	{
		bottom10_ids.push_back(bottom10[i].getId());
	}

	//guarda apenas as transacoes dos bottom10
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		for (unsigned int j = 0; j < bottom10_ids.size();j++)
		{
			if (transacoes[i].getIdCliente() == bottom10_ids[j])
				bottom10_trans.push_back(transacoes[i]);				
		}
	}

	//preenche o interessantes_ids
	for (unsigned int i = 0; i < interessantes.size(); i++)
	{
		interessantes_ids.push_back(interessantes[i].getId());
	}

	//guarda apenas as transacoes dos clientes interessantes
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		for (unsigned int j = 0; j < interessantes_ids.size(); j++)
		{
			if (transacoes[i].getIdCliente() == interessantes_ids[j])
				interessantes_trans.push_back(transacoes[i]);
		}
	}

	//adiciona valores ao map clienteIdx
	for (unsigned int i = 0; i < bottom10.size(); i++)
	{
		clienteIdx[bottom10_ids.at(i)] = i;
	}

	//adiciona valores ao map produtoIdx
	for (unsigned int i = 0; i < produtos.size(); i++) 
	{
		produtoIdx.insert(make_pair(produtos.at(i).getNome(), i));
	}

	vector<vector<bool>>matriz_bottom10(bottom10.size(), vector<bool>(produtos.size(), false)); //Cria a matriz

	// preenche a matriz de true nos produtos adquiridos por cada cliente
	for (unsigned int i = 0; i < bottom10_trans.size(); i++) 
	{
		for (unsigned int j = 0; j < bottom10_trans[i].getvector().size(); j++)
		{
			matriz_bottom10[clienteIdx[bottom10_trans[i].getIdCliente()]][produtoIdx[bottom10_trans[i].getvector().at(j)]] = true;
		}
	}

	vector<bool>pro_comuns(produtos.size(),false); //posicao dos produtos comuns aos bottom10

	//coloca a true a posicao do vetor do produtos comuns correspondente ao produto comum
	for (unsigned int i = 0; i < produtos.size(); i++)
	{
		for (unsigned int j = 0; j < bottom10.size(); j++)
		{
			if (matriz_bottom10[clienteIdx[j]][i])
				pro_comuns[i] = true; 
			else
			{
				pro_comuns[i] = false;
				break;
			}
		}
	}

	//Cria map igual a clienteIdx
	map<int, int>cliente_interessanteIdx;

	for (unsigned int i = 0; i < interessantes.size(); i++)
	{
		cliente_interessanteIdx[interessantes_ids.at(i)] = i;
	}

	vector<vector<bool>>matriz_interessantes(interessantes.size(), vector<bool>(produtos.size(), false)); //Cria a matriz


	for (unsigned int i = 0; i < interessantes_trans.size(); i++) // preenche a matriz de true nos produtos adquiridos por cada cliente
	{
		for (unsigned int j = 0; j < interessantes_trans[i].getvector().size(); j++)
		{
			matriz_interessantes[cliente_interessanteIdx[interessantes_trans[i].getIdCliente()]][produtoIdx[interessantes_trans[i].getvector().at(j)]] = true;
		}
	}

	vector<int>v;//vetor temporario que vai guardar os ids dos clientes interessantes "semelhantes"

	for (unsigned int i = 0; i < pro_comuns.size(); i++)
	{
		if (pro_comuns[i])
		{
			for (unsigned int j = 0; j < interessantes_ids.size(); j++)
			{
				if (matriz_interessantes[cliente_interessanteIdx[interessantes_ids[j]]][i])
					v.push_back(interessantes_ids[j]);		
			}
		}
	}
	interessantes_ids = v;


	vector<vector<bool>>matriz_final;//Cria a matriz
	vector<Transacao>interessantes_final_trans;//vetor que contem transacoes dos clientes interessantes "semelhantes"

	matriz_final.push_back(pro_comuns);

	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		for (unsigned int j = 0; j < interessantes_ids.size(); j++)
		{
			if (transacoes[i].getIdCliente() == interessantes_ids[j])
				interessantes_final_trans.push_back(transacoes[i]);
		}
	}

	//preenche a matriz de true nos produtos adquiridos por cada cliente
	for (unsigned int i = 0; i < interessantes_final_trans.size(); i++)
	{
		for (unsigned int j = 0; j < interessantes_final_trans[i].getvector().size(); j++)
		{
			matriz_final[clienteIdx[interessantes_final_trans[i].getIdCliente()]][produtoIdx[interessantes_final_trans[i].getvector().at(j)]] = true;
		}
	}

	vector<int> coluna(produtos.size(), 0); //vetor para ver quantas trues ha numa coluna

	for (unsigned int i = 0; i < interessantes_ids.size(); i++)
	{
		for (unsigned int j = 0; j < produtos.size(); j++)
		{
			if (!pro_comuns[j] && matriz_final[i][j])
				coluna[j] = coluna[j] + 1;
		}
	}

	int a; //Produto mais comprado pelo cliente semelhante e nao comprado pelo cliente alvo
	int b; //Posicao no vetor dos produtos


	if (interessantes_ids.size() == 0) {
		cout << "Nao ha produto sugerido "<<endl;
	}
	else {
		for (unsigned int i = 0; i < coluna.size(); i++)
		{
			if ((i + 1) == coluna.size() && coluna[i] > coluna[i - 1]) {
				a = coluna[i];
				b = i;
			}
			else if ((i + 1) == coluna.size()) {
				break;
			}
			else if (coluna[i] > coluna[i + 1]) {
				a = coluna[i];
				b = i;
			}
		}
		cout << "O produto sugerido ao cliente  e " << produtos[b].getNome() << endl;
	}
}


/*********************************
* Preservar Informacao
********************************/

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() {
	string cli, resposta, tra, itemstr;
	ofstream fich;
	vector<string>temp;
	if (clientesAlterados == true) {
		cout << "Deseja guardar as alteracoes feitas aos clientes?: ";
		getline(cin, resposta);
		if (resposta == "sim" || resposta == "Sim" || resposta == "SIm" || resposta == "SIM" || resposta == "SiM" || resposta == "siM" || resposta == "sIM" || resposta == "sIm" || resposta == "S" || resposta == "s") {
			cli = getClientes();
			fich.open(cli);
			fich << clientes.size();
			for (int i = 0; i < clientes.size(); i++) {
				fich << endl << clientes[i].getId() << " ; " << clientes[i].getNome() << " ; " << clientes[i].getDate() << " ; " << clientes[i].getVolCompras();
			}
			setcolor(10); cout << "Ficheiros guardados!\n"; setcolor(7);
		}
		else {
			setcolor(14); cout << "\nNenhuma alteracao no ficheiro de Clientes foi guardada" << endl; setcolor(7);
		}
	}

	if (clientesAlterados == false) {
		cout << "Nao houve alteracoes feitas ao ficheiro dos clientes.\n";
	}
	

	if (transacoesAlterdas == true) {
		cout << "Deseja guardar as alteracoes feitas as transacoes?: ";
		getline(cin, resposta);
		if (resposta == "sim" || resposta == "Sim" || resposta == "SIm" || resposta == "SIM" || resposta == "SiM" || resposta == "siM" || resposta == "sIM" || resposta == "sIm" || resposta == "S" || resposta == "s") {
			tra = getTrans();
			fich.open(tra);
			fich << transacoes.size();
			for (int i = 0; i < transacoes.size(); i++)
			{
				itemstr = "";
				temp = transacoes[i].getvector();
				fich << endl << transacoes[i].getIdCliente() << " ; " << transacoes[i].getData() << " ; ";
				for (int j = 0; j < temp.size(); j++)
				{
					itemstr.append(temp[j]);
					itemstr.append(", ");
				}
				itemstr.pop_back();
				itemstr.pop_back();
				fich << itemstr;
			}
			setcolor(10); cout << "Ficheiros guardados!\n\n"; setcolor(3);
			cout << TAB_BIG << "Trabalho desenvolvido por Vicente Espinha e Jose Pedro Borges\n\n"; setcolor(7);
		}
		else{
			setcolor(14); cout << "Nenhuma alteracao no ficheiro de transacoes foi guardada\n" << endl; setcolor(7);
			setcolor(3); cout << TAB_BIG << "Trabalho desenvolvido por Vicente Espinha e Jose Pedro Borges\n\n"; setcolor(7);
		}
	}
	if (transacoesAlterdas == false) {
		cout << "Nao houve alteracoes feitas ao ficheiro das transacoes.\n\n";
		setcolor(3); cout << TAB_BIG << "Trabalho desenvolvido por Vicente Espinha e Jose Pedro Borges\n\n"; setcolor(7);
	}
}