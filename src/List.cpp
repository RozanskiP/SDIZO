/*
 * List.cpp
 *
 *  Created on: 5 mar 2021
 *      Author: Pawe�
 */

#include "List.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Node::Node(){
	this->value = 0;
	this->next = NULL;
	this->prev = NULL;
}

Node::~Node(){
}

List::List() {
	this->head = NULL;
}

List::~List() {
	deleteStructure();
}

void List::deleteStructure(){
	Node * node;

	while(head){
		node = head->next;
		delete head;
		head = node;
	}
}

void List::AddRandomToTesting(int size, int start, int end){
	deleteStructure();
	srand(time(NULL));

	int randvalue = rand()%end + start;

	Node *node = new Node();
	head = node;
	head->next = NULL;
	head->prev = NULL;
	head->value = randvalue;

	int i;
	for(i = 0;i < size-1; ++i){ //-1 bo pierwszy element jest headem
		randvalue = rand()%end + start;
		Node *node = new Node();
		node->next = head;
		node->prev = NULL;

		if(head){
			head->prev = node;
		}
		head = node;
		node->value = randvalue;
	}

}

void List::addAtFirst(int value){
	Node *node = new Node();

	node->next = head;
	node->prev = NULL;

	if(head){
		head->prev = node;
	}
	head = node;
	node->value = value;
}

void List::addAtEnd(int value){
	Node * node = new Node();
	Node* temp = head;

	while(temp->next != NULL){
		temp = temp->next;
	}
	node->value = value;
	node->next = NULL;
	temp->next = node;
	node->prev = temp;
}

void List::addAtIndex(int value, int index){
	Node *temp = head;

	int counter = 0;
	while(temp->next != NULL){
		++counter;
		temp = temp->next;
	}

	Node * node = new Node();
	temp = head;
	if(counter < index){ //to dodaj na koniec listy
		addAtEnd(value);
	}else if(index == 0){ //jesli index zero to wstaw na poczatek
		addAtFirst(value);
	}else{ //to wstaw na index
		counter = 2;
		while(counter <= index){
			temp = temp->next;
			++counter;
		}
		node->next = temp->next;
		temp->next->prev = node;
		node->prev = temp;
		temp->next = node;
		node->value = value;
	}
}

void List::deleteAtFirst(){
	if(head == NULL){
		cout << "Brak elementow do usuniecia"<<endl;
	}else{
		Node *temp = head;
		head = head->next;
		if(head != NULL){
			head->prev = NULL;
		}
		delete temp;
	}
}

void List::deleteAtEnd(){
	if(head == NULL){
		cout << "Brak elementow do usuniecia"<<endl;
	}else{
		Node *temp = NULL;
		Node *lastnode = head;
		while(lastnode->next != NULL){
			lastnode = lastnode->next;
		}
		temp = lastnode;
		lastnode = lastnode->prev;
		lastnode->next = NULL;
		delete temp;
	}
}

void List::deleteAtIndex(int index){
	if(head == NULL){
		cout << "Brak elementow do usuniecia"<<endl;
	}else{
		Node *temp = head;
		int counter = 0;
		while(temp->next != NULL){
			++counter;
			temp = temp->next;
		}
		temp = head;
		if(counter <= index){ //to usun z konca
			deleteAtEnd();
		}else if(index == 0){ //to usun z poczatku
			deleteAtFirst();
		}else{
			counter = 1;
			while(counter <= index){
				temp = temp->next;
				++counter;
			}
			Node *indexnode = new Node();
			indexnode = temp;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete indexnode;
		}
	}
}

void List::searching(int value){
	int counter = 0;

	Node *temp = head;
	while(temp != NULL){
		if(temp->value == value){
			++counter;
		}
		temp = temp->next;
	}

	if(counter != 0){
		cout << "W tablicy znajduje sie taki element."<<endl;
	}else{
		cout << "Nie ma takiej liczby"<<endl;
	}
}

void List::loadDataFromFile(const char * filename){
	string line;
	ifstream file;
	deleteStructure();
	file.open(filename);

	if(!file){
		cout << "Blad otwarcia pliku" << endl;
	}else{
		getline(file,line);
		int newSize = atoi(line.c_str());
		cout << "SIZE: " << newSize << endl;
		getline(file,line);
		Node *node = new Node();
		head = node;
		head->next = NULL;
		head->prev = NULL;
		head->value = atoi(line.c_str());
		int tempvalue;
		int i = 1;
		while(getline(file, line) && i < newSize){
			tempvalue = atoi(line.c_str());
			node = new Node();

			node->next = head;
			node->prev = NULL;

			if(head){
				head->prev = node;
			}
			head = node;
			node->value = tempvalue;
			i++;
		}
	}
}

void List::show(){ //TODO Wyswietlanie od tylu i od przodu
	Node * node = head;
	if(!node){
		cout << "Lista jest pusta" <<endl;
	}else{
		int counter = 0;
		cout << "Od przodu: ";
		while(node){
			cout  << node->value <<" ";
			node = node->next;
			counter++;
		}
		cout << "Od tyłu: ";
		while(node){
			cout  << node->value <<" ";
			node = node->next;
			counter++;
		}
		cout << endl;
	}
}

int main(int argc, char **args){

	List list;

	srand(time(NULL));
	int randvalue = 0;
	int size;
	sscanf(args[1], "%d", &size);

	for(int i=0; i < size; i++){
		randvalue = rand();
		list.addAtFirst(randvalue);
	}


// 	cout << "D1zialam" <<endl;

// 	list.addAtFirst(5);
// 	list.addAtFirst(10);
// 	list.addAtFirst(11);

// 	list.addAtEnd(33);

// 	list.addAtFirst(121);
// 	list.addAtEnd(3333);

// 	list.addAtIndex(111111, 2);
// 	list.show();
// 	list.deleteAtEnd();
// 	list.deleteAtEnd();
// 	list.deleteAtFirst();
// 	list.deleteAtFirst();

// 	list.deleteAtIndex(6);

// 	cout << "_________________________" << endl;
// 	list.show();

// 	list.searching(10);
// 	list.searching(5);

// 	const char * filename = "DaneTablica.txt";
// 	list.loadDataFromFile(filename);
// 	list.show();
// 	cout << "_________________________" << endl;
// 	list.AddRandomToTesting(5, 0, 1000);
// 	list.show();
// 	cout << endl;
// 	list.deleteAtEnd();
// 	list.deleteAtEnd();
// 	list.show();

// 	cout << "Koniec" <<endl;

	return 0;
}