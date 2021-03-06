#include "pch.h"
#include <iostream>
#include "functions.h"
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;
int main()
{
	srand(time(NULL));
	MatrixGraph graph;
	graph.loadFromFile("6_2.txt");
	int wynik = 80;
	string pliki[] = { "6_1", "6_2", "10", "12", "13", "14", "15", "17" }; 
	int wyniki[] = { 132,80,212,264,269,282,291,39 };//i
	int liczbaplikow = 8;

	//string pliki[] = { "data36", "data45", "data70","data100"};
	//int wyniki[] = { 1473, 1613,38673,36230}; 
	//int liczbaplikow = 4;

	//string pliki[] = {"data100"};
	//int wyniki[] = {36230};
	//int liczbaplikow = 1;

	int licznikprocent = 0;
	double licznikczas = 0;
	double blad = 0.0;

	int* result = new int[graph.getNumOfVertex()+1];
	double czas;
	double* czasPtr = &czas;
	int koszt;
	int* kosztPtr = &koszt;

	//koszt = genetic(graph, czasPtr, result);
	//cout << koszt;
	//double licznik = koszt - wynik;
	//		double mianownik = wynik;
	//		blad += (licznik*100.0) / mianownik;
	//cout<< "SredniBlad wzgledny" << blad << "%" << endl;

	ofstream fout;
	if(liczbaplikow==8)
		fout.open("wyniki_cross30.txt");
	else
		fout.open("wynikiBIG_cross30.txt");


	for (int i = 0; i <liczbaplikow; i++)				//nazwa pliku + sprawdzenie wyniku
	{
		string nazwapliku = pliki[i];
		nazwapliku += ".txt";
		cout << nazwapliku.c_str() << endl;
		graph.loadFromFile(nazwapliku);	
		int* result = new int[graph.getNumOfVertex() + 1];
		licznikprocent = 0;
		licznikczas = 0.0;
		blad = 0.0;

		for (int m = 0; m < 100; m++)
		{	
			if(m%10==0)cout << m+10 << "% ";
			koszt=genetic(graph, czasPtr, result);
			double licznik = koszt - wyniki[i];
			double mianownik = wyniki[i];
			blad += (licznik*100.0) / mianownik;

			if (koszt == wyniki[i]) licznikprocent++;
			licznikczas += czas;
		}
		cout << endl;
		licznikczas /= 100.0;
		blad /= 100.0;
		fout <<pliki[i].c_str()<<"\t"<< licznikczas << "\t" << licznikprocent << "%\t" << blad << "%" << endl;

		graph.~MatrixGraph();
	}
	fout.close();



	//genetic(graph);


	system("pause");
	return 0;
}


