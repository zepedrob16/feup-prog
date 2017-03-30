#include "Transacao.h"

Transacao::Transacao(string line){ // le uma transacao na forma de  idcliente ; data ; lista produtos
	string separator = " ; ";

	string split = line.substr(0, line.find(separator)); //substring from the original string until it finds the separator " ; "
	this -> idCliente = ((atoi(split.c_str())));
	line.erase(0, line.find(separator) + 3);

	split = line.substr(0, line.find(separator));
	this->data = Data(split);
	line.erase(0, line.find(separator) + 3);


	string products = line.substr(0, line.length());

		while (true) {
			if (products.find(", ") == -1) {
				produtos.push_back(products);
				break;
			}
			produtos.push_back(products.substr(0, products.find(", ")));
			products.erase(0, products.find(", ") + 2);
		}
}

unsigned int Transacao::getIdCliente() const {
	return idCliente;
}

Data Transacao::getData()
{
	return data;
}

vector<string> Transacao::getvector()
{
	return produtos;
}

void Transacao::setid(unsigned int i)
{
	this->idCliente = i;
}

void Transacao::setdate(Data d)
{
	this->data = d;
}

void Transacao::setvector_products(vector<string>products)
{
	this->produtos = products;
}

ostream& operator<<(ostream& out, const Transacao & trans){

	out << setw(4) << trans.idCliente << setw(15) << trans.data;
	out << setw(30);
	for (int i = 0; i < (trans.produtos.size()-1); i++)
	{	
			out << trans.produtos[i] << ", ";		
	}
	out << trans.produtos.back();
	return out;
}
