/*
 * BinarySearchTree.h
 *
 *  Created on: 6 mar 2021
 *      Author: Pawe�
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
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void deleteStructure();
	void addNode(int value);
	void deleteNode(BSTNode *& root, int value);
	BSTNode *searching(int value);
	void DSW(); //algorytm r�wnowa�enia drzewa
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
	void inOrder(BSTNode *node);
};

#endif /* BINARYSEARCHTREE_H_ */
