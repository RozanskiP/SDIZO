/*
 * Heap.h
 *
 *  Created on: 5 mar 2021
 *      Author: Pawel
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <cstring>
#include <iostream>

class Heap {
public:
	int *tab;
	int size;
	int reallocsize;
public:
	Heap();
	~Heap();
	void deleteStructure();
	void realloc();
	void addNode(int value);
	void deleteNode();
	void deleteNodeKey(int elem);
	void searching(int elem);
	void loadDataFromFile(const char * filename);
	void buildByFloydAlgoritm();
	void show();
	void printBT(std::string sp, std::string sn, int v);
	void AddRandomToTesting(int size, int start, int end);
	void heapify(int tab[], int i);
};

#endif /* HEAP_H_ */
