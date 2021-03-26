/*
 * BinarySearchTree.h
 *
 *  Created on: 6 mar 2021
 *      Author: Pawel
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

class BSTNode{
public:
	BSTNode *left;
	BSTNode *right;
	BSTNode *parent;
	int key;
public:
	BSTNode();
	~BSTNode();
};

class BinarySearchTree {
public:
	BSTNode *root;
private:
	BSTNode * poprzednik(BSTNode *node);
	BSTNode * nastepnik(BSTNode *node);
	BSTNode * minimum(BSTNode *node);
	BSTNode * maximum(BSTNode *node);
	void inOrder(BSTNode *node);
	void rightRotation(BSTNode *tempRoot, BSTNode *& root);
	void leftRotation(BSTNode *tempRoot, BSTNode *& root);
	void deleteStructure();
public:
	BinarySearchTree();
	~BinarySearchTree();
	void addNode(int value);
	void deleteNode(int value);
	BSTNode *searching(int value);
	void DSW(); //algorytm rownowazenia drzewa
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
};

#endif /* BINARYSEARCHTREE_H_ */
