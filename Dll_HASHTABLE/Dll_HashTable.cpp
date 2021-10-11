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

Hash::Hash(int size)
{
	Initialize(size);
}

void Hash::Initialize(int size)
{
	this->mnNumIndexes = size;
	table = new list<int>[mnNumIndexes];
}
int Hash::GetHash(int key)
{
	int result = 0;
	result = key % this->mnNumIndexes;
	return result;

}

void Hash::Insert(int key)
{
	int hashedKey = GetHash(key);
	table[hashedKey].push_back(key);
}

void Hash::Remove(int key)
{
	int hashedKey = GetHash(key);
	list<int>::iterator i;
	for (i = table[hashedKey].begin(); i != table[hashedKey].end(); i++)
	{
		if (*i == key)
			break;
	}
	if (i != table[hashedKey].end())
	{
		table[hashedKey].erase(i);
	}
}

void Hash::Display()
{
	for (int i = 0; i < mnNumIndexes; i++) {
		cout << i;
		for (int x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}

HashNode* Hash::Retrieve(int key)
{
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

LinearProbingHashTable::LinearProbingHashTable()
{
	Initialize();
}

void LinearProbingHashTable::Initialize()
{
	mnSize = 0;
	table = new HashNode * [MAXCAP];
	for (int i = 0; i < MAXCAP; i++)
	{
		table[i] = new HashNode(-1, -1);
	}
	dummy = new HashNode(-1, -1);
}


int LinearProbingHashTable::GetHash(int key)
{
	int result = 0;
	result = key % MAXCAP;
	return result;
}


HashNode* LinearProbingHashTable::Insert(int key, int value)
{
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


int LinearProbingHashTable::Retrieve(int key)
{
	int hashIndex = GetHash(key);
	int counter = 0;
	while (table[hashIndex] != NULL)
	{
		if (counter++ > MAXCAP)
			return NULL;

		if (table[hashIndex]->key == key)
		{
			return table[hashIndex]->value;
		}
		hashIndex++;
		hashIndex %= MAXCAP;
	}
	return NULL;
}


int LinearProbingHashTable::Remove(int key)
{
	HashNode* temp = NULL;
	int hashIndex = GetHash(key);
	while (table[hashIndex] != NULL)
	{
		if (table[hashIndex]->key == key)
		{
			temp = table[hashIndex];
			table[hashIndex] = dummy;
			mnSize--;
			return temp->value;
		}
		hashIndex++;
		hashIndex %= MAXCAP;

	}
	return NULL;
}


int LinearProbingHashTable::sizeOfTable()
{
	return mnSize;
}


bool LinearProbingHashTable::isEmpty()
{
	return mnSize == 0;
}


void LinearProbingHashTable::Display()
{
	for (int i = 0; i < MAXCAP; i++)
	{
		if ((table[i] != NULL) && (table[i]->key != -1))
		{
			cout << "key = " << table[i]->key << " value = " << table[i]->value << endl;
		}
	}
}

DoubleHashedHashTable::DoubleHashedHashTable(int size)
{
	Initialize(size);
}
void DoubleHashedHashTable::Initialize(int size)
{
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
	int result = 0;
	result = k % s;
	return result;
}
int DoubleHashedHashTable::Hash2(int k, int s)
{
	int result = 0;
	result = (k * s - 1) %s;
	return result;
}

int DoubleHashedHashTable::SearchKey(int k)
{
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
	int pos = SearchKey(k);
	if (table->tab[pos].info != Legi)
	{
		table->tab[pos].info = Legi;
		table->tab[pos].e = k;
	}
		
}
void DoubleHashedHashTable::Display()
{
	int value = 0;
	for (int i = 0; i < table->s; i++)
	{
		value = table->tab[i].e;
		if (!value)
		{
			cout << "Position: " << i + 1 << " element: NULL" << endl;
		}
		else
		{
			cout << "Position: " << i + 1 << " element: " << value << endl;
		}
	}
}

HashNode* DoubleHashedHashTable::Retrieve(int searchFor)
{
	HashNode* hn = NULL;
	int result = 0;
	int value = 0;
	int hashValue = Hash1(searchFor, table->s);
	int stepSize = Hash2(searchFor, table->s);

	for (int i = 0; i < table->s; i++)
	{
		hashValue = Hash1(i, table->s);
		stepSize = Hash2(i, table->s);

		value = table->tab[hashValue].e;
		if (searchFor == value)
		{
			hn = new HashNode(hashValue+1, value);
			return hn;
		}
		else
		{
			value = table->tab[stepSize].e;
			if (searchFor == value)
			{
				hn = new HashNode(stepSize+1, value);
				return hn;
			}

		}
	}
	hn = new HashNode(-1, -1);
	return hn;
}

void DoubleHashedHashTable::ReHash()
{
	int s = table->s;
	Entry* t = table->tab;

	Initialize(s * 2);

	for (int i = 0; i < s; i++)
	{
		if (t[i].info == Legi)
		{
			Insert(t[i].e);
		}
	}
	delete t;
}