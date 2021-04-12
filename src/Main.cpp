/*
 * Main.cpp
 *
 *  Created on: 15 mar 2021
 *      Author: Pawel
 */
#include <iostream>
#include <stdlib.h>
#include <string>

#include "Table.h"
#include "Table.h"
#include "List.h"
#include "Heap.h"
#include "BinarySearchTree.h"
#include "RedBlackTree.h"


using namespace std;

void displayMenu(string info){
	cout << endl,
	cout << info <<endl,
	cout << "1 <- Wczytaj dane z pliku."<<endl,
	cout << "2 <- Usun."<<endl;
	cout << "3 <- Dodaj."<<endl;
	cout << "4 <- Znajdz."<<endl;
	cout << "5 <- Utworz losowo."<<endl;
	cout << "6 <- Wyswietl."<<endl;
	cout << "7 <- Test(pomiary czasow)."<<endl;
	cout << "0 <- Powrot do menu glownego"<<endl;
	cout << "Podaj opcje: ";
}

void displayMenuBST(string info){
	cout << endl,
	cout << info <<endl,
	cout << "1 <- Wczytaj dane z pliku."<<endl,
	cout << "2 <- Usun."<<endl;
	cout << "3 <- Dodaj."<<endl;
	cout << "4 <- Znajdz."<<endl;
	cout << "5 <- Utworz losowo."<<endl;
	cout << "6 <- Wyswietl."<<endl;
	cout << "7 <- Równoważenie drzewa."<<endl;
	cout << "8 <- Test(pomiary czasow)."<<endl;
	cout << "0 <- Powrot do menu glownego"<<endl;
	cout << "Podaj opcje: ";
}

Table table;

void menuTable(){
	char opt;
	char filename[50];
	int index;
	int value;

	do{
		displayMenu(" -->MENU TABLICA<-- ");
		cin >> opt;
		cout << endl;

		switch(opt){
			case '1': //wczytywanie elementow z pliku
				cout << "Podaj nazwe pliku: ";
				cin >> filename;
				table.loadDataFromFile(filename);
				table.show();
				break;
			case '2': //usuwanie elementu
				cout << "Podaj index: ";
				cin >> index;
				table.deleteAtIndex(index);
				table.show();
				break;
			case '3': //dodawanie elemntu
				cout << "Podaj wartosc: ";
				cin >> value;
				cout << "Podaj index: ";
				cin >> index;
				table.addAtIndex(value, index);
				table.show();
				break;
			case '4': //wyszukiwanie elemnetu
				cout << "Podaj wartosc: ";
				cin >> value;
				table.searching(value);
				break;
			case '5': //generowanie elementow
				cout << "Podaj ilosc elemenow tablicy: ";
				cin >> value;
				table.AddRandomToTesting(value, 0, 1000);
				table.show();
				break;
			case '6': //wyswietlanie lementow
				table.show();
				break;
			case '7': //pomiary czasow
				break;
		}
	}while(opt != '0');
}

List list;

void menuList(){
	char opt;
	char filename[50];
	int index;
	int value;

	do{
		displayMenu(" -->MENU LISTA<-- ");
		cin >> opt;
		cout << endl;
		Node * node;

		switch(opt){
			case '1': //wczytywanie elementow z pliku
				cout << "Podaj nazwe pliku: ";
				cin >> filename;
				list.loadDataFromFile(filename);
				list.show();
				break;
			case '2': //usuwanie elementu
				cout << "Podaj wartosc do usuniecia: ";
				cin >> value;
				list.deleteAtKey(value);
				list.show();
				break;
			case '3': //dodawanie elemntu
				cout << "Podaj wartosc: ";
				cin >> value;
				cout << "Podaj index: ";
				cin >> index;
				list.addAtIndex(value, index);
				list.show();
				break;
			case '4': //wyszukiwanie elemnetu
				cout << "Podaj wartosc: ";
				cin >> value;
				node = list.searching(value);
				if(node == NULL){
					cout << "W liście nie ma takiego elementu"<< endl;
				}else{
					cout << "W liście znajduje sie taki element"<< endl;
				}
				break;
			case '5': //generowanie elementow
				cout << "Podaj ilosc elemenow tablicy: ";
				cin >> value;
				list.AddRandomToTesting(value, 0, 1000);
				list.show();
				break;
			case '6': //wyswietlanie lementow
				list.show();
				break;
			case '7': //pomiary czasow
				break;
		}
	}while(opt != '0');
}

Heap heap;

void menuHeap(){ //todo blad w wyswietlaniu
	char opt;
	char filename[50];
	int index;
	int value;

	do{
		displayMenu(" -->MENU KOPIEC<-- ");
		cin >> opt;
		cout << endl;

		switch(opt){
			case '1': //wczytywanie elementow z pliku
				cout << "Podaj nazwe pliku: ";
				cin >> filename;
				heap.loadDataFromFile(filename);
				heap.show();
				break;
			case '2': //usuwanie elementu
				cout << "Podaj wartosc: ";
				cin >> value;
				heap.deleteNodeKey(value);
				heap.show();
				break;
			case '3': //dodawanie elemntu
				cout << "Podaj wartosc: ";
				cin >> value;
				heap.addNode(value);
				heap.show();
				break;
			case '4': //wyszukiwanie elemnetu
				cout << "Podaj wartosc: ";
				cin >> value;
				heap.searching(value);
				heap.show();
				break;
			case '5': //generowanie elementow
				cout << "Podaj ilosc elemenow tablicy: ";
				cin >> value;
				heap.AddRandomToTesting(value, 0, 1000);
				heap.show();
				break;
			case '6': //wyswietlanie lementow
				heap.show();
				break;
			case '7': //pomiary czasow
				break;
		}
	}while(opt != '0');
}

BinarySearchTree bst;

void menuBinarySearchTree(){
	char opt;
	char filename[50];
	int index;
	int value;

	do{
		displayMenuBST(" -->MENU BST<-- ");
		cin >> opt;
		cout << endl;

		switch(opt){
			case '1': //wczytywanie elementow z pliku
				cout << "Podaj nazwe pliku: ";
				cin >> filename;
				bst.loadDataFromFile(filename);
				bst.show();
				break;
			case '2': //usuwanie elementu
				cout << "Podaj wartosc: ";
				cin >> value;
				bst.deleteNode(value);
				bst.show();
				break;
			case '3': //dodawanie elemntu
				cout << "Podaj wartosc: ";
				cin >> value;
				bst.addNode(value);
				bst.show();
				break;
			case '4': //wyszukiwanie elemnetu
				cout << "Podaj wartosc: ";
				cin >> value;
				bst.searching(value);
				break;
			case '5': //generowanie elementow
				cout << "Podaj ilosc elemenow tablicy: ";
				cin >> value;
				bst.AddRandomToTesting(value, 0, 1000);
				bst.show();
				break;
			case '6': //wyswietlanie lementow
				bst.show();
				break;
			case '7': //równowazenie drzewa
				bst.DSW();
				bst.show();
				break;
			case '8': //pomiary czasow
				break;
		}
	}while(opt != '0');

}

RedBlackTree rbt;

void menuBlackReadTree(){
	char opt;
	char filename[50];
	int index;
	int value;

	do{
		displayMenu(" -->MENU RBT<-- ");
		cin >> opt;
		cout << endl;

		switch(opt){
			case '1': //wczytywanie elementow z pliku
				cout << "Podaj nazwe pliku: ";
				cin >> filename;
				rbt.loadDataFromFile(filename);
				rbt.show();
				break;
			case '2': //usuwanie elementu
				cout << "Podaj wartosc: ";
				cin >> value;
				rbt.deleteNode(value);
				rbt.show();
				break;
			case '3': //dodawanie elemntu
				cout << "Podaj wartosc: ";
				cin >> value;
				rbt.addNode(value);
				rbt.show();
				break;
			case '4': //wyszukiwanie elemnetu
				cout << "Podaj wartosc: ";
				cin >> value;
				rbt.searching(value);
				rbt.show();
				break;
			case '5': //generowanie elementow
				cout << "Podaj ilosc elemenow tablicy: ";
				cin >> value;
				rbt.AddRandomToTesting(value, 0, 1000);
				rbt.show();
				break;
			case '6': //wyswietlanie lementow
				rbt.show();
				break;
			case '7': //pomiary czasow
				break;
		}
	}while(opt != '0');
}

int main(void){

	char choose;

	do{
		cout << endl;
		cout << "		MENU GLOWNE" <<endl;
		cout << "1 <- Tablica" <<endl;
		cout << "2 <- Lista" <<endl;
		cout << "3 <- Kopiec binarny" <<endl;
		cout << "4 <- Drzewo przeszukiwan binarnych" <<endl;
		cout << "5 <- Drzewo czerwono-czarne" <<endl;
		cout << "0 <- Wyjscie z programu" <<endl;
		cout << "Podaj opcje: ";
		cin >> choose;

		switch(choose){
		case '1':
			menuTable();
			break;
		case '2':
			menuList();
			break;
		case '3':
			menuHeap();
			break;
		case '4':
			menuBinarySearchTree();
			break;
		case '5':
			menuBlackReadTree();
			break;
		}
	}while(choose != '0');

	return 0;
}
