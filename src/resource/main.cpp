#include <iostream>
#include <string>
#include <vector>
#include<iomanip>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"



void logo()
{
	cout << setw(10) << "Welcome to VENDE ++ " << endl << endl;
}



void main()
{
	logo();

	string loja, fichClients, fichProducts, fichTransactions;


	bool correct = false;
	while (correct == false)
	{
		clearScreen();
		logo();
		correct = infoInicial(loja, fichClients, fichProducts, fichTransactions);
	}


	// cria uma loja
	VendeMaisMais supermercado(loja, fichClients, fichProducts, fichTransactions);

	opcoesIniciais(supermercado); // menu inicial com as grandes opcoes
								  // que implementam as funcioanlidades
								  // disonibilizadas
}

