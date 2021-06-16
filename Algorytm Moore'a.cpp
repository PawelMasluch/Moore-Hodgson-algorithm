/*

Copyright (C) Pawel Masluch, 2021. All rights reserved.


Algorytm Moore'a (Hodgsonsa) znajduje minimalna liczbe 
zadan opoznionych, przy zalozeniu, ze wszystkie zadania 
maja byc wykonane sekwencyjnie na jednym procesorze
oraz zadania wykonuja sie niezaleznie od siebie.

Dodatkowo, podaje przykladowa kolejnosc wykonywania zadan,
gwarantujaca minimalna liczbe zadan opoznionych.
*/


#include<iostream>
#include<algorithm>
#include<list>
#include<queue>


using namespace std;


typedef pair <int, int>  Para;

typedef pair< Para, int > Trojka;

typedef list <  Trojka  >  Lista;


#define MP make_pair


int main()
{
	/*
	Liczba zadan do wykonania przez procesor.
	*/
	int n;
	cin >> n;
	
	
	
	/* 
	Lista zadan do wykonania. 
	
	Dla danego zadania,
	pierwszym elementem jest termin ukonczenia (d),
	drugim - dlugosc trwania (p),
	trzecim - identyfikator zadania (id).
	*/
	Lista Zadania;
	
	
	
	/*
	Pomocnicza tablica mowiaca, czy dane zadanie jest opoznione, czy nie.
	*/
	bool opoznione[n];
	
	
	
	/*
	Kolejka priorytetowa trojek postaci: dlugosc zadania (p), termin ukonczenia zadania (d), nr zadania (id).
	*/
	priority_queue <Trojka>  PQ;
	
	
	
	/*
	Wczytanie zadan.
	*/
	int p, d, id;
	
	for(id=0; id<n; ++id)
	{
		cin >> p >> d;
		
		Zadania.push_back(  MP( MP(d, p), id)  ); // p - dlugosc trwania zadania, d - termin ukonczenia zadania, id - identyfikator zadania
		
		opoznione[id] = false; // poczatkowo, zadanie o identyfikatorze "id" nie jest opoznione
	}
	
	
	
	/*
	Sortowanie zadan (rosnaco) wzgledem terminow ukonczen (d). 
	*/
	Zadania.sort();
	
	
	
	/*
	Wlasciwy etap algorytmu.
	
	Symulujemy wykonywanie kolejnych zadan w czasie.
	
	Jesli w pewnym momencie przekraczamy termin ukonczenia aktualnie rozpatrywanego zadania (d),
	to decydujemy sie nie wykonywac najdluzej trwajacego (p) jak dotad zadania
	i wyrzucic owo najdluzej trwajace zadanie na koniec listy zadan. 
	*/
	int ile_zadan_opoznionych = 0;
	int czas = 0;
	int licznik = 0; // ile zadan juz rozpatrzylismy
	int P, D, ID;
	
	for(Lista::iterator it = Zadania.begin(); it != Zadania.end()  && licznik < n; ++it, ++licznik) // przegladamy pierwszych "n" elementow na liscie zadan
	{
		// Parametry aktualnie rozpatrywanego zadania
		p = (*it).first.second; // czas trwania
		d = (*it).first.first; // termin ukonczenia
		id = (*it).second; // identyfikator
		
		czas += p; // dodajemy czas trwania aktualnego zadania (p)
		
		PQ.push(  MP( MP( p, d ), id )   ); // dodajemy do kolejki priorytetowej aktualnie rozpatrywane zadanie
		
		
		if( czas > d ) // jesli przekroczylismy termin ukonczenia aktualnie rozpatrywanego zadania
		{
			++ile_zadan_opoznionych; // zwiekszamy liczbe zadan opoznionych o 1
			
			// Parametry najdluzszej trwajacego zadania (sposrod zadan bedacych aktualnie w kolejce)
			P = PQ.top().first.first; // czas trwania
			D = PQ.top().first.second; // termin ukonczenia
			ID = PQ.top().second; // identyfikator
			
			opoznione[ID] = true; // zadanie o identyfikatorze ID jest opoznione
			
			Zadania.push_back(  MP( MP(D, P), ID)  ); // dodajemy na koniec listy zadan znalezione zadanie opoznione
			
			czas -= P; // nie decydujemy sie wykonywac teraz znalezionego zadania opoznionego, zatem zmniejszamy czas o dlugosc trwania (P) tego znalezionego zadania opoznionego
			
			PQ.pop(); // pozbywamy sie z kolejki tego znalezionego zadania opoznionego
		}
	}
	
	
	/*
	Pozbywamy sie duplikatow na liscie zadan
	*/
	licznik = 0; // ile zadan juz rozpatrzylismy
	
	for(Lista::iterator it = Zadania.begin(); it != Zadania.end() && licznik < n;  ++licznik) // przegladamy pierwszych "n" elementow na liscie zadan
	{
		id = (*it).second; // identyfikator aktualnie rozpatrywanego zadania
		
		if( opoznione[id] == true ) // jesli aktuane zadanie jest opoznione
		{
			it = Zadania.erase( it ); // usun aktualne zadanie z listy zadan i przejdz do kolejnego zadania
		}
		else
		{
			++it; // przejdz do kolejnego zadania na liscie zadan
		}
	}
	
	
	
	/*
	Wypisywanie liczby zadan opoznionych oraz optymalnej kolejnosci wykonywania zadan.
	Ciekawostka: jesli opoznionych jest "k" zadan, to jest to "k" ostatnich zadan w optymalnej kolejnosci wykonywania zadan.
	*/
	cout << ile_zadan_opoznionych << endl;
	
	for(Lista::iterator it = Zadania.begin(); it != Zadania.end(); ++it)
	{
		id = (*it).second; // identyfikator aktualnie rozpatrywanego zadania
		cout << id + 1 << " ";
	}
	cout << endl;
	
	
	return 0;	
}

/*
Dane testowe


Zestaw 1:
10
5 7
11 30
10 40
1 10
9 20
7 25
4 14
9 55
10 45
8 34


Zestaw 2:
4
10 6
1 100
5 9
100 1


Zestaw 3:
6
2 9
7 6
1 17
171 12
12 88
9 78


Zestaw 4:
30
4 6
6 10
3 8
7 15
9 20
7 10
4 40
1 9
2 6
7 45
9 50
11 20
20 60
6 11
9 30
5 25
12 60
7 14
10 48
20 30
12 70
1 4
4 10
5 70
9 36
2 16
7 80
4 11
6 57
3 24
*/
