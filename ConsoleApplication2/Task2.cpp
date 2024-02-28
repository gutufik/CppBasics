#include <iostream>
using namespace std;

// ������������ ������ �1 
int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    float min = -1; 

    cout << "������� ���������� ��������� ";
    cin >> n;
    if (n < 0) 
    {
        cout << "������� ������������� ����������";
        return 0;
    }
    cin.clear();         // ������� ������ � ������������� �������� ��������
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++)
    {
        cout << "������� ����� ";
        float number;
        cin >> number;

        if (number > 20 && (number < min || min == -1))
        {
            min = number;
        }

        cin.clear();         // ������� ������ � ������������� �������� ��������
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (min == -1)
        cout << "�� ������� ����� ��������������� �������";
    else
        cout << min;

    return 0;
}
