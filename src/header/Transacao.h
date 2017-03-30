#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Data.h"



using namespace std;


class Transacao {
 private:
  unsigned int idCliente;
  Data data; // na forma DD/MM/AAAAA
  vector<string> produtos;

 public:
	Transacao() {};
  Transacao(string line); // trabsacao na forma de  idCliente ; data ; lista de produtos
  unsigned int getIdCliente() const;
  Data getData();
  void setid(unsigned int i);
  void setdate(Data d);
  vector<string>getvector();
  void setvector_products(vector<string>products);
  friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao
};



