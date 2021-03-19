/*
 * Table.cpp
 *
 *  Created on: 5 mar 2021
 *      Author: Pawe�
 */

#include "Table.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
//#include <windows.h>
using namespace std;

//https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter

//double PCFreq = 0.0;
//__int64 CounterStart = 0;

//void StartCounterTime(){
//	LARGE_INTEGER li;
//	if(!QueryPerformanceCounter(&li)){
//		cout << "Blad" << endl;
//	}
//
//	PCFreq = double(li.QuadPart)/1000.0;
//
//	QueryPerformanceCounter(&li);
//	CounterStart = li.QuadPart;
//}
//
//void GetCounterTime(){
//	LARGE_INTEGER li;
//	QueryPerformanceCounter(&li);
//	cout << "Czas: " << double(li.QuadPart-CounterStart)/PCFreq << endl;
//}

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
	if(table == NULL){
		this->size = 0;
		this->table = new int[size];
	}

	resize(this->size + 1);
	if(index > size){
		return;
	}
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
	if(size <= 0 || index > size){
		return;
	}

	for(int i = index; i < size-1;i++){
		this->table[i] = this->table[i+1];
	}
	resize(this->size - 1);
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
	for(i = 0;i < size;i++){
		cout << this->table[i] << " ";
	}
	cout <<endl;
}

std::ostream& operator<<(std::ostream &strm, const Table &table){
	return strm << "Table size: " << table.size <<endl;
}

int main(int argc, char **args){
	Table table;


	srand(time(NULL));
	int randvalue = 0;
	int size;
	sscanf(args[1], "%d", &size);

	for(int i=0; i< size; i++){
		randvalue = rand();
		table.addAtFirst(randvalue);
	}


	// cout<<table<<endl;

	// table.addAtFirst(5);
	// table.addAtFirst(6);
	// table.addAtFirst(18);
	// table.addAtFirst(1);
	// table.show();

	// table.addAtEnd(4);
	// table.addAtEnd(14);

	// table.addAtFirst(13);

	// table.show();
	// cout<<table<<endl;

	// table.addAtIndex(111,2);
	// table.show();

	// table.searching(18);
	
	// table.deleteAtFirst();
	// table.deleteAtIndex(4);
	// table.deleteAtEnd();
	// table.show();

	// const char * filename = "DaneTablica.txt";

	// table.loadDataFromFile(filename);
	// table.show();
	
	// table.AddRandomToTesting(100000, 0, 0xFFFFFFFF);
	// table.show();


	

	// cout<<table<<endl;

	return 0;
}
