#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Data.h"

using namespace std;

class Cliente {
 private:
  unsigned int id;
  string nomCliente;
  float value;
  Data date;

 public:
	 Cliente() {};
  Cliente(string line);
  string getNome() const;
  unsigned int getId() const;
  float getVolCompras() const;
  Data getDate();
  void setid(unsigned int i);
  void setnome(string n);
  void setvalue(float v);
  void setdate(Data d);
  friend ostream& operator<<(ostream& out, const Cliente & cli);  // mostra informacao do cliente no ecra
};

