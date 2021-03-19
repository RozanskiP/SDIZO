/*
 * BlackRedTree.cpp
 *
 *  Created on: 6 mar 2021
 *      Author: Pawe�
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

void RedBlackTree::rightRotation(RedBlackTreeNode *forRotat){
	RedBlackTreeNode *leftson = forRotat->left;
	// cout << "Rotuje w prawo!" << endl;
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

void RedBlackTree::leftRotation(RedBlackTreeNode *forRotat){
	RedBlackTreeNode *rightson = forRotat->right;
	//cout << "Rotuje w lewo!" << endl;
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
	node->parent = NULL;
	node->color = 'R';
	
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
	if(node->parent->parent == NULL){
		return;
	}
	addNodeFixUp(node);
}

void RedBlackTree::deleteNodeFixUp(RedBlackTreeNode *& node){

}

void RedBlackTree::deleteNode(int value){

}

RedBlackTreeNode * RedBlackTree::searching(int elem){
	RedBlackTreeNode *node = this->root;

	while(node != this->nullLeaf){
		if(node->key == elem){
			cout << "Znalazlem taki element" << endl;
			return node;
		}else if(node->key > elem){
			node = node->left;
		}else{
			node = node->right;
		}
	}
	cout << "Nie ma takiego elementu" << endl;
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

int main(void){
	cout << "Zaczynam" << endl;

	//cout << "┌ │ └  ─" << endl;
	RedBlackTree RBTree;

	// RBTree.addNode(12);
	// RBTree.addNode(6);
	// RBTree.addNode(12);
	// RBTree.addNode(3);
	// RBTree.addNode(9);
	// RBTree.addNode(9);
	// RBTree.addNode(21);
	// RBTree.addNode(21);

	//RBTree.show();

	//const char * filename = "DaneTablica.txt";

	//RBTree.loadDataFromFile(filename);

	//RBTree.show();

	RBTree.AddRandomToTesting(1000000, -10000, 10000);

	//RBTree.show();

	cout << "Koncze" << endl;

	return 0;
}
