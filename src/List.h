/*
 * List.h
 *
 *  Created on: 5 mar 2021
 *      Author: Pawel
 */

#ifndef LIST_H_
#define LIST_H_

class Node{

public:
	int value;
	Node *next;
	Node *prev;
	Node();
	~Node();
};

class List {
private:
	Node *head;
private:
	void deleteStructure();
	void deleteAtIndex(int index);
public:
	List();
	~List();
	void addAtFirst(int value);
	void addAtEnd(int value);
	void addAtIndex(int value, int index);
	void deleteAtFirst();
	void deleteAtEnd();
	void deleteAtKey(int key);
	Node * searching(int value);
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
};

#endif /* LIST_H_ */
