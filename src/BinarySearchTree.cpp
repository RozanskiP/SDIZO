/*
 * BinarySearchTree.cpp
 *
 *  Created on: 6 mar 2021
 *      Author: Pawel
 */

#include "BinarySearchTree.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

BSTNode::BSTNode(){
	left = NULL;
	right = NULL;
	parent = NULL;
	key = 0;
}

BSTNode::~BSTNode(){
	if(this->left != NULL){
		delete this->left;
		this->left = NULL;
	}
	if(this->right != NULL){
		delete this->right;
		this->right = NULL;
	}
}

BinarySearchTree::BinarySearchTree() {
	root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
	deleteStructure();
}

void BinarySearchTree::deleteStructure(){
	if(this->root != NULL){
		delete this->root;
		this->root = NULL; //wazne jesli nie bedzie to wartosc bedzie sie usuwac w nieskonczosnosc
	}
}

void BinarySearchTree::inOrder(BSTNode *node){ //rekurencyjnie
	if(node){
		inOrder(node->left);
		cout << node->key << endl;
		inOrder(node->right);
	}
}

void BinarySearchTree::addNode(int value){
	BSTNode *node = new BSTNode();
	node->key = value; //nadanie wartosci poczatkowych

	BSTNode *temproot = this->root;
	BSTNode *temp2 = NULL;
	while(temproot != NULL){ //sprawdzaj az nie dojdziesz do ostatniego syna w tej galezi
		temp2 = temproot;
		if(node->key < temproot->key){ //jesli mniejszy to na lewo
			temproot = temproot->left;
		}else{
			temproot = temproot->right; //w przeciwnym razie na prawo
		}
	}

	node->parent = temp2; // przypisanie do nowego wezla jego rodzica

	if(temp2 == NULL){	// jesli nie ma elementow zadnych to korzen
		this->root = node;
	}
	else if(temp2->key > node->key){ //jesli jest mniejsza niz wartosc z wezle rodzica to na lewo
		temp2->left = node;
	}else{ // w przeciwnym nazie na prawo
		temp2->right = node;
	}
}

BSTNode * BinarySearchTree::minimum(BSTNode *node){
	if(node == NULL){
		return node;
	}
	while(node->left != NULL){
		node = node->left;
	}
	return node;
}

BSTNode * BinarySearchTree::maximum(BSTNode *node){
	if(node == NULL){
		return node;
	}
	while(node->right != NULL){
		node = node->right;
	}
	return node;
}

BSTNode * BinarySearchTree::nastepnik(BSTNode *node){
	if(node == NULL){ //sprawdza czy drzewo jest puste
		return node;
	}
	if(node->right != NULL){ //pierwszy przypadek jesli ma prawego syna to wtedy wez minimum z tego drzewa
		return minimum(node->right);
	}else{ // 2 i 3 przypadek nie ma prawego syna
		BSTNode *temp = node->parent;
		while(temp->right == node && temp){ //idziemy w gore drzewa az do wtedy kiedy znajdziemy taki wezel
			node = temp;					// ze node lezy w jego lewej galezi
			temp = temp->parent;
		}
		return temp;
	}
}

BSTNode * BinarySearchTree::poprzednik(BSTNode *node){
	if(node == NULL){
		return node;
	}
	if(node->left != NULL){
		return maximum(node->left);
	}else{
		BSTNode *temp = node->parent;
		while(temp->left == node && temp){
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

void BinarySearchTree::deleteNode(BSTNode *& root, int value){
	BSTNode * temp = searching(value);
	//je�li nie ma takiego elementu
	if(temp == NULL){
		return;
	}
	// -1 opcja: nie ma zadnego syna
	if(temp->right == NULL && temp->left == NULL){
		BSTNode * parent = temp->parent;
		if(temp != root){ //jesli nie jest rowny korzeniowy
			if(parent->left == temp){
				parent->left = NULL;
			}else{
				parent->right = NULL;
			}
		}else{
			root = NULL;
		}
		temp->left = NULL;
		temp->right = NULL;
		delete temp;
		return;
	}
	// -2 opcja: posiada jednego syna - lewego
	if(temp->right == NULL && temp->left != NULL){
		BSTNode * parent = temp->parent;
		BSTNode * son = temp->left;
		if(temp != root){
			son->parent = parent;
			if(parent->left == temp){
				parent->left = son;
			}else{
				parent->right = son;
			}
		}else{
			root = son;
		}
		//ustawienie wartosci prawej i lewej na null zeby destruktor nie usunal innych elementow
		temp->left = NULL;
		temp->right = NULL;
		delete temp;
		return;
	}
	// -2 opcja: posiada jednego syna - prawego
	if(temp->right != NULL && temp->left == NULL){
		BSTNode * parent = temp->parent;
		BSTNode * son = temp->right;
		if(temp != root){
			son->parent = parent;
			if(parent->left == temp){
				parent->left = son;
			}else{
				parent->right = son;
			}
		}else{
			root = son;
		}
		temp->left = NULL;
		temp->right = NULL;
		delete temp;
		return;
	}
	// -3 opcja: 2 syn�w
	// naprawienie miejsca skad wzielismy wezle next
	BSTNode * next = nastepnik(temp);
	int val = next->key; //zapisz wartosc
	deleteNode(root, next->key); //zrob rekurencyjnie tak znowu az nie bedizie mial jednego syna
	temp->key = val; //przypisz wartosc
	return;
}

BSTNode * BinarySearchTree::searching(int value){
	BSTNode *node = this->root;

	while(node != NULL){
		if(node->key == value){
			cout << "Znalazlem taki element" << endl;
			return node;
		}else if(node->key > value){
			node = node->left;
		}else{
			node = node->right;
		}
	}
	cout << "Nie ma takiej liczby" << endl;
}

void BinarySearchTree::rightRotation(BSTNode *tempRoot, BSTNode *& root){ //rotacja w prawo potrzebna dla alrogrytmu DSW
	if(tempRoot->left != NULL){
		BSTNode *leftson = tempRoot->left;
		BSTNode *tempRootparent = tempRoot->parent;

		tempRoot->left = leftson->right;
		if(tempRoot->left != NULL){ //jesli istnieje lewa strona to przypisz jej rodzica
			tempRoot->left->parent = tempRoot;
		}
		leftson->right = tempRoot;
		leftson->parent = tempRootparent;
		tempRoot->parent = leftson;

		if(tempRootparent != NULL){
			if(tempRootparent->left == tempRoot){
				tempRootparent->left = leftson;
			}else{
				tempRootparent->right = leftson;
			}
		}else{
			root = leftson;
		}
	}
}

void BinarySearchTree::leftRotation(BSTNode *tempRoot, BSTNode *& root){ //rotacja w lewo potrzebna dla alrogrytmu DSW
	if(tempRoot->right != NULL){
		BSTNode *rightson = tempRoot->right;
		BSTNode *tempRootparent = tempRoot->parent;
		tempRoot->right = rightson->left;

		if(tempRoot->right != NULL){
			tempRoot->right->parent = tempRoot;
		}
		rightson->left = tempRoot;
		rightson->parent = tempRootparent;
		tempRoot->parent = rightson;

		if(tempRootparent != NULL){ //je�li rodzic nie by� korzeniem
			if(tempRootparent->left == tempRoot){ //jesli nasz weze zamieniany byl po lewo
				tempRootparent->left = rightson;
			}else{ //jesli byl po prawo
				tempRootparent->right = rightson;
			}
		}else{ //jesli byl korzeniem
			root = rightson;
		}
	}
}

void BinarySearchTree::DSW(){
	BSTNode *temp = root;
	//Pierwsza czesc utowrzenie kregoslupa
	int count = 0;
	while(temp != NULL){
		if(temp->left != NULL){
			rightRotation(temp, this->root);
			temp = temp->parent;
		}else{
			temp = temp->right;
			++count;
		}
	}

	// druga czesc pierwsze przejscie przez wszystkie
	int m = count + 1 - pow(2, floor(log2(count+1)));

	temp = root;
	for(int i=0;i < m; i++){
		leftRotation(temp, this->root);
		temp = temp->parent->right;
	}

	// przejscie przez  elementy sk�adanie do konca w zalznosci od elenetow
	count = count - m;
	while(count > 1){
		count = count/2;
		temp = root;
		for(int i = 0;i < count; i++){
			leftRotation(temp, this->root);
			temp = temp->parent->right;
		}
	}
}

void BinarySearchTree::loadDataFromFile(const char * filename){
	deleteStructure();
	int sizeFromFile = 0;
	string line;
	ifstream file;

	file.open(filename);

	if(!file){
		cout << "Blad otwarcia pliku" << endl;
	}else{
		getline(file, line);
		sizeFromFile = atoi(line.c_str());
		int i;
		for(i = 0;i < sizeFromFile;i++){
			getline(file, line);
			addNode(atoi(line.c_str()));
		}
	}
}

//https://eduinf.waw.pl/inf/alg/001_search/0113.php
void print(string sp, string sn, BSTNode *& v){ //TODO sa jakies dziwne ascii
	string s;
	string cr, cl, cp;

	cr = cl = cp = "  ";
	cr [0] = 43; cr [1] = 45;
	cl [0] = 45; cl [1] = 43;
	cp [0] = 124	;

	if(v)
	{
		s = sp;
		if( sn == cr ) s [ s.length( ) - 2 ] = ' ';
		print( s + cp, cr, v->right );

		s = s.substr ( 0, sp.length( ) - 2 );

		cout << s << sn << v->key << endl;

		s = sp;
		if( sn == cl ) s [ s.length( ) - 2 ] = ' ';
		print( s + cp, cl, v->left );
	}
}

void BinarySearchTree::show(){
	print("" ,"" , this->root);
}

void BinarySearchTree::AddRandomToTesting(int size, int start, int end){
	deleteStructure();
	srand(time(NULL));

	int randvalue = 0;

	int i;
	for(i = 0;i < size; i++){
		randvalue = rand()%end + start;
		addNode(randvalue);
	}
}

// int main(void){

// 	cout << "Poczatek" <<endl;

// 	BinarySearchTree tree;

// 	tree.addNode(9);
// 	tree.addNode(14);
// 	tree.addNode(5);
// 	tree.addNode(1);

// 	tree.addNode(6);
// 	tree.addNode(11);
// 	tree.addNode(16);
// 	// tree.addNode(7);
// 	// tree.addNode(6);

// 	// tree.addNode(5);
// 	// tree.addNode(10);
// 	// tree.addNode(9);
// 	// tree.addNode(12);
// 	// tree.addNode(11);
// 	// tree.addNode(15);
// 	// tree.addNode(3);
// 	// tree.addNode(14);
// 	// tree.addNode(2);
// 	// tree.addNode(1);
// 	// tree.addNode(6);
// 	// tree.addNode(13);
// 	// tree.addNode(4);
// 	// tree.addNode(8);
// 	// tree.addNode(7);

// 	tree.show();
// 	tree.deleteNode(tree.root , 15);
// 	// tree.deleteNode(tree.root , 1);
// 	// tree.deleteNode(tree.root , 6);
// 	// tree.deleteNode(tree.root , 3);
// 	// tree.deleteNode(tree.root , 15);

// 	cout << "@@@@@@@@@@@@@@@@" << endl;
// 	tree.show();

// 	// tree.addNode(10);
// 	// tree.addNode(9);
// 	// tree.addNode(7);

// 	tree.searching(43);
// 	tree.searching(11);
// 	// tree.addNode(68);
// 	// tree.addNode(77);
// 	// tree.addNode(6);
// 	// tree.addNode(5);
// 	// tree.addNode(2);
// 	// tree.addNode(7);
// 	// tree.addNode(6);
// 	// tree.addNode(1);
// 	// tree.addNode(1);
// 	// tree.addNode(7);
// 	// tree.addNode(2);
// 	// tree.addNode(4);

// 	tree.show();

// 	cout << "-----------------" << endl;

// 	tree.AddRandomToTesting(20, 0, 100);
// 	tree.show();
// 	cout << "%%%%%%%%%%%%%%%%%%%%%" << endl;
// 	tree.loadDataFromFile("DaneTablica.txt");
// 	tree.DSW();
	
// 	tree.show();
	
// 	tree.inOrder(tree.root);

// 	cout << "Koniec" <<endl;
// 	return 0;
// }
