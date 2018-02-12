#include <iostream>
#include "Node.h"

#include "HashTable.h"
using namespace std;
int main() {
	HashTable ht;
	int id, status, selection;
	string name, position;
	float salary;
	hashItem finding;
	do {
		cout << "--------------MENU--------------"<<endl;
		cout<<"1.Find a record given Employee ID\n2.Delete a record given Employee ID\n3.Insert a new record by reading the record data\n4.Exit"<<endl;
		cin >> selection;
		//SEARCH
		if (selection == 1) {
			 ht.searchHashTable();
			
		}
		//DELETE
		else if (selection == 2) {
			if (ht.deleteItem()) {
				cout << "Successfull:Item is deleted:" << endl;
				ht.printHashTable();

			}
			else {
				cout << "ERROR:Item is not deleted:" << endl;
			}

		}
		//INSERT
		else if (selection == 3) {
			if (ht.readTextFile("studentList.txt")) {
				cout << "Succesfull insertion" << endl;
				ht.printHashTable();
			}
			else
				cout << "ERROR:Unsuccesfull insertion!" << endl;

		}
		else
			cout << "Invalid value:" << endl;
	} while (selection != 4);
	

}