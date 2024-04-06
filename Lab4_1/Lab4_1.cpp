#include <iostream>
#include <cmath>
#include <format>
#include <stdexcept>
#include <Windows.h>

using namespace std;

//�������� ��������!!!

struct Vector {
    float x;
    float y;
    float z;

    float GetLength() {
        return sqrt(x*x + y*y + z*z);
    }

    bool operator==(Vector& other) {
        return this->GetLength() == other.GetLength();
    }
    bool operator> (Vector& other) {
        return this->GetLength() > other.GetLength();
    }
};

struct Node {
    Node* Next;
    Vector* Value;

    Node(Vector* vector) {
        Next = NULL;
        Value = vector;
    }
};

struct LinkedList {
    Node* Head;
    int Length;

    LinkedList() {
        Head = NULL;
        Length = 0;
    }

    void PushBack(Vector* vector) {
        Node* newNode = new Node(vector);
        
        if (Length == 0) {
            Head = newNode;
        }
        else {
            Node* lastNode = Head;
            while (lastNode->Next != NULL)
            {
                lastNode = lastNode->Next;
            }

            lastNode->Next = newNode;
        }
        Length++;
    }

    Vector operator[](int index) {
        if (index < 0 || index >= Length)
        {
            throw out_of_range("Index out of range");
        }

        Node* resultNode = Head;

        for (int i = 0; i < index; i++) {
            resultNode = resultNode->Next;
        }
        return *resultNode->Value;
    }

    Vector Max() {
        Vector max = *(*Head).Value;

        for (int i = 1; i < Length; i++) {
            if ((*this)[i] > max) {
                max = (*this)[i];
            }
        }
        return max;
    }

    int IndexOf(Vector vector) {
        int index = -1;

        for (int i = 1; i < Length; i++) {
            if ((*this)[i] == vector) {
                return i;
            }
        }
        return index;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int vectorCount;
    LinkedList* vectors = new LinkedList();

    cout << "������� ���������� ��������\n";
    cin >> vectorCount;

    for (int i = 0; i < vectorCount; i++) 
    {
        Vector* vector = new Vector();
        cout << format("������� x ��� {}-�� �������\n", i + 1);
        cin >> vector->x;

        cout << format("������� y ��� {}-�� �������\n", i + 1);
        cin >> vector->y;

        cout << format("������� z ��� {}-�� �������\n", i + 1);
        cin >> vector->z;

        vectors->PushBack(vector);

        cout << format("����� {}-�� ������� = {}\n", i + 1, vector->GetLength());
    }
    try {
        
        for (int i = 0; i < vectorCount; i++) {
            cout << (*vectors)[i].GetLength() << endl;
        }

        Vector maxVector = vectors->Max();
        cout << "������������ ����� ������� " << maxVector.GetLength() << endl;
        cout << "������ ������������� ������� " << vectors->IndexOf(maxVector) << endl;
    }
    catch(exception e) {
        cerr << e.what();
    }
}
