#include "pch.h"

#include "Dll_HashTable.h"
#include <list>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
using namespace std;

HashNode::HashNode(int key, int value)
{
	this->key = key;
	this->value = value;
}

Hash::Hash(int size, int debug)
{
	if (debug == 1)
		cout << "Hash::Hash(int " << size << ", int " << debug << ")" << endl;
	Initialize(size, debug);
}

void Hash::Initialize(int size, int debug)
{
	if (debug == 1)
		cout << "Hash::Initialize(int " << size << ", int " << debug << ")" << endl;
	this->mnNumIndexes = size;
	table = new list<int>[mnNumIndexes];
	mnDebug = debug;
}

int Hash::GetHash(int key)
{
	if (mnDebug == 1)
		cout << "Hash::GetHash(int " << key << ")" << endl;
	int result = 0;
	result = key % this->mnNumIndexes;
	return result;

}

void Hash::Insert(int key)
{
	if (mnDebug == 1)
		cout << "Hash::Insert(int " << key << ")" << endl;
	int hashedKey = GetHash(key);
	table[hashedKey].push_back(key);
}

void Hash::Remove(int key)
{
	if (mnDebug == 1)
		cout << "Hash::Remove(int " << key << ")" << endl;
	int hashedKey = GetHash(key);
	int value = 0;
	list<int>::iterator i;
	for (i = table[hashedKey].begin(); i != table[hashedKey].end(); i++)
	{
		if (*i == key)
			break;
	}

	if (i != table[hashedKey].end())
	{
		value = *i;
		cout << "Removed value: " << value << endl;

		table[hashedKey].erase(i);
	}

}

void Hash::Display()
{
	if (mnDebug == 1)
		cout << "Hash::Display()" << endl;
	for (int i = 0; i < mnNumIndexes; i++) {
		cout << i;
		for (int x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}

HashNode* Hash::Retrieve(int key)
{
	if (mnDebug == 1)
		cout << "Hash::Remove(int " << key << ")" << endl;
	HashNode* hn = new HashNode(-1, -1);
	int result = 0;
	int hashedIndex = GetHash(key);
	for (int i = 0; i < table[hashedIndex].size(); i++)
	{
		for (int x : table[hashedIndex])
		{
			if (x == key)
				hn = new HashNode(hashedIndex, x);
		}
	}
	return hn;
}

LinearProbingHashTable::LinearProbingHashTable(int debug)
{
	if (debug == 1)
		cout << "LinearProbingHashTable::LinearProbingHashTable(int " << debug << ")" << endl;

	Initialize(debug);
}

void LinearProbingHashTable::Initialize(int debug)
{
	if (debug == 1)
		cout << "LinearProbingHashTable::Initialize(int " << debug << ")" << endl;

	mnSize = 0;
	table = new HashNode * [MAXCAP];
	for (int i = 0; i < MAXCAP; i++)
	{
		table[i] = new HashNode(-1, -1);
	}
	dummy = new HashNode(-1, -1);
	mnDebug = debug;
}

int LinearProbingHashTable::GetHash(int key)
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::GetHash(int " << key << ")" << endl;

	int result = 0;
	result = key % MAXCAP;
	return result;
}


HashNode* LinearProbingHashTable::Insert(int key, int value)
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::Insert(int " << key << ", int " << value << ")" << endl;

	HashNode* temp = new HashNode(key, value);
	int hashIndex = GetHash(key);

	while ((table[hashIndex] != NULL) && (table[hashIndex]->key != key) && (table[hashIndex]->key != -1))
	{
		hashIndex++;
		hashIndex %= MAXCAP;
	}

	if ((table[hashIndex] == NULL) || (table[hashIndex]->key == -1))
	{
		mnSize++;
	}
	table[hashIndex] = temp;

	return temp;

}

HashNode* LinearProbingHashTable::Retrieve(int key)
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::Retrieve(int " << key << ")" << endl;

	HashNode* hn = NULL;
	int hashIndex = GetHash(key);
	int counter = 0;
	while (table[hashIndex] != NULL)
	{
		if (counter++ > MAXCAP)
			return NULL;

		if (table[hashIndex]->key == key)
		{
			hn = new HashNode(hashIndex, table[hashIndex]->value);
			return hn;
		}
		hashIndex++;
		hashIndex %= MAXCAP;
	}
	return NULL;
}

int LinearProbingHashTable::Remove(int key)
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::Remove(int " << key << ")" << endl;

	HashNode* temp = NULL;
	int hashIndex = GetHash(key);
	while (table[hashIndex] != NULL)
	{
		if (table[hashIndex]->key == key)
		{
			temp = table[hashIndex];
			table[hashIndex] = dummy;
			mnSize--;
			cout << "Removed value: " << temp->value << endl;
			return temp->value;
		}
		hashIndex++;
		hashIndex %= MAXCAP;

	}
	return NULL;
}

int LinearProbingHashTable::sizeOfTable()
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::sizeOfTable()" << endl;

	return mnSize;
}

bool LinearProbingHashTable::isEmpty()
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::isEmpty()" << endl;

	return mnSize == 0;
}

void LinearProbingHashTable::Display()
{
	if (mnDebug == 1)
		cout << "LinearProbingHashTable::Display()" << endl;

	for (int i = 0; i < MAXCAP; i++)
	{
		if ((table[i] != NULL) && (table[i]->key != -1))
		{
			cout << "key = " << table[i]->key << " value = " << table[i]->value << endl;
		}
	}
}

DoubleHashedHashTable::DoubleHashedHashTable(int size, int debug)
{
	if (debug == 1)
		cout << "DoubleHashedHashTable::DoubleHashedHashTable(int " << size << ", int " << debug << ")" << endl;

	Initialize(size, debug);
}
void DoubleHashedHashTable::Initialize(int size, int debug)
{
	if (debug == 1)
		cout << "DoubleHashedHashTable::Initialize(int " << size << ", int " << debug << ")" << endl;

	Table* t = NULL;
	if (size < maxSize)
	{
		cout << "Table size is too small!" << endl;
	}
	else
	{
		t = new Table();
		if (t == NULL)
		{
			cout << "out of space!" << endl;
		}
		else
		{
			t->s = size;
			t->tab = new Entry[t->s];

			if (t->tab == NULL)
			{
				cout << "table is NULL" << endl;
			}
			else
			{
				for (int i = 0; i < t->s; i++)
				{
					t->tab[i].info = Emp;
					t->tab[i].e = NULL;
				}
				table = t;
			}
		}
	}
}

int DoubleHashedHashTable::Hash1(int k, int s)
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::Hash1(int " << k << ", int " << s << ")" << endl;

	int result = 0;
	result = (k % s);
	return result;
}
int DoubleHashedHashTable::Hash2(int k, int s)
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::Hash2(int " << k << ", int " << s << ")" << endl;

	int result = 0;
	result = ((k * s - 1) %s);
	return result;
}

int DoubleHashedHashTable::SearchKey(int k)
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::SearchKey(int " << k << ")" << endl;

	int hashValue = Hash1(k, table->s);
	int stepSize = Hash2(k, table->s);
	while ((table->tab[hashValue].info != Emp) && (table->tab[hashValue].e != k))
	{
		hashValue = hashValue + stepSize;
		hashValue = hashValue % table->s;
	}
	return hashValue;
}

void DoubleHashedHashTable::Insert(int k)
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::Insert(int " << k << ")" << endl;

	int pos = SearchKey(k);
	if (table->tab[pos].info != Legi)
	{
		table->tab[pos].info = Legi;
		table->tab[pos].e = k;
	}
		
}
void DoubleHashedHashTable::Display()
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::Display()" << endl;

	int value = 0;
	for (int i = 0; i < table->s; i++)
	{
		value = table->tab[i].e;
		if (!value)
		{
			cout << "Position: " << i << " element: NULL" << endl;
		}
		else
		{
			cout << "Position: " << i << " element: " << value << endl;
		}
	}
}

HashNode* DoubleHashedHashTable::Retrieve(int searchFor)
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::Retrieve(int " << searchFor << ")" << endl;

	HashNode* hn = NULL;
	int result = 0;
	int value = 0;
	int hashValue = SearchKey(searchFor);

	for (int i = 0; i < table->s; i++)
	{
		hashValue = Hash1(i, table->s);

		value = table->tab[hashValue].e;
		if (searchFor == value)
		{
			hn = new HashNode(hashValue, value);
			return hn;
		}

	}
	hn = new HashNode(-1, -1);
	return hn;
}

void DoubleHashedHashTable::Remove(int value)
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::Remove(int " << value << ")" << endl;

	int result = 0;
	int value2 = 0;
	int hashValue = SearchKey(value);

	for (int i = 0; i < table->s; i++)
	{
		hashValue = Hash1(i, table->s);

		value2 = table->tab[hashValue].e;
		if (value2 == value)
		{
			cout << "Removed value: " << value2 << endl;
			table->tab[hashValue].e = NULL;

		}

	}

}

void DoubleHashedHashTable::ReHash()
{
	if (mnDebug == 1)
		cout << "DoubleHashedHashTable::ReHash()" << endl;

	int s = table->s;
	Entry* t = table->tab;

	Initialize(s * 2, mnDebug);

	for (int i = 0; i < s; i++)
	{
		if (t[i].info == Legi)
		{
			Insert(t[i].e);
		}
	}
	delete t;
}