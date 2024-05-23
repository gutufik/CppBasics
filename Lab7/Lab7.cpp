#include <iostream>
#include <string> 
#include <Windows.h>

#define maxVertices 10

using namespace std;

bool TryParseInt(char* str, int& result)
{
    if (sscanf_s(str, "%d", &result) != 1) {
        cout << "���������� ������������� ��������� �������� � �����\n";
        return false;
    }
    return true;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int vertices;
    char inputString[20];

    cout << "������� ���������� ������ (���� " +to_string(maxVertices) + ") \n";
    cin >> inputString;
    if (!TryParseInt(inputString, vertices)) return 0;
    if (vertices <= 0)
    {
        cout << "���������� ������ ������ ���� ������ ����";
        return 1;
    }
    if (vertices > maxVertices)
    {
        cout << "���������� ������ ������ ���� �� ������ " + to_string(maxVertices);
        return 1;
    }

    int a, b;

    int** adjacencyMatrix = new int* [vertices];

    for (int i = 0; i < vertices; i++)
    {
        adjacencyMatrix[i] = new int[vertices];
    }

    int arcs;

    cout << "������� ���������� ��� \n";
    cin >> inputString;
    if (!TryParseInt(inputString, arcs)) return 0;
    if (arcs <= 0)
    {
        cout << "���������� ��� ������ ���� ������ ����";
        return 1;
    }

    for (int i = 0; i < arcs; i++)
    {
        cout << "������� ���� (�������������� ��������) \n";
        cin >> a >> b;

        if (a - 1 > vertices || b - 1 > vertices) {
            cout << "����������� ����";
            return 1;
        }
        adjacencyMatrix[a - 1][b - 1] = 1;
    }

    cout << "��������������� ��� ������ \n";

    for (int i = 0; i < vertices; i++)
    {
        cout << to_string(i + 1) + " - ";
        for (int j = 0; j < vertices; j++)
        {
            if (adjacencyMatrix[j][i] == 1) 
            {
                cout << to_string(j + 1) + " ";
            }
        }
        cout << "\n";
    }
}