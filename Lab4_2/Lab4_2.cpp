#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <format>
#include <iomanip>
#include <Windows.h>
#include <json/json.h>
#include <json/value.h>
#include "LinkedList.h"
#include "ValidationFunctions.h"

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    LinkedList* scannerList = new LinkedList();

    fstream file("Data.json");
    if (file.fail()) {
        cout << "�� ������� ������� ���� Data.json";
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

    if (scannerList->IsEmpty()) {
        cout << "�������� ���� � ������� ������\n";
        return 1;
    }


    string inputString;
    float minVSize, maxVSize, minHSize, maxHSize;

    cout << "������� ����������� �������������� ������\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, minHSize)) return 1;
    if (!IsSizeValid(minHSize, "������ ������ ���� ������ 0\n")) return 1;

    cout << "������� ������������ �������������� ������\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, maxHSize)) return 1;
    if (!IsSizeValid(maxHSize, "������ ������ ���� ������ 0\n")) return 1;
    if (minHSize > maxHSize) {
        cout << "������������ ������ ������ ���� ������ ������������";
        return 1;
    }

    cout << "������� ����������� ������������ ������\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, minVSize)) return 1;
    if (!IsSizeValid(minVSize, "������ ������ ���� ������ 0\n")) return 1;

    cout << "������� ������������ ������������ ������\n";
    cin >> inputString;

    if (!TryParseFloat(inputString, maxVSize)) return 1;
    if (!IsSizeValid(maxVSize, "������ ������ ���� ������ 0\n")) return 1;
    if (minVSize > maxVSize) {
        cout << "������������ ������ ������ ���� ������ ������������";
        return 1;
    }

    LinkedList* filteredList = scannerList->Filter(minVSize, maxVSize, minHSize, maxHSize);

    if (filteredList->Length == 0) cout << "������ �� �������";
    else cout << "�������, ��������������� ������� \n";
    for (int i = 0; i < filteredList->Length; i++) {
        cout << (*filteredList)[i]->ToString();
    }

    return 0;
}