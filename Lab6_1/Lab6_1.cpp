#include <iostream>
#include <Windows.h>

using namespace std;

bool Any(int* array, int length) 
{
    if (length == 1)
        return cbrt(pow(array[0], 2) + 2) < 10;
    if (length == 2)
        return cbrt(pow(array[0], 2) + 2) < 10 || cbrt(pow(array[1], 2) + 2) < 10;

    return Any(array, length / 3) || Any(array + length / 3, length - length / 3);
}

bool TryParseInt(char* str, int& result)
{
    if (sscanf_s(str, "%d", &result) != 1) {
        cout << "Невозможно преобразовать введенное значение в число\n";
        return false;
    }
    return true;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int length;
    char inputString[20];

    cout << "Введите количество элементов в массиве\n";
    cin >> inputString;
    if (!TryParseInt(inputString, length)) return 0;
    if (length <= 0)
    {
        cout << "Количество элементов должно быть больше нуля";
        return 1;
    }
    int* myArray = new int[length];

    for (int i = 0; i < length; i++)
    {
        cout << "Введите значение\n";
        cin >> inputString;
        if (!TryParseInt(inputString, myArray[i])) return 0;
    }

    if (Any(myArray, length))
    {
        std::cout << "В массиве есть хоть один элемент, удовлетворяющий условию" << std::endl;
    }
    else
    {
        cout << "В массиве нет элементов, удовлетворяющих условию" << endl;
    }

    return 0;
}