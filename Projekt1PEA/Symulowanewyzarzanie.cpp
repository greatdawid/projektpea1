#include "Symulowanewyzarzanie.h"



void Symulowanewyzarzanie::zamienwierzcholki()
{
	int pierwszy = rand() % (size-1)+1; //rozne od 0
	int drugi = rand() % (size-1)+1;
	while (pierwszy == drugi) {
		drugi = rand() % (size-1)+1;
	} 
	obecna_droga = najlepsza_droga; //przepisanie
	int tmp = obecna_droga[pierwszy];
	obecna_droga[pierwszy] = obecna_droga[drugi];
	obecna_droga[drugi] = tmp;

}

void Symulowanewyzarzanie::wczytajmacierz(string nazwa)
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

void Symulowanewyzarzanie::wyswietlmacierz()
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

int Symulowanewyzarzanie::waga_drogi(vector<int> droga)
{
	int tmp_waga=0, tmp_element=0; //tmp_element poczatkowo 0, zwiazane to jest z definicja pierwszej drogi od wierzcholka 0...size 
	for (int i = 1; i < size; i++) //zakladamy ze zaczynamy od zerowego wierzcholka i tam konczymy
	{
		tmp_waga += macierz[tmp_element][droga[i]];
		tmp_element = droga[i];
	}
	tmp_waga += macierz[tmp_element][0];
	return tmp_waga;
}
void Symulowanewyzarzanie::szukajwyniku()
{
	uniform_real_distribution<double> distribution(0.0, 1.0);
	default_random_engine generator;
	double tmp_prawd = 0.0;
	while (temperatura_obecna>temperatura_minimalna) {
		for (int i = 0; i <500; i++)		//probny parametr zobaczymy jak to wyjdzie
		{
			zamienwierzcholki();
			waga_obecnej_drogi = waga_drogi(obecna_droga);

			if (waga_obecnej_drogi < waga_najlepszej_drogi) 
				{
					najlepsza_droga = obecna_droga;
					waga_najlepszej_drogi = waga_obecnej_drogi;
				}
			else {	
				tmp_prawd = distribution(generator);
				if (tmp_prawd<oblicz_prawd()) {
					najlepsza_droga = obecna_droga;
					waga_najlepszej_drogi = waga_obecnej_drogi;
				}
			}
		}
		temperatura_obecna *= wspolczynnik_chlodzenia;
	}

}
void Symulowanewyzarzanie::inicjuj(double tempc, double tempp, double tempm)
{
	wspolczynnik_chlodzenia = tempc;
	temperatura_minimalna = tempm;
	temperatura_obecna = tempp;
	for ( int i = 0; i < size; i++)
		obecna_droga.push_back(i);
	waga_obecnej_drogi = waga_drogi(obecna_droga);
	waga_najlepszej_drogi = waga_obecnej_drogi;
	najlepsza_droga = obecna_droga;
	srand((unsigned int)time(NULL));

}
double Symulowanewyzarzanie::oblicz_prawd()
{
	double prawd = -((waga_obecnej_drogi - waga_najlepszej_drogi)/temperatura_obecna);
	prawd = pow(M_E, prawd);
	return prawd;
}

void Symulowanewyzarzanie::test()
{
	inicjuj(0.99, 100000.0, 0.0001);
	szukajwyniku();
	cout << "Najlepsza trasa: ";
	for (unsigned int i = 0; i < size; i++)
		cout << najlepsza_droga[i] << ", ";
	cout << "0" << endl;
	cout << "Jej dlugosc: " << waga_najlepszej_drogi << endl;
	cout << endl;
	int w;
	cin >> w;

}

void Symulowanewyzarzanie::testowanie()
{
	double sredniczas = 0.0;
	int najlepsza=INT_FAST32_MAX;
	for (int i = 0; i < 20; i++)
	{
		double czas;
		StartCounter();
		inicjuj(0.99, 100000.0, 0.0001);
		szukajwyniku();
		czas = GetCounter();
		sredniczas += czas;
		cout << "Czas tego wykonania " << czas << "ms" << endl;
		cout << "Najlepsza znaleziona droga: ";
		for (unsigned int i = 0; i < size; i++)
			cout << najlepsza_droga[i] << ", ";
		cout << "0" << endl;
		cout << "Laczna waga: " << waga_najlepszej_drogi << endl;
		if (waga_najlepszej_drogi < najlepsza) najlepsza = waga_najlepszej_drogi;
		cout << endl;
	}
	cout <<"Najlepsza znaleziona w petli "<<najlepsza<< endl;
	cout << "Sredni czas obliczenia najlepszego rozwiazania wynosi:  " << sredniczas / 20 << "ms" << endl;

}

void Symulowanewyzarzanie::StartCounter()
{
	LARGE_INTEGER num;
	if (!QueryPerformanceFrequency(&num))
		std::cout << "Unable to perform!\n";

	freq = double(num.QuadPart) / 1000.0; //pomiar w  milisekundach
	QueryPerformanceCounter(&num);
	counts = num.QuadPart;
}

double Symulowanewyzarzanie::GetCounter()
{
	LARGE_INTEGER num;
	QueryPerformanceCounter(&num);
	return (num.QuadPart - counts) / freq;
}

Symulowanewyzarzanie::Symulowanewyzarzanie()
{
	counts = 0;
	freq = 0.0;
	macierz = nullptr;
}


Symulowanewyzarzanie::~Symulowanewyzarzanie()
{
	if (macierz == nullptr) {
		for (int i = 0; i < size; i++)
		{
			delete[] macierz[i];
		}
		delete[] macierz;
	}
}
