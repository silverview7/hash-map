#include <iostream>
#include <string>
#include <ctime>


using namespace std;

struct person {
	string name;
	int age;
	char gender;
	string phoneNumber;
	person* next = NULL;
};

class HashTable {
public:
	HashTable(int elements);
	~HashTable();
	void insert(string name, int age, char gender, string phoneNumber);
	person search(string name, bool& found);
	person* people;

private:
	int numElements;
	int determineIndex(string name);
};

HashTable::HashTable(const int elements) 
{
	numElements = elements;

	people = new person[numElements];
}

HashTable::~HashTable()
{
	delete[] people;
}

void HashTable::insert(string name, int age, char gender, string phoneNumber)
{
	int indexToInsert = determineIndex(name);
	person* head = &(people[indexToInsert]);
	
	while (head->next != NULL)
		head = head->next;
	
	head->name = name;
	head->age = age;
	head->gender = gender;
	head->phoneNumber = phoneNumber;

	return;
}

int HashTable::determineIndex(string name)
{
	int totalSum = 0;
	int index;

	for (int i = 0; i < name.length(); i++)
	{
		totalSum += int(name[i]);
	}

	index = totalSum % numElements;

	return index;
}

person HashTable::search(string name, bool& found) 
{
	int indexToFind = determineIndex(name);
	person* head = &(people[indexToFind]);
	person thePerson;
	bool cont = true;

	while (head->name != name && cont) 
	{
		if (head->next == NULL)
			cont = false;
		else
			head = head->next;
	}

	found = cont;
	if(found)
		thePerson = *(head);

	return thePerson;
}

bool insertIntoHashTable(HashTable* theTable);
void searchHashTable(HashTable* theTable);


int main()
{
	char choice;
	HashTable* theTable = new HashTable(30);
	while (true)
	{
		
		cout << "Enter a menu option: " << endl
			<< "(i) Insert" << endl << "(s) Search"
			<< endl;

		cin >> choice;

		switch (choice)
		{
		case 'i':
			if(insertIntoHashTable(theTable))
				cout << "Success" << endl;
			break;
		case 's':
			clock_t start;
			double duration;

			start = std::clock();

			/* Your algorithm here */
			searchHashTable(theTable);

			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

			std::cout << "printf: " << duration << '\n';
			
			break;
		default:
			cout << "Enter valid character" << endl;
			break;
		}
	}

	return 0;
}

bool insertIntoHashTable(HashTable* theTable)
{
	string name;
	int age;
	char gender;
	string phoneNumber;

	cout << "Enter name, age, gender, phoneNumber (seperated by spaces)" << endl;
	cin >> name >> age >> gender >> phoneNumber;

	theTable->insert(name, age, gender, phoneNumber);

	return true;
}

void searchHashTable(HashTable* theTable)
{

	string name;
	bool found;
	
	cout << "Enter name to search: ";
	cin >> name;

	person thePerson;

	thePerson = theTable->search(name, found);

	if (found)
	{
		cout << "Found: " << endl
			<< "Name: " << thePerson.name << endl
			<< "Age: " << thePerson.age << endl
			<< "Gender: " << thePerson.gender << endl
			<< "Phone number: " << thePerson.phoneNumber << endl
			<< "============================" << endl << endl;
	}
	else
		cout << "Could not find that person..." << endl;

	return;
}