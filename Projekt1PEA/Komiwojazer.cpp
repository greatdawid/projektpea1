#include "Komiwojazer.h"



Komiwojazer::Komiwojazer()
{
	counts = 0;
	freq = 0.0;
	macierz = nullptr;
	stosptr = 0;
	tmpstosptr = 0;

}


Komiwojazer::~Komiwojazer()
{
	if (macierz == nullptr) {
		for (int i = 0; i < size; i++)
		{
			delete[] macierz[i];
		}
		delete[] macierz;
	}
}

void Komiwojazer::StartCounter()
{
	LARGE_INTEGER num;
	if (!QueryPerformanceFrequency(&num))
		std::cout << "Unable to perform!\n";

	freq = double(num.QuadPart) / 1000.0; //pomiar w  milisekundach
	QueryPerformanceCounter(&num);
	counts = num.QuadPart;
}

double Komiwojazer::GetCounter()
{
	LARGE_INTEGER num;
	QueryPerformanceCounter(&num);
	return (num.QuadPart - counts) / freq;
}


void Komiwojazer::test()
{

	stos = new int[size];
	tmpstos = new int[size];
	srand(time(NULL));
	int losuj;
	double sredniczas = 0.0;
	for (int i = 0; i < 20; i++)
	{
		losuj = rand() % size;
		int *tmpwagasciezki = new int;
		*tmpwagasciezki = 0;
		najmniejszadroga = INT_MAX;
		bool *odwiedzone = new bool[size];
		for (int i = 0; i < this->size; i++)
		{
			odwiedzone[i] = false;
		}
		double czas;
		StartCounter();
		szukajrozwiazania(losuj, losuj,tmpwagasciezki, odwiedzone);
		czas = GetCounter();
		sredniczas += czas;
		cout << "Czas tego wykonania " << czas << "ms" << endl;
	}
	cout << "Sredni czas obliczenia najlepszego rozwiazania wynosi:  " << sredniczas / 20 << "ms" << endl;
}

void Komiwojazer::wyswietlmacierz()
{
	cout << "Graf ma:  " << size << " wierzcholkow." << endl << "Koszty podrozy z wierzcholka i do j sa nastepujace:  " << endl;
	for (int i = 0; i <size; i++)
	{
		cout << "  " << i;
	}
	cout << endl;
	for (int i = 0; i <size; i++)
	{
		cout << "___";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <size; j++)
		{
			if (j == 0) cout << i << "| ";
			cout << macierz[i][j] << " ";
		}
		cout << endl;
	}
}

void Komiwojazer::szukajrozwiazania(int startowy, int obecny, int * tmpwagasciezki, bool * odwiedzone)
{
	 //chowamy na stosie wierzcholek przegladany
	tmpstos[tmpstosptr++] = obecny;

	if (tmpstosptr < size) { //jezeli nie znaleziono drogi hamiltona
		odwiedzone[obecny] = true; //obecny zaznaczamy jako odwiedzony
		for (int i = 0; i < size; i++) { //przegladanie sasiadow
			if (odwiedzone[i]) continue;
				*tmpwagasciezki += macierz[obecny][i]; //dodanie wagi krawedzi
				szukajrozwiazania(startowy, i, tmpwagasciezki, odwiedzone); //wywolanie rekurencji
				*tmpwagasciezki -= macierz[obecny][i]; //usuwamy wage krawedzi
			
		}
		odwiedzone[obecny] = false;
		tmpstosptr--;
		return;
	}

	else {
		//znaleziono droge hamiltona
		*tmpwagasciezki += macierz[obecny][startowy]; //dodanie wartosci krawedzi do z obecnego do poczatkowego wierzcholka
		if (*tmpwagasciezki < najmniejszadroga) { //jesli jest najlepsza
			this->najmniejszadroga = *tmpwagasciezki; //zapamietujemy dlugosc drogi i sciezke
			for (int i = 0; i < tmpstosptr; i++) {
				stos[i] = tmpstos[i];
			}
			stosptr = tmpstosptr;
		}
		*tmpwagasciezki -= macierz[obecny][startowy]; //usuwamy ze sciezki wartosc ostatniej krawedzi
	}
	tmpstosptr--;
}

void Komiwojazer::wczytajmacierz(string nazwa)
{
	fstream plik;
	plik.open(nazwa, fstream::in);
	if (!plik.is_open()) {
		cout << "Nieudana proba otwarcia pliku!" << endl;
		
	}
	plik >> size;
	macierz = new int *[size];
	for (int i = 0; i < size; i++) {
		macierz[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int tmp;
			plik >> tmp;
			macierz[i][j] = tmp;
		}
	}
	plik.close();
}


void Komiwojazer::BForce(int startowy)
{
	bool *odwiedzone = new bool[size];
	for (int i = 0; i < size; i++) {
		odwiedzone[i] = false;
	}
	stos = new int[size];
	tmpstos = new int[size];
	najmniejszadroga = INT_MAX;
	int * tmpwagadroga = new int;
	*tmpwagadroga = 0;
	szukajrozwiazania(startowy, startowy, tmpwagadroga, odwiedzone);
	if (najmniejszadroga == INT_MAX) {
		cout << "Sciezka nie zostala odnaleziona" << endl;
		delete[] odwiedzone;
		return;
	}
	else {
		cout << "Najkrotsza sciezka ma wage: " << najmniejszadroga << endl;
		cout << "Odwiedzono nastepuja wierzcholki w kolejnosci: " << endl;
		for (int i = 0 ; i<size; i++) {
			cout << stos[i] << " --> ";
		}
		cout << startowy << endl;
		cout << endl;
	}
	delete[] tmpstos;
	delete[] stos;
	delete[] odwiedzone;
}
