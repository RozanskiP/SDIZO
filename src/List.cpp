/*
 * List.cpp
 *
 *  Created on: 5 mar 2021
 *      Author: Pawel
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
	Node *node = new Node(); //towrzymy nowe element
	node->next = head;	// przypisujemy stary element głowy do naszego elementu
	node->prev = NULL;	// nasz element bedzie teraz głowa czyli nie bedzie mial poprzedniego

	if(head){ // jezeli mielismy glowe wczesniej czyli nie byla zerowa tablica 
		head->prev = node; //to przypisujemy do glowy wartosc poprzednia czyli nasz element
	}
	head = node; // zmienaimy wartosc w polu klasy head na node
	node->value = value; //przypisujemy wartosc
}

void List::addAtEnd(int value){
	Node * node = new Node();
	node->value = value;
	node->next = NULL;
	if(this->head == NULL){
		this->head = node;
		return;
	}
	Node* temp = this->head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	
	temp->next = node;
	node->prev = temp;
}

void List::addAtIndex(int value, int index){
	if(index <= 0){
		addAtFirst(value);
		return;
	}
	Node *temp = head;
	Node * node = new Node();
	node ->value = value;
	int i = 0;
	
	while(temp != NULL){
		if(temp->next == NULL){
			temp->next = node;
			node->prev = temp;
			return;
		}
		if(i == index){
			temp->prev->next = node;
			node->next = temp;
			node->prev = temp->prev;
			temp->prev = node;
			return;
		}
		i++;
		temp = temp->next;
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
		if(lastnode->next == NULL){
			return;
		}
		while(lastnode->next != NULL){
			lastnode = lastnode->next;
		}
		temp = lastnode;
		lastnode = lastnode->prev;
		lastnode->next = NULL;
		delete temp;
	}
}

void List::deleteAtKey(int key){
	Node *temp = head;
	while(temp != NULL){
		if(temp->value == key){
			if(temp == head){
				head = temp->next;
			}
			if(temp->next != NULL){
				temp->next->prev = temp->prev;
			}
			if(temp->prev != NULL){
				temp->prev->next = temp->next;
			}
			delete temp;
			break;
		}
		temp = temp->next;
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

Node *List::searching(int value){
	Node *temp = head;
	while(temp != NULL){
		if(temp->value == value){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void List::loadDataFromFile(const char * filename){
	string line;
	ifstream file;

	file.open(filename);
	
	if(!file){
		cout << "Blad otwarcia pliku" << endl;
	}else{
		deleteStructure();
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
			Node* temp = head;
			while(temp->next != NULL){
				temp = temp->next;
			}
			node->value = tempvalue;
			node->next = NULL;
			temp->next = node;
			node->prev = temp;
			i++;
		}
	}
}

void List::show(){
	Node * node = head;
	if(!node){
		cout << "Lista jest pusta" <<endl;
	}else{
		int counter=0;
		cout << "Od przodu: " << endl;
		while(node){
			cout  << node->value <<" ";
			node = node->next;
			counter++;
		}
		cout << endl;
		cout << "Od tyłu: " << endl;
		node = head;
		counter--;
		while(counter != 0){
			node = node->next;
			counter--;
		}
		while(node){
			cout  << node->value <<" ";
			node = node->prev;
		}
		cout << endl;
	}
}

// int main(int argc, char **args){

// 	List list;

// 	srand(time(NULL));
// 	int randvalue = 0;
// 	int index = 0;
// 	int size = 10;
// 	sscanf(args[1], "%d", &size);

// 	for(int i=0; i < size; i++){
// 		randvalue = rand();
// 		list.addAtFirst(randvalue);
// 	}

// 	// for(int i=0; i < 1000; i++){
// 	// 	randvalue = rand();
// 	// 	list.searching(randvalue);
// 	// }

// 	return 0;
// }

int main(int argc, char **args){

	List list;

	srand(time(NULL));
	int randvalue = 0;
	int index = 0;
	int size;
	sscanf(args[1], "%d", &size);

	for(int i=0; i < size;){
		randvalue = rand();
		list.addAtIndex(randvalue, index);
		i++;
		index = rand() % i;
	}

	return 0;
}


// // 	cout << "D1zialam" <<endl;

// // 	list.addAtFirst(5);
// // 	list.addAtFirst(10);
// // 	list.addAtFirst(11);

// // 	list.addAtEnd(33);

// // 	list.addAtFirst(121);
// // 	list.addAtEnd(3333);

// // 	list.addAtIndex(111111, 2);
// // 	list.show();
// // 	list.deleteAtEnd();
// // 	list.deleteAtEnd();
// // 	list.deleteAtFirst();
// // 	list.deleteAtFirst();

// // 	list.deleteAtIndex(6);

// // 	cout << "_________________________" << endl;
// // 	list.show();

// // 	list.searching(10);
// // 	list.searching(5);

// // 	const char * filename = "DaneTablica.txt";
// // 	list.loadDataFromFile(filename);
// // 	list.show();
// // 	cout << "_________________________" << endl;
// // 	list.AddRandomToTesting(5, 0, 1000);
// // 	list.show();
// // 	cout << endl;
// // 	list.deleteAtEnd();
// // 	list.deleteAtEnd();
// // 	list.show();

// // 	cout << "Koniec" <<endl;
