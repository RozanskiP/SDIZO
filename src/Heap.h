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
private:
	void realloc();
	void deleteStructure();
	void deleteNode();
	void buildByFloydAlgoritm();
	void printBT(std::string sp, std::string sn, int v);
	void heapify(int tab[], int i);
public:
	Heap();
	~Heap();
	void addNode(int value);
	void deleteNodeKey(int elem);
	void searching(int elem);
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
};

#endif /* HEAP_H_ */
