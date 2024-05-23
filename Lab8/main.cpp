#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cstdlib>  
#include <fstream>
#include "Student.h"
#include "LinkedList.h"
#include "PrintMenu.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string line;

    fstream file("Students.txt");

    fstream output("Output.txt");

    LinkedList* students = new LinkedList();

    string header;

    bool headerPassed = false;

    if (file.fail())
    {
        cout << "Не удается открыть файл Students.txt";
        return 1;
    }

    if (file.is_open()) // Чтение файла
    {
        while (getline(file, line))
        {
            students->PushBack(new Student(line));
        }
    }
    file.close();

    PrintMenu();

    int num;
    cin >> num;


    while (num != 5) {
        switch (num)
        {
            case 1:
            {
                PrintList(students);
                break;
            }
            case 2:
            {
                string FIO;
                cout << "Введите фамилию\n";
                cin >> FIO;
                LinkedList* filtered = students->Filter(FIO);
                if (filtered->Length == 0) {
                    cout << "Ничего не найдено\n";
                }
                else {
                    PrintList(filtered);
                }
                break;
            }
            case 3:
            {
                LinkedList* withTwos = students->GetStudentsWithTwos();
                PrintList(withTwos);
                break;
            }
            case 4:
            {
                SortList(students);
                PrintList(students);
                break;
            }
        }
        PrintMenu();
        cin >> num;
    }
}