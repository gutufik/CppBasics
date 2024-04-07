#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <Windows.h>
#include <json/json.h>
#include <json/value.h>

using namespace std;

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

    TabletScanner operator[](int index) {
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

    LinkedList Filter() {

    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    LinkedList* scannerList = new LinkedList();

    fstream file("Data.json");
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
    cout << json << endl;

}
