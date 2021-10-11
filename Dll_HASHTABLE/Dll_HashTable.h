#pragma once

#ifdef DLLHASHTABLE_EXPORTS
#define DLLHashTable_API __declspec(dllexport)
#else
#define DLLHashTable_API __declspec(dllimport)
#endif

#include <iostream>
#include <list>
using namespace std;

class HashNode
{
	public:
		int key;
		int value;
		DLLHashTable_API HashNode(int key, int value);
};

class Hash
{
	public:
		DLLHashTable_API Hash(int size);
		DLLHashTable_API void Initialize(int size);
		DLLHashTable_API int GetHash(int key);
		DLLHashTable_API void Insert(int key);
		DLLHashTable_API void Remove(int key);
		DLLHashTable_API void Display();
		DLLHashTable_API HashNode* Retrieve(int key);
private:
		list<int>* table;
		int mnNumIndexes;
};

class LinearProbingHashTable
{
	// LINEAR PROBING implementation

	// Public Methods
	public:
		DLLHashTable_API LinearProbingHashTable();
		DLLHashTable_API void Initialize();
		DLLHashTable_API int GetHash(int key);
		DLLHashTable_API HashNode* Insert(int key, int value);
		DLLHashTable_API int Retrieve(int key);
		DLLHashTable_API int Remove(int key);
		DLLHashTable_API int sizeOfTable();
		DLLHashTable_API bool isEmpty();
		DLLHashTable_API void Display();
	private:
		const int MAXCAP = 20000;
		HashNode** table;
		int mnSize;
		HashNode* dummy;
};
