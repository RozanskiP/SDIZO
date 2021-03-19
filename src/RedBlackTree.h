/*
 * BlackRedTree.h
 *
 *  Created on: 6 mar 2021
 *      Author: Pawel
 */

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <string>

class RedBlackTreeNode{
public:
	int key;
	char color;
	RedBlackTreeNode *parent;
	RedBlackTreeNode *left;
	RedBlackTreeNode *right;
public:
	RedBlackTreeNode();
	~RedBlackTreeNode();
};

class RedBlackTree {
public:
	RedBlackTreeNode *root;
	RedBlackTreeNode *nullLeaf;
private:
	void deleteStructure(RedBlackTreeNode *node);
	void deleteStructureButDoNew(RedBlackTreeNode *node);
	void rightRotation(RedBlackTreeNode *forRotat);
	void leftRotation(RedBlackTreeNode *forRotat);
	void addNodeFixUp(RedBlackTreeNode *& node);
	void deleteNodeFixUp(RedBlackTreeNode *& node);
public:
	RedBlackTree();
	~RedBlackTree();
	void addNode(int value);
	void deleteNode(int value);
	RedBlackTreeNode * searching(int elem);
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
	void print(std::string sp, std::string sn, RedBlackTreeNode * v);
};

#endif /* REDBLACKTREE_H_ */
