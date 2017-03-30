#include "utils.h"
#include "Windows.h"

void clearScreen(){
	system("cls");
}

bool isinteger(const string s)
{
	if (s.empty() || !isdigit(s[0]))
		return false;

	char *p;
	strtol(s.c_str(), &p, 10);
	return (*p == 0);
}//verifica se a escolha e um inteiro

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){

	string input;
	getline(cin, input);
	if (isinteger(input))
	{
		unsigned short int opcao = strtol(input.c_str(), nullptr, 10);

		if (opcao >= min || opcao <= max)
			return opcao;
	}
	else
		cout << "Escolha invalida";
	Sleep(300);
}

