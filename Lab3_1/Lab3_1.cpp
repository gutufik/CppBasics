#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>


using namespace std;

bool TryParseFloat(string str, float& result)
{
    if (sscanf_s(str.data(), "%f", &result) != 1) {
        cout << "���������� ������������� �������� � �����\n";
        return false;
    }
    return true;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    vector<float> arr;
    float sum = 0;

    string line;
    int lineNumber = 1;

    fstream file("Data.txt");

    if (file.fail())
    {
        cout << "�� ������� ������� ����";
        return 1;
    }

    if (file.is_open())
    {
        while (getline(file, line))
        {
            float fline;

            if (!TryParseFloat(line, fline)) {
                cout << "������ � ������ " + to_string(lineNumber);
                return 1;
            }

            if (fline > 0)
            {
                sum += stof(line);
                arr.push_back(fline); // ��������� � �������� ������ ������ ������������� ��������
            }
            lineNumber++;
        }
    }
    file.close();

    if (arr.size() == 0) {
        cout << "� ����� ��� ������������� �����";
        return 1;
    }

    float avg = sum / arr.size();

    vector<float> output;

    for (float elem : arr)
    {
        if (elem > avg) output.push_back(elem);
    }

    cout << "������� �������� ������������� ����� = " << avg << endl;

    if (output.size() == 0) {
        cout << "� ����� ��� ����� ����������� ������� ��������\n";
        return 1;
    }

    cout << "����� ����������� ������� ��������:\n";
    for (float elem : output)
    {
        cout << elem << endl;
    }
}

