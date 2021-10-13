#include "pch.h"
#include "CppUnitTest.h"
#include "..\Dll_HASHTABLE\Dll_HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableUnitTest
{
	TEST_CLASS(HashTableUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int limit = 100;
			int debug = 0;
			HashNode* hn = NULL;
			LinearProbingHashTable* ht = new LinearProbingHashTable(debug);
			for (int i = 0; i < limit; i++)
			{
				ht->Insert(i, i);
			}
			hn = ht->Retrieve(7);
			Assert::IsTrue(hn->value = 7);
			hn = ht->Retrieve(101);
			Assert::IsTrue(hn == NULL);

			Assert::IsTrue(ht->sizeOfTable() == 100);
		}
		TEST_METHOD(TestMethod2)
		{
			int limit = 100;
			int debug = 0;
			HashNode* hn = NULL;

			Hash* ht = new Hash(limit, debug);
			for (int i = 0; i < limit; i++)
			{
				ht->Insert(i);
			}
			hn = ht->Retrieve(7);
			Assert::IsTrue(hn->value = 7);
			hn = ht->Retrieve(101);
			Assert::IsTrue(hn->value = -1);
		}
		TEST_METHOD(TestMethod3)
		{
			int limit = 100;
			int debug = 0;
			HashNode* hn = NULL;
			DoubleHashedHashTable* ht = new DoubleHashedHashTable(limit, debug);
			for (int i = 0; i < limit; i++)
			{
				ht->Insert(i);
			}
			hn = ht->Retrieve(7);
			Assert::IsTrue(hn->value = 7);
			hn = ht->Retrieve(101);
			Assert::IsTrue(hn->value = -1);
		}
	};
}
