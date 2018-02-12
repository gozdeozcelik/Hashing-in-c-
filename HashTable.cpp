#include "HashTable.h"
#define SIZE 10 //hash size
HashTable::HashTable()
{
	for (int i = 0; i < SIZE; i++)
	{
		item[i] = NULL;
	}
}
int HashTable::hashCode(hashItem h) {
	return h.EmployeeId%SIZE;
}

void HashTable::insertItem(hashItem h) {
	
	int indx = hashCode(h);
	Node *curr = item[indx];
	Node *prev = NULL;
	while (curr != NULL) {
		if (curr->count < 2) {
			curr->data[curr->count] = h;
			curr->count++;
			return;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	if (prev == NULL) {
		Node *k = new Node();
		k->data[0] = h;
		k->count = 1;
		k->next = NULL;
		item[indx] = k;

	}
	else {
		prev->next = new Node();
		curr = prev->next;
		curr->next = NULL;
		curr->count = 1;
		curr->data[0] = h;


	}

}
//Text filedan veri oku ve hash tablea insert et.
bool HashTable::readTextFile(string fileName) {
	int id, status, selection;
	string name, position;
	float salary;
	ifstream person(fileName, ios::in);
	if(!person.is_open())
		return false;
	//File'dan veri okuma
	while (!person.eof()) {
		person >> id;
		person >> status;
		person >> name;
		person >> position;
		person >> salary;
		hashItem a = hashItem{ id, status, name, position, salary };
		//Ýtemi hash tablosuna insert et
		insertItem(a);

	}
	return true;
}
void HashTable::insertRecord() {
	int id, status;
	string name, position;
	float salary;
	cout << "Enter person id,status,name,position,salary" << endl;
	cin >> id;
	cin >> status;
	cin >> name; 
	cin >> position;
	cin>>salary;
	hashItem a = hashItem{ id, status, name, position, salary };
	//Ýtemi hash tablosuna insert et
	insertItem(a);

}
void HashTable::printHashTable() {

	for (int i = 0; i < SIZE; i++)
	{
		printf("Mode %d : ", i);
		if (item[i] != NULL) { //hash tablosunda eleman varsa ilerle 

			cout << item[i]->data[0].EmployeeId << " "; //hashin ilk elemanýný yazdýr
			if (item[i]->count == 1) { //hash tablosunda tek eleman varsa
				cout << "/ ";

			}
			else { //hash tablosunda iki eleman varsa
				cout << item[i]->data[1].EmployeeId << " ";
			}
		    Node *walk = item[i]->next;
			while (walk != NULL) { // iki elemanlý hash dolmuþsa linked listleride kontrol etmelidir.
				if (walk->count == 1) {
					cout << walk->data[0].EmployeeId << " ";
					cout<<"/";
				}
				else {
					cout << walk->data[0].EmployeeId << " ";
					cout << walk->data[1].EmployeeId << " ";

				}

				walk = walk->next;
			}
		}
		else //hash tablosunda eleman yoksa direk boþ yazýdr devamýna bakma
		{
			cout << "/ ";
		}


		cout << endl;
	}
	
		
}
void HashTable::searchHashTable() {
	hashItem finding;
	int id;
	cout << "Enter id which want to finding:" << endl;
	cin >> id;
	int indx = id%SIZE;
	
	if (item[indx] != NULL) {

		Node *curr = item[indx];
		Node *prev = NULL;
		while (curr != NULL)
		{
			if (curr->count < 2) { //tek eleman vardýr onuda bulmuþtur
				if (curr->data[curr->count].EmployeeId == id) {
					finding = curr->data[curr->count];
					cout << "Id:" << finding.EmployeeId << " Name:" << finding.name << " Salary:" << finding.salary << " Position:" << finding.postion << endl;
					break;
				}
			}
			else  {
				if (curr->data[0].EmployeeId == id) { //iki elamnlýdýr birincide bulmuþtur
					finding = curr->data[0];
					cout << "Id:" << finding.EmployeeId << " Name:" << finding.name << " Salary:" << finding.salary << " Position:" << finding.postion << endl;
					break;
					
				}
				else if(curr->data[1].EmployeeId == id){ //iki elmanlýdýr ikincide bulmuþtur
					finding = curr->data[1];
					cout << "Id:" << finding.EmployeeId << " Name:" << finding.name << " Salary:" << finding.salary << " Position:" << finding.postion << endl;
					break;

				}
				else { //bulamamýþtýr dolayýsýyla linked liste ilerlemek gerekli
					prev = curr;
					curr = curr->next;
				}
				

			}

		}

	}
	cout << "NOT FOUND ITEM" << endl;
	
}
bool HashTable::deleteItem() {
	int id;
	cout << "Enter id which wanted to deleted:" << endl;
	cin >> id;
	int indx = id%SIZE;
	if (item[indx] != NULL) {

		Node *curr = item[indx];
		Node *prev = NULL;
		Node *del = item[indx]->next;
		Node *delprev = item[indx];
		if (curr->next == NULL && curr->count == 1) //linked list yoksa ve hash tablosunda tek elememan varsa
		{
			if (curr->data[0].EmployeeId == id) { //ilk elemanlý hash tablosunda bulunduysa
				curr->count--;
				item[indx] = NULL;
				return true;
			}
			else { //tek elemanlý hash tablosunda bulunmadýysa
				cout << "Item is not found" << endl;
				return false;
			}
		}
		else if (curr->next == NULL && curr->count == 2) {
			if (curr->data[0].EmployeeId == id) {
				curr->data[0] = curr->data[1]; //ikinci itemi sildiðinden emin deðilim
				curr->count--;
				return true;
			}
			else if(curr->data[1].EmployeeId == id){
				curr->count--;
				return true;
			}
		}
		while (curr != NULL) { //linkedListler varsa onlarý kaydýrman gerekli
			if (curr->data[0].EmployeeId == id) {
				curr->data[0] = curr->data[1];
				curr->count--;
				while (del != NULL) {
					if (del->count == 1 && curr==item[indx]->next) {
						if (delprev == item[indx]) {
							curr->data[1] = del->next->data[0];
							del->next->data[0] = del->next->data[1];
							curr->count++;
							del->next->count--;
						}
						else if(delprev!= item[indx] && del->count==1) {
							if (del->next != NULL) {
								del->data[1] = del->next->data[0];
								del->next->data[0] = del->next->data[1];
								del->count++;
								del->next->count--;
							}
							if(del->next==NULL && del->count==0) {
								delprev->next = NULL;
							}
							if(del->next == NULL && del->count == 1) {
								del->data[0] = del->data[1];

							}
							
							
						}
						
						if (del->count == 0) {
							curr->next = NULL;
						}
					}
					else if (del->count == 2) { //linkedliste iki elman varsa
						delprev->data[1] = del->data[0];
						delprev->count++;
						del->data[0] = del->data[1];
						del->count--;
					}
					else if (del->count == 0) {
						delprev->next = NULL;
					}
					del = del->next;
					delprev = delprev->next;
					//curr->curr->next;
				}
				//curr->count--;
				
				return true;
			}
			else if (curr->data[1].EmployeeId == id) {
				curr->count--;
				while (del != NULL) {
					if (del->count == 1) {
						curr->data[1] = del->data[0];
						curr->count++;
						del->count--;
						if (del->count == 0) {
							curr->next = NULL;
						}
					}
					else if (del->count == 2) { //linkedliste iki elman varsa
						curr->data[1] = del->data[0];
						curr->count++;
						
						del->data[0] = del->data[1];
						del->count--;
					}
					else if (del->count == 0) {
						delprev->next = NULL;
					}
					del = del->next;
					delprev = delprev->next;
					curr = curr->next;
				}
				//curr->count--;
				return true;

			}
			curr = curr->next;
			del = del->next;
			delprev = delprev->next;
			

		}
	}
	cout << "NOT FOUND ITEM" << endl;
	return false;

}