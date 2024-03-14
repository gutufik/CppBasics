#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

void PrintArray(int** array, int rowsCount, int colsCount)
{
    for (int i = rowsCount - 1; i > -1; i--)
    {
        for (int j = 0; j < colsCount; j++)
        {
            cout << array[i][j] << "\t";
        }
        cout << endl;
    }
}

void RowSort(int** array, int rowsCount, int colsCount)
{
    for (int i = 0; i < rowsCount; i++)
    {
        for (int j = i; j < rowsCount; j++)
        {
            if (array[i][0] > array[j][0])
            {
                swap(array[i], array[j]);
            }
        }
    }
}

void FillArray(int** array, int rowsCount, int colsCount,  int minValue, int maxValue)
{
    srand(time(NULL));

    for (int i = 0; i < rowsCount; i++)
    {
        for (int j = 0; j < colsCount; j++)
        {
            array[i][j] = minValue + rand() % (maxValue - minValue + 1);
        }
    }
}

bool TryParseInt(char *str, int &result) 
{
    if (sscanf_s(str, "%d", &result) != 1) {
        cout << "���������� ������������� ��������� �������� � �����\n";
        return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    char inputString[20];

    int n, m, min, max;

    cout << "������� ���������� ����� � �������\n";
    cin >> inputString;
    if (!TryParseInt(inputString, n)) return 0;
    if (n <= 0)
    {
        cout << "���������� ����� ������ ���� ������ ����";
        return 1;
    }

    cout << "������� ���������� �������� � �������\n";
    cin >> inputString;
    if (!TryParseInt(inputString, m)) return 0;
    if (n <= 0)
    {
        cout << "���������� �������� ������ ���� ������ ����";
        return 1;
    }

    cout << "������� ����������� �������� ��� �������� \n";
    cin >> inputString;
    if (!TryParseInt(inputString, min)) return 0;

    cout << "������� ������������ �������� ��� ��������\n";
    cin >> inputString;
    if (!TryParseInt(inputString, max)) return 0;
    if (min > max)
    {
        cout << "������� ������ ���� ������ ��� ����� ��������� \n";
        return 1;
    }

    int** array = new int*[n];
    for (int i = 0; i < n; ++i)
        array[i] = new int[m];

    FillArray(array, n, m, min, max);
    cout << "�������� ������\n";
    PrintArray(array, n, m);

    RowSort(array, n, m);
    cout << "��������������� ������\n";
    PrintArray(array, n, m);

    for (int i = 0; i < n; ++i)
        delete[] array[i];
    delete[] array;

}