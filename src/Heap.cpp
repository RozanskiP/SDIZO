/*
 * Heap.cpp
 *
 *  Created on: 5 mar 2021
 *      Author: Pawel
 */

#include "Heap.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Heap::Heap() {
	this->size = 0;
	this->tab = NULL;
	this->reallocsize = 10;
}

Heap::~Heap() {
	deleteStructure();
}

void Heap::deleteStructure(){
	delete [] this->tab;
	this->size = 0;
	this->reallocsize = 10;
}

void Heap::realloc(){
	int * temp = tab;
	int i;
	tab = new int[size+reallocsize];
	for(i = 0; i < size ;i++){
		tab[i] = temp[i];
	}
	delete [] temp;
}

void Heap::addNode(int value){
	if(this->tab == NULL){
		this->size = 0;
		this->tab = new int[size+11];
		this->reallocsize = 10;
	}
	if(reallocsize <= 2){
		this->reallocsize = 10;
		realloc();
	}
	int temp;
	int indexnew = this->size++;
	int parent = (indexnew-1)/2;
	while(indexnew > 0 && value > tab[parent]){ //je�li warto�� jest wieksza niz rodzic i wartosc indexu miesci sie w rozmiarze
		// temp = tab[indexnew];
		tab[indexnew] = tab[parent];
		// tab[parent] = temp;
		indexnew = parent;
		parent = (indexnew-1)/2;
	}
	tab[indexnew] = value;
	this->reallocsize--;
}

void Heap::deleteNodeKey(int elem){
	if(size == 0){
		return;
	}
	if(reallocsize >= 18){
		this->reallocsize = 10;
		realloc();
	}
	int i;
	int indexToDelete = -1;
	for(i = 0;i < size; ++i){
		if(tab[i] == elem){
			indexToDelete = i;
			break;
		}
	}
	cout << "Indeks do usun: " << indexToDelete << endl;
	cout << "SIZE: " << this->size << endl;
	if(indexToDelete == 0){
		deleteNode();
		return;
	}
	if(indexToDelete == size-1){ //jeśli nasza wartościa jest ostatni element to go usuwamy
		this->size--;
		this->reallocsize++;
		return;
	}
	if(indexToDelete > 0){
		int temp = tab[indexToDelete];
		tab[indexToDelete] = tab[size-1];
		tab[size-1] = temp;
		// cout << "Zamiana: " << indexToDelete << " : " << size-1 << endl;
		this->size--;
		if(tab[indexToDelete] > tab[(indexToDelete-1)/2]){//jesli jest wiekszy od rodzica to
			// cout << "Wiekszy" << endl;
			while( ( indexToDelete > 0 ) && ( (indexToDelete-1)/2 >= 0 ) && ( tab[(indexToDelete-1)/2] < tab[indexToDelete] ) ){
				// cout << "Zamiana Wiekszy: " << indexToDelete << " : " << (indexToDelete-1)/2 << endl;
				int temp = tab[(indexToDelete-1)/2];
				tab[(indexToDelete-1)/2] = tab[indexToDelete];
				tab[indexToDelete] = temp;
				indexToDelete = (indexToDelete-1)/2;
				this->reallocsize++;
			}
		}else if(tab[indexToDelete] < tab[(indexToDelete-1)/2]){ //jesli jest mniejszy od rodzica to
			int v = tab[indexToDelete];
			// cout << "Mniejszy" << endl;
			int parent = (indexToDelete-1)/2;
			int son = indexToDelete*2+1;
			// cout << "indexToDelete: " << indexToDelete << endl;
			// cout << "Rodzic: " << tab[parent] << endl;
			// cout << "Syn lewy: " << tab[son] << endl;
			while(son < size){
				if(son+1 < size && tab[son+1] > tab[son]){ //jesli prawy syn jest wiekszy to zamien na jego paramtry i wtedy zmienimy z prawym synem
					son++;
					// cout << "Zamieniamy na prawego" << endl;
				}
				if( v >= tab[son]){ // jak warunek jest spelniony ze obydwoje z synow sa mniejsi to wyjdz
					break;
				}
				// cout << "Zamiana: " << indexToDelete << " : " << son << endl;
				temp = tab[indexToDelete];
				tab[indexToDelete] = tab[son];
				tab[son] = temp;
				parent = son;
				son = 2*son+1; // wpisanie nastepnego lewego syna
			}
			// tab[parent] = v;
			this->reallocsize++;
		}else{ //jesli jest rowny rodzicow to nic nie robimy czyli ostatni mozliwe warunek
			cout << "Rowny" << endl;
		}
	}else{
		cout << "Nie ma takiego elemetu" << endl;
	}
}

void Heap::deleteNode(){
	if(size == 0){
		return;
	}
	if(reallocsize >= 18){
		this->reallocsize = 10;
		realloc();
	}

	int v = tab[size-1];
	size--;
	int parent = 0;
	int son = 1;
	while(son < size){
		if(son+1 < size && tab[son+1] > tab[son]){ //jesli prawy syn jest wiekszy to zamien na jego paramtry i wtedy zmienimy z prawym synem
			son++;
		}
		if( v >= tab[son]){ // jak warunek jest spelniony ze obydwoje z synow sa mniejsi to wyjdz
			break;
		}
		tab[parent] = tab[son];
		parent = son;
		son = 2*son+1; // wpisanie nastepnego leweso syna
	}
	tab[parent] = v; // wstawiamy nasza wartosc w kopcu w miejsce gdzie zostalo ostatecznie znalezione
	this->reallocsize++;
}

void Heap::searching(int elem){
	int i;
	int count = 0;
	for(i = 0;i < size;i++){
		if(this->tab[i] == elem){
			count++;
		}
	}
	if(!count == 0){
		cout << "W tablicy znajduje sie taki element."<<endl;
	}else{
		cout << "Nie ma takiej liczby"<<endl;
	}
}

void Heap::loadDataFromFile(const char * filename){
	string line;
	ifstream file;
	file.open(filename);

	if(!file){
		cout << "Blad otwarcia pliku" << endl;
	}else{
		deleteStructure();
		this->tab = new int[size+11];
		int sizeFromFile = 0;
		getline(file, line);
		sizeFromFile = atoi(line.c_str());
		int i;
		for(i = 0;i < sizeFromFile;i++){
			getline(file, line);
			addNode(atoi(line.c_str()));

			// tab[i] = atoi(line.c_str());
		}
		// buildByFloydAlgoritm();
		file.close();
	}
}

//https://eduinf.waw.pl/inf/alg/001_search/0113.php
void Heap::printBT(string sp, string sn, int v){ //TODO sa jakies dzinwe ascii
	string s;
	string cr, cl, cp;

	cr = cl = cp = "  ";
	cr [0] = 43; cr [1] = 45;
	cl [0] = 45; cl [1] = 43;
	cp [0] = 124	;

	if( v < this->size )
	{
		s = sp;
		if( sn == cr ) s [ s.length( ) - 2 ] = ' ';
		printBT(s + cp, cr, 2 * v + 2 );

		s = s.substr ( 0, sp.length( ) - 2 );

		cout << s << sn << this->tab [ v ] << endl;

		s = sp;
		if( sn == cl ) s [ s.length( ) - 2 ] = ' ';
		printBT(s + cp, cl, 2 * v + 1 );
	}
}

void Heap::show(){
	int i;
	if(size == 0){
		cout << "Kopiec jest pusty" << endl;
		return;
	}
	for(i = 0;i < size;i++){
		cout << tab[i] << ", ";
	}
	cout << endl;
	cout << "Drzewo: "<< endl;
	printBT( "", "", 0);
}

void Heap::AddRandomToTesting(int sizeNew, int start, int end){
	deleteStructure();
	this->tab = new int[size+11];

	srand(time(NULL));

	int randvalue = 0;
	this->size = 0;

	int i;
	for(i = 0;i < sizeNew; ++i){
		randvalue = rand()%end + start;
		addNode(randvalue);
	}
}

void moveDown(int tab2[],int first, int last){ //TODO na cwiczenia do usuniecia
	int largest = 2*first + 1; //lewy syn
	while(largest <= last){ //mniejszy niz rozmiar tablicy
		if(largest < last && tab2[largest] < tab2[largest+1]){ //je�lli prawy syn jest wiekszy to
			largest++; //dodaj jeden aby by� wskaznikiem prawego syna
		}
		if(tab2[first] < tab2[largest]){ //je�li rodzic jest mniejszy to zamien je
			int temp = tab2[first];
			tab2[first] = tab2[largest];
			tab2[largest] = temp;
		}else{	//a je�li nie zmieni�e� to nie musisz poprawia� wiec warunek wtedy bedzie nie spelniony
			largest = last+1;
		}
	}
}

void Heap::buildByFloydAlgoritm(){ //TODO na cwiczenia do usuniecia
	int i;
	for(i = (size-1)/2 - 1; i >= 0; --i){ //dla kazdego elementu nie b�dacego li�ciem przeproawdzic
		moveDown(tab, i, size-1); //przeksztalcenie zmiany z synami jesli sa wieksi
	}
}
