#pragma once
#include<windows.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>

using namespace std;

class Komiwojazer
{

	double freq;
	__int64 counts;
public:

	int **macierz;
	int najmniejszadroga;
	int *stos, *tmpstos;
	int stosptr, tmpstosptr;
	int size;

	Komiwojazer();
	~Komiwojazer();
	void StartCounter();
	double GetCounter();
	void test();
	void wyswietlmacierz();
	void BForce(int startowy);
	void szukajrozwiazania(int startowy, int obecny,int *tmpwagasciezki,bool* odwiedzone );
	void wczytajmacierz(string nazwa);


};

