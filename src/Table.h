/*
 * Table.h
 *
 *  Created on: 5 mar 2021
 *      Author: Pawel
 */

#ifndef TABLE_H_
#define TABLE_H_

class Table {
public:
	int *table;
	int size;
private:
	void deleteStructure();
	void resize(int newSize);
public:
	Table();
	~Table();
	void addAtFirst(int elem);
	void addAtEnd(int elem);
	void addAtIndex(int elem, int index);
	void deleteAtFirst();
	void deleteAtEnd();
	void deleteAtKey(int value);
	void searching(int elem);
	void loadDataFromFile(const char * filename);
	void show();
	void AddRandomToTesting(int size, int start, int end);
};

#endif /* TABLE_H_ */
