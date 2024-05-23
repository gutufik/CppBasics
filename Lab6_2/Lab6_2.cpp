#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Node {
    Node* Next;
    string Value;

    Node(string stringValue) {
        Next = NULL;
        Value = stringValue;
    }
};

struct Stack 
{
    Node* Top;
    int Depth;

    Stack()
    {
        Top = NULL;
        Depth = 0;
    }

    void Push(string stringValue) 
    {
        Node* newTop = new Node(stringValue);
        newTop->Next = Top;
        Top = newTop;
        Depth++;
    }
    string Pop()
    {
        string topValue;
        if (!IsEmpty())
        {
            topValue = Top->Value;
            Top = Top->Next;
            Depth--;
        }
        return topValue;
    }
    bool IsEmpty()
    {
        return Depth == 0;
    }

    Stack* Copy()
    {
        Stack* reversedCopy = new Stack();
        Node* currentNode = Top;

        while (currentNode)
        {
            reversedCopy->Push(currentNode->Value);
            currentNode = currentNode->Next;
        }
        currentNode = reversedCopy->Top;
        Stack* copy = new Stack();

        while (currentNode)
        {
            copy->Push(currentNode->Value);
            currentNode = currentNode->Next;
        }

        return copy;
    }

    string ToString()
    {
        string result = "";

        Node* currentNode = Top;

        while (currentNode)
        {
            result += (currentNode->Value + "\n");
            currentNode = currentNode->Next;
        }

        return result;
    }
};

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

    Stack* st1 = new Stack();
    Stack* st2 = new Stack();

    Stack* result = new Stack();

    int length;
    char inputString[20];

    cout << "Введите количество элементов для 1 стека\n";
    cin >> inputString;
    if (!TryParseInt(inputString, length)) return 0;
    if (length <= 0)
    {
        cout << "Количество элементов должно быть больше нуля";
        return 1;
    }

    for (int i = 0; i < length; i++)
    {
        cout << "Введите значение\n";
        cin >> inputString;
        st1->Push(inputString);
    }

    cout << "Введите количество элементов для 2 стека\n";
    cin >> inputString;
    if (!TryParseInt(inputString, length)) return 0;
    if (length <= 0)
    {
        cout << "Количество элементов должно быть больше нуля";
        return 1;
    }

    for (int i = 0; i < length; i++)
    {
        cout << "Введите значение\n";
        cin >> inputString;
        st2->Push(inputString);
    }

    Stack* st1Copy = st1->Copy();
    Stack* st2Copy = st2->Copy();

    while (!st1->IsEmpty() || !st2->IsEmpty())
    {
        string st1Top = st1->Pop();
        string st2Top = st2->Pop();

        Node* resultTop = result->Top;
        string resultTopValue;
        if (resultTop == NULL)
        {
            result->Push(st1Top);

            resultTopValue = result->Top->Value;

            if (!st2->IsEmpty() && (tolower(resultTopValue[0]) == tolower(st2Top[0]) ||
                tolower(resultTopValue[resultTopValue.length() - 1]) == tolower(st2Top[st2Top.length() - 1]))) {
                result->Push(st2Top);
            }
        }
        else
        {
            resultTopValue = result->Top->Value;

            if (!st1->IsEmpty() && (tolower(resultTopValue[0]) == tolower(st1Top[0]) ||
                tolower(resultTopValue[resultTopValue.length() - 1]) == tolower(st1Top[st1Top.length() - 1]))) {
                result->Push(st1Top);
            }
            resultTopValue = result->Top->Value;

            if (!st2->IsEmpty() && (tolower(resultTopValue[0]) == tolower(st2Top[0]) ||
                tolower(resultTopValue[resultTopValue.length() - 1]) == tolower(st2Top[st2Top.length() - 1]))) {
                result->Push(st2Top);
            }
        }
    }
    cout << "Стек 1 \n";
    cout << st1Copy->ToString();
    cout << endl;

    cout << "Стек 2 \n";
    cout << st2Copy->ToString();
    cout << endl;

    cout << "Стек 3 \n";
    cout << result->ToString();

    return 0;
}
