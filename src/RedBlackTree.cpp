/*
 * BlackRedTree.cpp
 *
 *  Created on: 6 mar 2021
 *      Author: Pawel
 */

#include "RedBlackTree.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

//Node
RedBlackTreeNode::RedBlackTreeNode(){
	key = 0;
	this->color = 'B';
	parent = NULL;
	left = NULL;
	right = NULL;
}

RedBlackTreeNode::~RedBlackTreeNode(){
}

//Tree
RedBlackTree::RedBlackTree() {
	this->nullLeaf = new RedBlackTreeNode();
	this->nullLeaf->left = NULL;
	this->nullLeaf->right = NULL;
	this->nullLeaf->color = 'B';
	this->root = nullLeaf;
}

RedBlackTree::~RedBlackTree() {
	deleteStructure(root);
	if(this->nullLeaf != NULL){
		delete this->nullLeaf;
	}
}

void RedBlackTree::deleteStructure(RedBlackTreeNode *node){
	if(node != nullLeaf){
		// cout << "node2222: " << node->key << endl;
		deleteStructure(node->left);
		deleteStructure(node->right);
		delete node;
	}
}

void RedBlackTree::deleteStructureButDoNew(RedBlackTreeNode *node){
	deleteStructure(node);
	if(this->nullLeaf != NULL){
		delete this->nullLeaf;
	}
	this->nullLeaf = new RedBlackTreeNode();
	this->nullLeaf->left = NULL;
	this->nullLeaf->right = NULL;
	this->nullLeaf->color = 'B';
	this->root = nullLeaf;
}

RedBlackTreeNode *RedBlackTree::minimum(RedBlackTreeNode *node){
	// if(node == this->nullLeaf){ //sprawdza czy drzewo nie jest poste jesli tak to wraca podany wezel
	// 	return node;
	// }
	// while(node->left != nullLeaf){//przechodz cały czas na lewo jesli nie ma prawego to ten jest najmniejszy
	// 	node = node->left;
	// }
	// return node;
	// cout << "MINIMUM1: " << node->key << endl;
	 if( node != this->nullLeaf ){
		while( node->left != this->nullLeaf ) {
			node = node->left;
			// cout << "MINIMUM2: " << node->key << endl;
		}
	}
  	return node;
}

RedBlackTreeNode *RedBlackTree::maximum(RedBlackTreeNode *node){
	if(node == this->nullLeaf){ //sprawdza czy drzewo nie jest poste jesli tak to wraca podany wezel
		return node;
	}
	while(node != this->nullLeaf){ //przechodz cały czas na prawo jesli nie ma prawego to ten jest najwiekszy
		node = node->right;
	}
	return node;
}

RedBlackTreeNode *RedBlackTree::succesor(RedBlackTreeNode *node){
	RedBlackTreeNode * r;

	if( node != this->nullLeaf )
	{
	if( node->right != this->nullLeaf ) return minimum ( node->right );
	else
	{
		r = node->parent;
		while( ( r != this->nullLeaf ) && ( node == r->right ) )
		{
		node = r;
		r = r->parent;
		}
		return r;
	}
	}
	return this->nullLeaf;
}

void RedBlackTree::rightRotation(RedBlackTreeNode *forRotat){
	RedBlackTreeNode *leftson = forRotat->left;
	// cout << "Rotuje w prawo!" << endl;

	if(leftson != this->nullLeaf){
		forRotat->left = leftson->right; // przypisz prawego syna 
		if(leftson->right != this->nullLeaf){ //jesli nie byl rowny zero to przypisz mu rodzica
			leftson->right->parent = forRotat;
		}
		leftson->parent = forRotat->parent; //przypisz do nowego wezla rodzica - rodzica starego wezla

		if (forRotat->parent == nullptr) {//jesli byl korzeniem to korzen zmienia swoja wartosc
			this->root = leftson;
		} else if (forRotat == forRotat->parent->right) {//przypisanie do rodzica czy jest to jego prawy czy lewy syn
			forRotat->parent->right = leftson;
		} else {
			forRotat->parent->left = leftson;
		}

		leftson->right = forRotat; //przypisanie lewego syna do wezla syna
		forRotat->parent = leftson;
	}
}

void RedBlackTree::leftRotation(RedBlackTreeNode *forRotat){
	RedBlackTreeNode *rightson = forRotat->right;
	//cout << "Rotuje w lewo!" << endl;
	if(rightson != this->nullLeaf){
		forRotat->right = rightson->left; // przypisz prawego syna 
		if(rightson->left != this->nullLeaf){ //jesli nie byl rowny zero to przypisz mu rodzica
			rightson->left->parent = forRotat;
		}
		rightson->parent = forRotat->parent; //przypisz do nowego wezla rodzica - rodzica starego wezla
		//cout << "@@@@" << endl;
		if (forRotat->parent == nullptr) { //jesli byl korzeniem to korzen zmienia swoja wartosc
			this->root = rightson;
		} else if (forRotat == forRotat->parent->left) { //przypisanie do rodzica czy jest to jego prawy czy lewy syn
			forRotat->parent->left = rightson;
		} else {
			forRotat->parent->right = rightson;
		}

		rightson->left = forRotat; //przypisanie lewego syna do wezla syna
		forRotat->parent = rightson;
		// show();
		// cout << "!!!!" << endl;
	}
}

void RedBlackTree::addNodeFixUp(RedBlackTreeNode *& node){

	while((node != this->root) && (node->parent->color == 'R')){
		RedBlackTreeNode *temp;
		if(node->parent == node->parent->parent->left){ //sprawdzenie ojciec naszego wezla jest prawym czy lewym synego swojego dziadka
			temp = node->parent->parent->right;
			if(temp->color == 'R'){ //przypadek 1 gdy brat ojca jest czerwony
				temp->color = 'B';	//zamieniamy ojca i stryja na czarne a ojca ocja na czerwony i kontynuujemy 
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				node = node->parent->parent; //w kolejnej petli naszym node jest dziadek
				//cout << "left - 1" << endl;
			}else{
				//przypadek 2,3 gdy brat ojca jest czarny
				if(node == node->parent->right){
					node = node->parent;
					//cout << "left - 2" << endl;
					leftRotation(node);
				}
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				//cout << "left - 3" << endl;
				rightRotation(node->parent->parent);
				break;
			}
		}else{ //jesli jest prawym , wszytkie funkcje tak samo ze zmiana na prawy (symetrycznie)
			temp = node->parent->parent->left;
			if(temp->color == 'R'){ //przypadek 1 gdy brat ojca jest czerwony
				temp->color = 'B';
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				node = node->parent->parent;
				//cout << "right - 1" << endl;
			}else{
				//przypadek 2,3 gdy brat ojca jest czarny
				if(node == node->parent->left){
					node = node->parent;
					//cout << "right - 2" << endl;
					rightRotation(node);
				}
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				//cout << "right - 3" << endl;
				leftRotation(node->parent->parent);
				break;
			}
		}
	}
	this->root->color = 'B';
}

void RedBlackTree::addNode(int value){
	RedBlackTreeNode *node = new RedBlackTreeNode();
	node->key = value;
	node->left = nullLeaf;
	node->right = nullLeaf;
	node->parent = this->root;
	
	RedBlackTreeNode *temproot = this->root;
	RedBlackTreeNode *temp = NULL;
	
	while(temproot != this->nullLeaf){
		temp = temproot;
		if(node->key < temproot->key){
			temproot = temproot->left;
		}else{
			temproot = temproot->right;
		}
	}
	node->parent = temp;

	if(temp == NULL){
		this->root = node;
	}else if(temp->key > node->key){
		temp->left = node;
	}else{
		temp->right = node;
	}
	if(node->parent == NULL){ //jesli jest korzeniem to nie musi juz naprawiac
		node->color = 'B';
		return;
	}
	node->color = 'R';
	addNodeFixUp(node);
}

void RedBlackTree::deleteNodeFixUp(RedBlackTreeNode *& node){ //ZAPODOBNE
	// cout << "Naprawiam!" << endl;
	RedBlackTreeNode *brother;
	while(node != this->root && node->color == 'B'){
		if(node == node->parent->left){ // przypadki gdy nasz wezel jest lewym synem
			brother = node->parent->right; //przypisujemy do zmiennej brother wartosc brata naszego wezla
			//1 przypadek gdy brat (brother) jest czerwony
			if(brother->color == 'R'){
				brother->color = 'B'; //zamiana kolorów
				node->parent->color = 'R';
				leftRotation(node->parent); //rotacja w lewo
				brother = node->parent->right; //przypisanie nowej wartosci dla kolejnych obliczen 
			}
			//2 przypadek gdy brat (brother) jest czarny i jego synowie tez sa czarnii
			if(brother->left->color == 'B' && brother->right->color == 'B'){
				brother->color = 'R'; //zmiana koloru na czerwony
				node = node->parent; //przesuniecie wartosci node do rodzica i wykonanie kolejnej petli
				continue;
			}
			//3 przypadek brat (brother) jest czarny lewy syn jest czerwony a prawy jest czarny
			if(brother->right->color == 'B'){
				brother->left->color = 'B'; //zmiana koloru  lewego syna na czarny
				brother->color = 'R'; // zmiana koloru brata na czerwony
				rightRotation(brother); //rotacja prawostronan
				brother = node->parent->right;  //nowa wartosc brata 
			} // przekstalcenie naszego przypadku 3 na przypadek 4 i tutaj go dopiero zmieniamy
			//4 przypadek brat (brother) jest czarny a jego prawy syn jest czerwony
			brother->color = node->parent->color;
			node->parent->color = 'B';
			brother->right->color= 'B';
			leftRotation(node->parent);
			node = this->root; // ten warunek zakonczy nasza petle
		}else{// przypadki (lustrzane / symetryczne) gdy nasz wezel jest prawym synem
			brother = node->parent->left; //przypisujemy do zmiennej brother wartosc brata naszego wezla
			//1 przypadek gdy brat (brother) jest czerwony
			if(brother->color == 'R'){
				brother->color = 'B'; //zamiana kolorów
				node->parent->color = 'R';
				rightRotation(node->parent); //rotacja w lewo
				brother = node->parent->left; //przypisanie nowej wartosci dla kolejnych obliczen 
			}
			//2 przypadek gdy brat (brother) jest czarny i jego synowie tez sa czarnii
			if(brother->left->color == 'B' && brother->right->color == 'B'){
				brother->color = 'R'; //zmiana koloru na czerwony
				node = node->parent;
				continue;
			}
			//3 przypadek brat (brother) jest czarny lewy syn jest czerwony a prawy jest czarny
			if(brother->left->color == 'B'){
				brother->right->color = 'B';
				brother->color = 'R';
				leftRotation(brother);
				brother = node->parent->left;
			}
			//4 przypadek brat (brother) jest czarny a jego prawy syn jest czerwony
			brother->color = node->parent->color;
			node->parent->color = 'B';
			brother->left->color= 'B';
			rightRotation(node->parent);
			node = this->root;
		}
	}
}

void RedBlackTree::deleteNode(int value){
	RedBlackTreeNode *node = searching(value);
	if(node == NULL || node == this->nullLeaf){
		return;
	}
	if(node == this->root && node->left == this->nullLeaf && node->right == this->nullLeaf){ //przypadek z korzeniem
		delete node;
		this->root = this->nullLeaf;
		return;
	}

	if(node == this->root && node->left->left == this->nullLeaf && node->left->right == this->nullLeaf && node->right == this->nullLeaf)  { //warunki do naprawienia
		delete node->left;
		this->root->left = this->nullLeaf;
		return;
	} // gdy ma 2 wartosci jedna po lewej stronie i probuje usunac wartosc z wezla 

	if(node == this->root && node->right->left == this->nullLeaf && node->right->right == this->nullLeaf && node->left == this->nullLeaf)  { //warunki do naprawienia
		delete node->right;
		this->root->right = this->nullLeaf;
		return;
	}// gdy ma 2 wartosci jedna po prawej stronie i probuje usunac wartosc z wezla

	RedBlackTreeNode *temp;
	RedBlackTreeNode *tempToChange;

	if((node->left == this->nullLeaf) || (node->right == this->nullLeaf)){ // 1 i 2 przypadek kiedy zastepujemy usuwany wezel wezlem dzieckiem lewym albo prawym
		temp = node; // zapisujemy ktory to ma byc, obejmuje tez przypadek kiedy nie ma zadnego syna wtedy go usuwa i dalej w to miejsce wezel nullleaf
	}else{
		temp = succesor(node); // w przeciwnym przypadku będzie usuwany nastepnik naszego wezla
	}
	
	if(temp->left != this->nullLeaf){ // jesli ma 2 synow to sprawdzamy czy to prawy czy lewy syn do zamiany
		tempToChange = temp->left;
	}else{
		tempToChange = temp->right;
	}

	tempToChange->parent = temp->parent; //zamieniamy ojca wezla ktory bedziemy przenosic  na ojca ktorego mial wezel do usuniecia
	
	if(temp->parent == this->nullLeaf){ // jesli byly 2 elementy to teraz nowym rootem bedziesz nasz wezel nastepnik
		this->root = tempToChange;
	}else if(temp == temp->parent->left){ //jezeli byl jego lewym dzieckiem to bedzie znowu lewym
		temp->parent->left = tempToChange;
	}else{								// w przeciwym wypadku bedzie tak samo jak wczesniej prawym synem
		temp->parent->right = tempToChange; 
	}
	
	if(temp != node){ // jesli nie jest rowny poprzednikowi to daj zmien na nowa wartosc
		node->key = temp->key;
	}
	if(temp->color == 'B'){ // jesli zmieniony wezel ma color czarny to musimy naprawiac
		deleteNodeFixUp(tempToChange);	
	}
	tempToChange->color = 'B';
	delete temp;
}

RedBlackTreeNode * RedBlackTree::searching(int elem){
	RedBlackTreeNode *node = this->root;

	while(node != this->nullLeaf){
		if(node->key == elem){
			cout << "Znalazlem taki element: " << node->key << endl;
			return node;
		}else if(node->key > elem){
			node = node->left;
			// cout << "node left: " << node->key << endl;
		}else{
			node = node->right;
			// cout << "node right: " << node->key << endl;
		}
	}
	cout << "Nie ma takiego elementu o wartosci: " << elem << endl;
	return NULL;
}

void RedBlackTree::loadDataFromFile(const char * filename){
	deleteStructureButDoNew(this->root);
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

void RedBlackTree::show(){
	print("" ,"" , root);
}

void RedBlackTree::AddRandomToTesting(int size, int start, int end){
	deleteStructureButDoNew(this->root);
	srand(time(NULL));

	int randvalue = 0;
	int i;
	for(i = 0;i < size; i++){
		randvalue = rand()%end + start;
		// cout << "Wartosc: " << randvalue << endl;
		addNode(randvalue);
	}
}

//https://eduinf.waw.pl/inf/alg/001_search/0113.php
void RedBlackTree::print(std::string sp, std::string sn, RedBlackTreeNode * v){ //TODO sa jakies dziwne ascii
	string s;
	string cr, cl, cp;

	cr = cl = cp = "  ";
	cr [0] = 43; cr [1] = 45;
	cl [0] = 45; cl [1] = 43;
	cp [0] = 124;

	if(v != nullLeaf)
	{
		s = sp;
		if( sn == cr ) s [ s.length( ) - 2 ] = ' ';
		print( s + cp, cr, v->right );

		s = s.substr ( 0, sp.length( ) - 2 );

		cout << s << sn << v->color << ":" << v->key << endl;

		s = sp;
		if( sn == cl ) s [ s.length( ) - 2 ] = ' ';
		print( s + cp, cl, v->left );
	}
}

// int main(void){
// 	cout << "Zaczynam" << endl;

// 	//cout << "┌ │ └  ─" << endl;
// 	RedBlackTree RBTree;


// 	srand(time(NULL));
// 	int randvalue = 0;
// 	int size = 1000000;

// 	for(int i = 0; i < size; i++){
// 		RBTree.addNode(i);
// 	}
// 	// RBTree.show();
// 	for(int i = size-1; i >= 0; i--){
// 		RBTree.deleteNode(i);
// 	}

// // 3 25 14 29 10 
// 	RBTree.addNode(3);
// 	RBTree.addNode(25);
	// RBTree.addNode(14);
	// RBTree.addNode(29);
	// RBTree.addNode(10);
// // 17 23 2 11 1 
// 	RBTree.addNode(17);
// 	RBTree.addNode(23);
// 	RBTree.addNode(2);
// 	RBTree.addNode(11);
// 	RBTree.addNode(1);
// // 15 16 21 6 8 
// 	RBTree.addNode(15);
// 	RBTree.addNode(16);
// 	RBTree.addNode(21);
// 	RBTree.addNode(6);
// 	RBTree.addNode(8);
// // 20 27 24 4 5 
// 	RBTree.addNode(20);
// 	RBTree.addNode(27);
// 	RBTree.addNode(24);
// 	RBTree.addNode(4);
// 	RBTree.addNode(5);
// // 22 7 13 9 26 
// 	RBTree.addNode(22);
	// RBTree.addNode(7);
	// RBTree.addNode(13);
	// RBTree.addNode(9);
	// RBTree.addNode(26);
// // 28 12 30 18 19
// 	RBTree.addNode(28);
// 	RBTree.addNode(12);
// 	RBTree.addNode(30);
// 	RBTree.addNode(18);
// 	RBTree.addNode(19);


// 	RBTree.show();
	// RBTree.searching(14);
	// RBTree.searching(29);
// 	// RBTree.searching(7);
 
// // 18 10 2 13 3
	// RBTree.show();
	// cout << "-----------------" << endl;
	// RBTree.deleteNode(14);
	// RBTree.show();
	// cout << "-----------------" << endl;
	// RBTree.deleteNode(10);
	// RBTree.show();
	// cout << "-----------------" << endl;
	// RBTree.deleteNode(29);
	// RBTree.show();
// 	RBTree.deleteNode(13);
// 	RBTree.deleteNode(3);
// // 5 29 9 30 6 
// 	RBTree.deleteNode(5);
// 	RBTree.deleteNode(29);
// 	RBTree.deleteNode(9);
	
// 	// RedBlackTreeNode *numb7 = RBTree.searching(7);
// 	// cout << "numb7->left->key: " << numb7->left->key << endl;
// 	// cout << "numb7->left->right->key: " << numb7->left->right->key << endl;

// 	// cout << "SZUKAM: " << endl;
// 	// RBTree.show();
// 	RBTree.deleteNode(30);
// 	RBTree.deleteNode(6);
// // 19 28 26 25 21 
// 	RBTree.deleteNode(19);
// 	RBTree.deleteNode(28);
// 	RBTree.deleteNode(26);
// 	RBTree.deleteNode(25);
// 	RBTree.deleteNode(21);
// // 7	
// 	RBTree.deleteNode(7);
	

	

	// RBTree.show();

	//const char * filename = "DaneTablica.txt";

	//RBTree.loadDataFromFile(filename);

	//RBTree.show();

	// RBTree.AddRandomToTesting(1000, -10000, 10000);

	//RBTree.show();

// 	cout << "Koncze" << endl;

// 	return 0;
// }
