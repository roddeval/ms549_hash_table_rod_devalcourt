// ms549_hash_table_rod_devalcourt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\Dll_HASHTABLE\Dll_HashTable.h"
#include <cstdlib>
#include <ctime>
using namespace std;

#include <cstddef>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>

void LinearProbing()
{
    LinearProbingHashTable* ht = new LinearProbingHashTable();

    string pathFile = "C:\\Users\\rdeva\\source\\repos\\roddeval\\ms549_hash_table_rod_devalcourt\\100_numbers.txt";
    //string pathFile = "C:\\Users\\rdeva\\source\\repos\\roddeval\\ms549_hash_table_rod_devalcourt\\1000_numbers.txt";
    //string pathFile = "C:\\Users\\rdeva\\source\\repos\\roddeval\\ms549_hash_table_rod_devalcourt\\10000_numbers.txt";
    fstream file;
    file.open(pathFile, ios::in);
    string line = "";
    std::string::size_type sz;
    int value = 0;

    SYSTEMTIME st;
    SYSTEMTIME stopTime;
    SYSTEMTIME abc;
    std::stringstream ssStart;
    std::stringstream ssStop;
    std::stringstream ssElapsed;
    string timeString;
    string timeString2;
    string timeString3;
    FILETIME ft;
    FILETIME ftStop;
    FILETIME elapsed;

    ULARGE_INTEGER v_ui;
    __int64 v_right, v_left, v_res;

    if (file.is_open())
    {

        cout << "10000 numbers" << endl;

        GetSystemTime(&st);
        ssStart << st.wMonth << "/" << st.wDay << "/" << st.wYear << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << "." << st.wMilliseconds;

        timeString = ssStart.str();

        cout << "start time: " << timeString << endl;

        while (getline(file, line))
        {
            value = std::stoi(line, &sz);
            ht->Insert(value, value);
        }

        ht->Display();

        GetSystemTime(&stopTime);
        ssStop << stopTime.wMonth << "/" << stopTime.wDay << "/" << stopTime.wYear << " " << stopTime.wHour << ":" << stopTime.wMinute << ":" << stopTime.wSecond << "." << stopTime.wMilliseconds;

        timeString2 = ssStop.str();

        cout << "stop time: " << timeString2 << endl;


        SystemTimeToFileTime(&st, &ft);
        SystemTimeToFileTime(&stopTime, &ftStop);

        v_ui.LowPart = ftStop.dwLowDateTime;
        v_ui.HighPart = ftStop.dwHighDateTime;
        v_right = v_ui.QuadPart;

        v_ui.LowPart = ft.dwLowDateTime;
        v_ui.HighPart = ft.dwHighDateTime;
        v_left = v_ui.QuadPart;

        v_res = v_right - v_left;

        v_ui.QuadPart = v_res;
        elapsed.dwLowDateTime = v_ui.LowPart;
        elapsed.dwHighDateTime = v_ui.HighPart;
        FileTimeToSystemTime(&elapsed, &abc);

        ssElapsed << abc.wHour << ":" << abc.wMinute << ":" << abc.wSecond << "." << abc.wMilliseconds;

        timeString3 = ssElapsed.str();

        std::cout << "Elapsed time: " << timeString3 << endl;

        file.close();
    }

}

void Chained()
{
    //string pathFile = "C:\\Users\\rdeva\\source\\repos\\roddeval\\ms549_hash_table_rod_devalcourt\\100_numbers.txt";
    //string pathFile = "C:\\Users\\rdeva\\source\\repos\\roddeval\\ms549_hash_table_rod_devalcourt\\1000_numbers.txt";
    string pathFile = "C:\\Users\\rdeva\\source\\repos\\roddeval\\ms549_hash_table_rod_devalcourt\\10000_numbers.txt";

    int limit = 10000;

    fstream file;
    file.open(pathFile, ios::in);
    string line = "";
    std::string::size_type sz;
    int value = 0;

    SYSTEMTIME st;
    SYSTEMTIME stopTime;
    SYSTEMTIME abc;
    std::stringstream ssStart;
    std::stringstream ssStop;
    std::stringstream ssElapsed;
    string timeString;
    string timeString2;
    string timeString3;
    FILETIME ft;
    FILETIME ftStop;
    FILETIME elapsed;

    ULARGE_INTEGER v_ui;
    __int64 v_right, v_left, v_res;
    Hash* ht = new Hash(limit);
    //list<int>* result = NULL;
    //size_t info;
    HashNode* hn = NULL;

    if (file.is_open())
    {

        cout << "10000 numbers" << endl;

        GetSystemTime(&st);
        ssStart << st.wMonth << "/" << st.wDay << "/" << st.wYear << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << "." << st.wMilliseconds;

        timeString = ssStart.str();

        cout << "start time: " << timeString << endl;

        while (getline(file, line))
        {
            value = std::stoi(line, &sz);
            ht->Insert(value);
        }

        ht->Display();
        
        cout << endl;

        value = 11023;
        cout << "looking for: " << value << endl;
        hn = ht->Retrieve(value);
        if (hn != NULL)
        {
            cout << "key: " << hn->key << " Value: " << hn->value << endl;
        }

        GetSystemTime(&stopTime);
        ssStop << stopTime.wMonth << "/" << stopTime.wDay << "/" << stopTime.wYear << " " << stopTime.wHour << ":" << stopTime.wMinute << ":" << stopTime.wSecond << "." << stopTime.wMilliseconds;

        timeString2 = ssStop.str();

        cout << "stop time: " << timeString2 << endl;


        SystemTimeToFileTime(&st, &ft);
        SystemTimeToFileTime(&stopTime, &ftStop);

        v_ui.LowPart = ftStop.dwLowDateTime;
        v_ui.HighPart = ftStop.dwHighDateTime;
        v_right = v_ui.QuadPart;

        v_ui.LowPart = ft.dwLowDateTime;
        v_ui.HighPart = ft.dwHighDateTime;
        v_left = v_ui.QuadPart;

        v_res = v_right - v_left;

        v_ui.QuadPart = v_res;
        elapsed.dwLowDateTime = v_ui.LowPart;
        elapsed.dwHighDateTime = v_ui.HighPart;
        FileTimeToSystemTime(&elapsed, &abc);

        ssElapsed << abc.wHour << ":" << abc.wMinute << ":" << abc.wSecond << "." << abc.wMilliseconds;

        timeString3 = ssElapsed.str();

        std::cout << "Elapsed time: " << timeString3 << endl;

        file.close();

    }

}


int main()
{
    Chained();
    //LinearProbing();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
