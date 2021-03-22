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
	virtual ~Node();
};

class List {
private:
	Node *head;
public:
	List();
	virtual ~List();
	void deleteStructure();
	void addAtFirst(int value);
	void addAtEnd(int value);
	void addAtIndex(int value, int index);
	void deleteAtFirst();
	void deleteAtEnd();
	void deleteAtIndex(int index);
	void searching(int value);
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
};

#endif /* LIST_H_ */
