#include "Cliente.h"



Cliente::Cliente(string line){
	string separator = " ; ";

	string split = line.substr(0, line.find(separator)); //substring from the original string until it finds the separator " ; "
	this->id=((atoi(split.c_str())));
	line.erase(0, line.find(separator) + 3);
	split = line.substr(0, line.find(separator));
	this->nomCliente = split;
	line.erase(0, line.find(separator) + 3);
	split = line.substr(0, line.find(separator));
	this->date=Data(split);
	line.erase(0, line.find(separator) + 3);
	split = line.substr(0, line.find(separator));
	this->value=(stof(split.c_str()));
}

string Cliente::getNome() const{
  return nomCliente;
}

unsigned int Cliente::getId() const{
  return id;
}

float Cliente::getVolCompras() const{
  return value;
}

Data Cliente::getDate()
{
	return date;
}

void Cliente::setid(unsigned int i)
{
	this->id = i;
}

void Cliente::setnome(string n)
{
	this->nomCliente = n;
}

void Cliente::setvalue(float v)
{
	this->value = v;
}

void Cliente::setdate(Data d)
{
	this->date = d;
}

ostream& operator<<(ostream& out, const Cliente & cli){
	out << setw(2) << cli.id << setw(18) << cli.nomCliente << setw(8) << cli.date << setw(15) << cli.value << endl;
	return out;
}