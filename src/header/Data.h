# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Data {
 private:
  unsigned int day;
  unsigned int month;
  unsigned int year;

 public:
  Data(){};
  Data(unsigned int dia, unsigned int mes, unsigned int ano);
  Data(string line); // data na forma DD/MM/AAA
  unsigned int getDia() const;
  unsigned int getMes() const;
  unsigned int getAno() const;
  void setDia(int dia);
  void setMes(int mes);
  void setAno(int ano);
  friend bool operator==(const Data & D1, const Data & D2);
  friend bool operator<=(const Data & D1, const Data & D2);
  friend ostream& operator<<(ostream& out, const Data & data);
};


