#include <string>
#include <iostream>
#include "LinkedList.h"
#include <fstream>

using namespace std;

 void ReadFile(string filename, LinkedList* students)
{
    fstream file(filename);

    string line;

    if (file.fail())
    {
        cout << "�� ������� ������� ���� Students.txt";
        return ;
    }

    if (file.is_open()) // ������ �����
    {
        while (getline(file, line))
        {
            students->PushBack(new Student(line));
        }
    }

    file.close();
}
