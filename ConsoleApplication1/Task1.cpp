#include <iostream>
using namespace std;

// ������������ ������ �1 

int main()
{
    setlocale(LC_ALL, "Russian");

    float number = 0;
    float sum = 0;
    int count = 0;

    cout << "������� ����� ";
    cin >> number;

    while (number != 65535)
    {
        if ((int)number % 5 == 0 && (int)number % 7 != 0)
        {
            sum += number;
            count++;
        }

        cin.clear();         // ������� ������ � ������������� �������� ��������
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "������� ����� ";
        cin >> number;
    }

    if (count > 0)
    {
        cout << sum / count;
    }
    else
    {
        cout << "������������";
    }

    return 0;
}
