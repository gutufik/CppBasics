#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <format>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <json/json.h>
#include <json/value.h>

using namespace std;

bool IsSizeValid(float size, string notValidMessage) {
    bool valid = size > 0;
    if (!valid) cout << notValidMessage;
    return valid;
}

bool TryParseFloat(string str, float& result) {
    if (sscanf_s(str.data(), "%f", &result) != 1) {
        cout << "Невозможно преобразовать значение в число\n";
        return false;
    }
    return true;
}

struct TabletScanner {
    string ModelName;
    float Price;
    float HorizontalSize;
    float VerticalSize;

    TabletScanner(string modelName, float price, float horizontalSize, float verticalsize)
    {
        ModelName = modelName;
        Price = price;
        HorizontalSize = horizontalSize;
        VerticalSize = verticalsize;
    }

    string ToString() {
        stringstream stream;

        stream << fixed << setprecision(2) << HorizontalSize;

        return format("{} {}x{} {}\n", ModelName, HorizontalSize, VerticalSize, Price);
    }
};


struct Node {
    Node* Next;
    TabletScanner* Value;

    Node(TabletScanner* scanner) {
        Next = NULL;
        Value = scanner;
    }
};

struct LinkedList
{
    Node* Head;
    int Length;


    LinkedList()
    {
        Head = NULL;
        Length = 0;
    }

    void PushBack(TabletScanner* scanner) {
        Node* newNode = new Node(scanner);

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

    TabletScanner* operator[](int index) {
        if (index < 0 || index >= Length)
        {
            throw out_of_range("Index out of range");
        }

        Node* resultNode = Head;

        for (int i = 0; i < index; i++) {
            resultNode = resultNode->Next;
        }
        return resultNode->Value;
    }

    LinkedList* Filter(float minVSize, float maxVSize, float minHSize, float maxHSize) {
        LinkedList* filteredList = new LinkedList();
        
        for (int i = 0; i < Length; i++) {
            if ((*this)[i]->VerticalSize >= minVSize &&
                (*this)[i]->VerticalSize < maxVSize &&
                (*this)[i]->HorizontalSize >= minHSize &&
                (*this)[i]->HorizontalSize < maxHSize) {

                TabletScanner* sc = (*this)[i];

                filteredList->PushBack(sc);
            }
        }


        return filteredList;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    LinkedList* scannerList = new LinkedList();

    fstream file("Data.json");
    if (file.fail()) {
        cout << "Не удается открыть файл Data.json";
        return 1;
    }

    Json::Value json;
    Json::Reader reader;

    reader.parse(file, json);

    for (int i = 0; i < json.size(); i++) {

        string str = json[i]["ModelName"].asString().c_str();
        TabletScanner* scanner = new TabletScanner
        (
            json[i]["ModelName"].asString().c_str(),
            json[i]["Price"].asFloat(),
            json[i]["HorizontalSize"].asFloat(),
            json[i]["VerticalSize"].asFloat()
        );

        scannerList->PushBack(scanner);
    }

    string inputString;
    float minVSize, maxVSize, minHSize, maxHSize;

    cout << "Введите минимальный горизонтальный размер\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, minHSize)) return 1;
    if (!IsSizeValid(minHSize, "Размер должен быть больше 0\n")) return 1;

    cout << "Введите максимальный горизонтальный размер\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, maxHSize)) return 1;
    if (!IsSizeValid(maxHSize, "Размер должен быть больше 0\n")) return 1;
    if (minHSize > maxHSize) {
        cout << "Максимальный размер должен быть больше минимального";
        return 1;
    }

    cout << "Введите минимальный вертикальный размер\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, minVSize)) return 1;
    if (!IsSizeValid(minVSize, "Размер должен быть больше 0\n")) return 1;

    cout << "Введите максимальный вертикальный размер\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, maxVSize)) return 1;
    if (!IsSizeValid(maxVSize, "Размер должен быть больше 0\n")) return 1;
    if (minVSize > maxVSize) {
        cout << "Максимальный размер должен быть больше минимального";
        return 1;
    }

    LinkedList* filteredList = scannerList->Filter(minVSize, maxVSize, minHSize, maxHSize);

    if (filteredList->Length == 0) cout << "Ничего не найдено";

    for (int i = 0; i < filteredList->Length; i++) {
        cout << (*filteredList)[i]->ToString();
    }

    return 0;
}