#pragma once
#include "Node.h"
#include <iostream>
#include<string>
using namespace std;
#include <fstream>

class HashTable
{
	Node *item[10];
public:
	HashTable();
	void insertItem(hashItem h);
	int hashCode(hashItem h);
	void insertRecord();
	bool readTextFile(string name);
	void printHashTable();
	void searchHashTable();
	bool deleteItem();

	
};

