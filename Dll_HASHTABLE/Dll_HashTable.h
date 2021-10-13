#pragma once

#ifdef DLLHASHTABLE_EXPORTS
#define DLLHashTable_API __declspec(dllexport)
#else
#define DLLHashTable_API __declspec(dllimport)
#endif

#include <iostream>
#include <list>
using namespace std;

// class HashNode was primarily used to store key/value pairs for class LinearProbingHashTable
// initially.  However it is used in the other classes primarily in the
// Retrieve method as its return value.  All member variables and methods are public.
class HashNode
{
	public:

		// holds a hashed key
		int key;
		
		// holds a value represented by the hashed key
		int value;

		// constructor
		DLLHashTable_API HashNode(int key, int value);
};

// class Hash is a chained hash table.
class Hash
{
	public:

		// constructor
		DLLHashTable_API Hash(int size, int debug);

		// initializes member variables
		DLLHashTable_API void Initialize(int size, int debug);
		
		// hash method for key's value
		DLLHashTable_API int GetHash(int key);
		
		// insert method for key's value
		DLLHashTable_API void Insert(int key);
		
		// remove method for key's value
		DLLHashTable_API void Remove(int key);
		
		// displays the contents of the hash table to the screen
		DLLHashTable_API void Display();
		
		// retrieve a searched for value as a HashNode (key,value) pair
		DLLHashTable_API HashNode* Retrieve(int key);

private:
	
		// the hash table is represented as a list<int> * [mnNumIndexes]
		// the method Initialize does this
		list<int>* table;

		// represents how many key/value pairs you would like in the hash table
		// represented by list<int>* being the value and list<int> * [hashed key] as the value for key
		int mnNumIndexes;

		// used for a debug flag
		int mnDebug;
};

// class LinearProbingHashTable is a linearly probing hash table implementation.
class LinearProbingHashTable
{
	
	// Public Methods
	public:

		// constructor
		DLLHashTable_API LinearProbingHashTable(int debug);

		// initializes member variables including the hash table itself
		DLLHashTable_API void Initialize(int debug);

		// hash method used for the array index of HashNodes
		DLLHashTable_API int GetHash(int key);

		// lets you insert a key and value pair into the hash table
		// this method calls GetHash with the value of key which is
		// used as the array index.  the key/value pair is stored in
		// the HashNode pointed to by table**
		DLLHashTable_API HashNode* Insert(int key, int value);

		// with a key we can retrieve the HashNode key/value pair
		// this method calls the GetHash method to use in the array
		// index
		DLLHashTable_API HashNode* Retrieve(int key);

		// this method removes a key/value from the hash table
		DLLHashTable_API int Remove(int key);

		// returns the current size of the table
		DLLHashTable_API int sizeOfTable();

		// returns whether or not the hashtable is empty
		DLLHashTable_API bool isEmpty();

		// this method displays the contents of the hash table
		// to the console screen
		DLLHashTable_API void Display();

private:

		// MAXCAP is the maximum nodes expected in this implementation
		const int MAXCAP = 20000;

		// table holds the hash table of HashNode in an array.  It is
		// initialized in the member method Initialize
		HashNode** table;

		// mnSize is the current size of the hash table array.  it is
		// is set to zero (0) in the member method Initialize
		int mnSize;

		// dummy holds a key/value pair of (-1,-1) to use if the retrieve
		// method can't find a key/value pair and returns it to signal
		// there wasn't one found in the hashtable by the retrieve method
		HashNode* dummy;

		// used for a debug flag
		int mnDebug;

};

// the EntryType values of Legi and Emp are used by the Entry struct that
// is used by the double hashed table
enum EntryType {Legi, Emp};

// struct Entry is used to hold the value you insert into the double hashed hash table
// class. int e is the datapoint, i.e. the value for a key.  info is an enum type
// used in the methods of this class
struct Entry
{
	int e;
	enum EntryType info;
};

// struct Table is used by the double hashed hash table to store the hashed entries
// int s is the size of the table, Entry* tab is used like an array where the array
// indexed/key is the double hashed key for a value.
struct Table
{
	int s;
	Entry* tab;
};

// DoubleHashedHashTable is a double hashed hash table implementation.
// it performs rather well especially with a large number of values (10,000).

class DoubleHashedHashTable
{
	public:

		// constructor
		DLLHashTable_API DoubleHashedHashTable(int size, int debug);
		
		// initialize member values
		DLLHashTable_API void Initialize(int size, int debug);
		
		// hash method #1
		DLLHashTable_API int Hash1(int k, int s);
		
		// hash method #2
		DLLHashTable_API int Hash2(int k, int s);
		
		// returns a double hash search key given a value k
		DLLHashTable_API int SearchKey(int k);
		
		// insert method to double hashed hash table
		DLLHashTable_API void Insert(int k);
		
		// method to display the contents of the double hashed hash table
		DLLHashTable_API void Display();
		
		// retrieve a searched for value as a HashNode (key,value) pair
		DLLHashTable_API HashNode* Retrieve(int searchFor);
		
		// remove a value from the double hashed hash table
		DLLHashTable_API void Remove(int value);
		
		// rehash doubles the size of the hash table it was initialized with
		DLLHashTable_API void ReHash();
		
		// public member variable that is double hashed.  It uses a struct Table*
		Table* table;

	private:
		
		// this member variable is set, or initialized, in the constructor.
		// so if you use a rather large number, say 1,000,000 you might end up
		// with 2,000,000 hashed key value pairs.
		int maxSize;

		// used for a debug flag
		int mnDebug;
};
