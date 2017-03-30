#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>


using namespace std;


class Produto {
 private:
  string nome;
  float custo;
  
 public:
	 Produto() {};
  Produto(string line);
  string getNome() const;
  float getCusto() const;
  void setnome(string n);
  void setcusto(float c);
  friend ostream& operator<<(ostream& out, const Produto & prod); // ostra umproduto 
};


