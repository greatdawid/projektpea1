#pragma once
#include<windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cmath>
#include <random>
#include <vector>
#define M_E 2.71828182845904523536

using namespace std;

class Symulowanewyzarzanie
{
	double freq;
	__int64 counts;
	vector<int> obecna_droga;
	int waga_obecnej_drogi;
	int waga_najlepszej_drogi;
	vector <int> najlepsza_droga;
	double temperatura_obecna;
	double wspolczynnik_chlodzenia;
	double temperatura_minimalna;

public:

	int **macierz;
	int size;
	void zamienwierzcholki();
	void wczytajmacierz(string nazwa);
	void wyswietlmacierz();
	int waga_drogi(vector <int> droga);
	void szukajwyniku();
	void inicjuj(double tempc,double tempp,double tempm);
	double oblicz_prawd();
	void test();
	void testowanie();
	void StartCounter();
	double GetCounter();

	Symulowanewyzarzanie();
	~Symulowanewyzarzanie();
};

