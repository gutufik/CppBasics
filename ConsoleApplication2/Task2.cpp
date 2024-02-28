#include <iostream>
using namespace std;

// лабораторна€ работа є1 
int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    float min = -1; 

    cout << "¬ведите количество элементов ";
    cin >> n;
    if (n < 0) 
    {
        cout << "¬ведено отрицательное количество";
        return 0;
    }
    cin.clear();         // очистка буфера и игнорирование неверных символов
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++)
    {
        cout << "¬ведите число ";
        float number;
        cin >> number;

        if (number > 20 && (number < min || min == -1))
        {
            min = number;
        }

        cin.clear();         // очистка буфера и игнорирование неверных символов
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (min == -1)
        cout << "Ќе введено чисел удовлетвор€ющих условию";
    else
        cout << min;

    return 0;
}
