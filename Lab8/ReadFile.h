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
        cout << "Не удается открыть файл Students.txt";
        return ;
    }

    if (file.is_open()) // Чтение файла
    {
        while (getline(file, line))
        {
            students->PushBack(new Student(line));
        }
    }

    file.close();
}
