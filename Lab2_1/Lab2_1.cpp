#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

void PrintArray(int* array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << *(array + i) << " ";
    }
    cout << endl;
}

void PositiveSort(int* array, int arraySize)
{
    for (int i = 0; i < arraySize; i++) 
    {
        for (int j = i; j < arraySize; j++)
        {
            if (*(array + i) > 0 && *(array + j) > 0 &&
                *(array + i) > *(array + j))
            {
                swap(*(array + i), *(array + j));
            }
        }
    }
}

void FillArray(int* array, int arraySize, int minValue, int maxValue)
{
    srand(time(NULL));

    for (int i = 0; i < arraySize; i++)
    {
        *(array + i) = minValue + rand() % (maxValue - minValue + 1);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n, min, max;

    cout << "Введите количество элементов в массиве\n";
    cin >> n;
    
    if (cin.fail())
    {
        cout << "Невозможно преобразовать введенное значение в число";
        return 1;
    }

    if (n <= 0)
    {
        cout << "Количество элементов должно быть больше нуля";
        return 1;
    }

    cout << "Введите минимальное значение для элемента \n";
    cin >> min;
    if (cin.fail())
    {
        cout << "Невозможно преобразовать введенное значение в число";
        return 1;
    }

    cout << "Введите максимальное значение для элемента\n";
    cin >> max;

    if (cin.fail())
    {
        cout << "Невозможно преобразовать введенное значение в число";
        return 1;
    }
    if (min > max)
    {
        cout << "Минимум должен быть меньше или равен максимуму \n";
        return 1;
    }
    
    int* array = new int[n];
    FillArray(array, n, min, max);

    cout << "Исходный массив\n";
    PrintArray(array, n);

    PositiveSort(array, n);

    cout << "Отсортированный массив\n";
    PrintArray(array, n);

    delete[] array;

    return 0;
}