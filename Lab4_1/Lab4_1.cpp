#include <iostream>
#include <cmath>
#include <format>
#include <stdexcept>
#include <Windows.h>

using namespace std;

bool TryParseFloat(string str, float& result)
{
    if (sscanf_s(str.data(), "%f", &result) != 1) {
        cout << "Невозможно преобразовать значение в число\n";
        return false;
    }
    return true;
}

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
        if (Length == 0) {
            throw length_error("Cannot find maximum value in an empty list.");
        }
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

        for (int i = 0; i < Length; i++) {
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

    string inputString;
    float vectorCount;

    LinkedList* vectors = new LinkedList();

    cout << "Введите количество векторов\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, vectorCount)) return 1;

    if (vectorCount <= 0) {
        cout << "Количество должно быть больше 0\n";
        return 1;
    }

    for (int i = 0; i < vectorCount; i++)
    {
        Vector* vector = new Vector();
        cout << format("Введите x для {}-го вектора\n", i + 1);

        cin >> inputString;

        if (!TryParseFloat(inputString, vector->x)) return 1;

        cout << format("Введите y для {}-го вектора\n", i + 1);
        cin >> inputString;

        if (!TryParseFloat(inputString, vector->y)) return 1;

        cout << format("Введите z для {}-го вектора\n", i + 1);
        cin >> inputString;

        if (!TryParseFloat(inputString, vector->z)) return 1;

        vectors->PushBack(vector);

        cout << format("Длина {}-го вектора = {}\n\n", i + 1, vector->GetLength());
    }
    try {
        Vector maxVector = vectors->Max();
        cout << "Максимальная длина вектора " << maxVector.GetLength() << endl;
        cout << "Индекс максимального вектора " << vectors->IndexOf(maxVector) << endl;
    }
    catch (exception e) {
        cerr << e.what();
    }
}