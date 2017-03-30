#include "Data.h"



Data::Data(string line)
{
	string separator = "/";

	string str = line.substr(0, line.find(separator));
	this ->day=(atoi(str.c_str()));
	line.erase(0, line.find(separator) + 1);
	str = line.substr(0, line.find(separator));
	this ->month =(atoi(str.c_str()));
	line.erase(0, line.find(separator) + 1);
	str = line.substr(0, line.find(' '));
	this->year=(atoi(str.c_str()));
}
Data::Data(unsigned int dia, unsigned int mes, unsigned int ano)
{
	this->day = dia;
	this->month = mes;
	this->year = ano;
}

unsigned int Data::getDia() const{
  return day;
}

unsigned int Data::getMes() const{
  return month;
}

unsigned int Data::getAno() const{
  return year;
}

void Data::setDia(int dia){
	day = dia;
}

void Data::setMes(int mes){
	month = mes;
}

void Data::setAno(int ano){
	year = ano;
}

bool operator==(const Data & D1, const Data & D2)
{
	if (D1.day == D2.day&&D1.month == D2.month&&D1.year == D2.year)
		return true;
	else
		return false;
}

bool operator<=(const Data & D1, const Data & D2)
{
	if (D2.year > D1.year ||
		(D1.year == D2.year && D2.month > D1.month) ||
		(D1.year == D2.year && D1.month == D2.month && D2.day > D1.day)|| (D1.year == D2.year && D1.month == D2.month && D2.day == D1.day))
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const Data & data){
	if (data.day < 10)
		out << "0" << data.day;
	else
		out << data.day;
	out << "/";
	if (data.month < 10)
		out << "0" << data.month;
	else
		out << data.month;
	out << "/" << data.year;

	return out;
}
