#pragma once
#ifndef _NODE_
#define _NODE_
#include <iostream>
#include <string>
using namespace std;

typedef struct hashItem {
	int EmployeeId;
	int key; //status
	string name;
	string postion;
	double salary;
}ElemType;

class Node
{

public:
	Node *next;
	ElemType data[2];
	int count = 0;
	Node() {
		next = NULL;
		count = 0;
	};

};
#endif