/*
 * Table.cpp
 *
 *  Created on: 5 mar 2021
 *      Author: Pawel
 */

#include "Table.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Table::Table() {
	this->size = 0;
	this->table = NULL;
}

Table::~Table() {
	deleteStructure();
}

void Table::deleteStructure(){
	delete [] this->table;
	this->size = 0;
}

void Table::resize(int newSize){
	int * temp = table;

	table = new int[newSize];
	int i;
	if(this->size < newSize){
		for(i = 0; i < this->size; i++){
			table[i] = temp[i];
		}
	}else{
		for(i = 0; i < newSize; i++){
			table[i] = temp[i];
		}
	}
	this->size = newSize;
	delete [] temp;
}

void Table::addAtFirst(int elem){
	if(table == NULL){
		this->size = 0;
		this->table = new int[size];
	}

	resize(this->size + 1);
	int i;
	for(i = size-1; i > 0;i--){
		this->table[i] = this->table[i-1];
	}
	this->table[0] = elem;
}

void Table::addAtEnd(int elem){
	if(table == NULL){
		this->size = 0;
		this->table = new int[size];
	}

	resize(this->size + 1);
	this->table[size-1] = elem;
}

void Table::addAtIndex(int elem, int index){
	if(index > size || index < 0){
		return;
	}
	if(table == NULL){
		this->size = 0;
		this->table = new int[size];
	}

	resize(this->size + 1);
	
	for(int i = size-1; i > index;i--){
			this->table[i] = this->table[i-1];
	}
	this->table[index] = elem;
}

void Table::deleteAtFirst(){
	if(size <= 0){
		return;
	}
	for(int i = 0; i < size-1;i++){
		this->table[i] = this->table[i+1];
	}
	resize(this->size - 1);
}

void Table::deleteAtEnd(){
	if(size <= 0){
		return;
	}
	resize(this->size - 1);
}

void Table::deleteAtIndex(int index){
	if(size <= 0){ //jesli talica jest pusta
		return;
	}
	if(index >= 0){
		for(int i = index; i < size-1;i++){
			this->table[i] = this->table[i+1];
		}
		resize(this->size - 1);
	}
}

void Table::searching(int elem){
	int i;
	int count = 0;
	for(i = 0;i < size;i++){
		if(this->table[i] == elem){
			count++;
		}
	}
	if(!count == 0){
		cout << "W tablicy znajduje sie taki element."<<endl;
	}else{
		cout << "Nie ma takiej liczby"<<endl;
	}
}

void Table::AddRandomToTesting(int newSize, int start, int end){
	deleteStructure();
	this->table = new int[newSize];
	this->size = newSize;

	srand(time(NULL));
	int randvalue = 0;

	int i;
	for(i = 0;i < size; ++i){
		randvalue = rand()%end + start;
		this->table[i] = randvalue;
	}
}

void Table::loadDataFromFile(const char * filename){
	string line;
	ifstream file;
	file.open(filename);

	if(!file){
		cout << "Blad otwarcia pliku" << endl;
	}else{
		deleteStructure();
		getline(file, line);
		int newSize = atoi(line.c_str());
		this->table = new int[newSize];
		this->size = newSize;
		
		int i = 0;
		while(getline(file, line) && i < newSize){
			this->table[i] = atoi(line.c_str());
			i++;
		}
		file.close();
	}
}

void Table::show(){
	int i;
	if(size == 0){
		cout << "Tablica jest pusta" << endl;
		return;
	}
	for(i = 0;i < size;i++){
		cout << this->table[i] << " ";
	}
	cout <<endl;
}

std::ostream& operator<<(std::ostream &strm, const Table &table){
	return strm << "Table size: " << table.size <<endl;
}
