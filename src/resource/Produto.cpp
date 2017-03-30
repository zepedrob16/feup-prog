#include "Produto.h"


Produto::Produto(string line){ // nome ; custo
	string separator = " ; ";

	string split = line.substr(0, line.find(separator)); //substring from the original string until it finds the separator " ; "
	nome = split;
	line.erase(0, line.find(separator) + 3);
	split = line.substr(0, line.find(separator));
	custo = atof(split.c_str());
}

string Produto::getNome() const {
  return nome;
}

float Produto::getCusto() const {
  return custo;
}

void Produto::setnome(string n)
{
	nome = n;
}

void Produto::setcusto(float c)
{
	custo = c;
}

ostream& operator<<(ostream& out, const Produto & prod){

	out << setw(20) << prod.nome << setw(8) << prod.custo << endl;
	return out;
}
