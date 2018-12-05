#include <iostream>
#include "Komiwojazer.h"
#include "Symulowanewyzarzanie.h"
#include <windows.h>
using namespace std;
string filepa = "C:\\Users\\Dawid\\Documents\\Visual Studio 2015\\Projects\\Projekt1PEA\\";
string filepath = "C:\\Users\\Dawid\\Documents\\Visual Studio 2015\\Projects\\Projekt1PEA\\data17.txt";
string tmp = "";
void menu() {
	Komiwojazer * unit = new Komiwojazer();
	Symulowanewyzarzanie *jednostka = new Symulowanewyzarzanie();
	bool wyjscie = true;
	do {
		system("cls");
		cout << "Witaj w programie, ktory sprobuje rozwiazac problem komiwojazera"<<endl;
		cout << "1. Wczytaj macierz definiujaca krawedzi(domyslny plik w folderze) " << endl;
		cout << "2. Wczytaj macierz z podanego pliku" << endl;
		cout << "3. Rozwiaz problem komiwojazera za pomoca metody brutal force" << endl;
		cout << "4. Testuj i oblicz czas wykonania(BrutalForce)" << endl;
		cout << "5. Wyswietl macierz w konsoli" << endl;
		cout << "6. Wyjscie z programu" << endl;
		cout << "7. Utworz przyblizone rozwiazanie za pomoca metody symulowanego wyzarzania" << endl;
		cout << "8. Testuj algorytm symulowanego wyzarzania" << endl;
		int wybor;
		cin >>wybor;
		switch (wybor) {
		case 1:
			jednostka->wczytajmacierz(filepath);
			//unit->wczytajmacierz(filepath);
			break;
		case 2:
			//string diffpath = "C:\\"			
			cout << "Wpisz nazwe pliku(bez .txt)" << endl;
			cin >> tmp;
			cout << endl;
			filepa = filepa + tmp+".txt";
			jednostka->wczytajmacierz(filepa);
			break;
		case 3:
			system("cls");
			cout << "Podaj numer wierzcho³ka z ktorego chcesz zaczac" << endl;
			int w;
			cin >> w;
			unit->BForce(w);
			system("pause");
			break;
		case 4:
			unit->test();
			system("pause");
			break;
		case 5:
			system("cls");
			if (jednostka->macierz == nullptr) {
				cout << "Nie wczytano macierzy" << endl;
			}
			else {
				jednostka->wyswietlmacierz();
				//unit->wyswietlmacierz();
				system("pause");
			}
			system("pasue");
			break;
		case 6:
			wyjscie = false;
			break;
		case 7:
			jednostka->test();
			break;
		case 8:
			jednostka->testowanie();
			system("pause");
			break;
		default:
			cout << "Wcisnieto z³y numer" << endl;
			system("pasue");
			break;
		}

	} while (wyjscie);

	delete unit;
}


int main() {


	/*
	Komiwojazer * unit = new Komiwojazer();
	unit->wczytajmacierz(filepath);
	unit->wyswietlmacierz();
	unit->BForce(2);*/

	menu();

	return 0;
};