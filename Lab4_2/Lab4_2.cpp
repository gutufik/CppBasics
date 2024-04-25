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

    if (scannerList->IsEmpty()) {
        cout << "Исходный файл с данными пустой\n";
        return 1;
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
    else cout << "Сканеры, удовлетворяющие условию \n";
    for (int i = 0; i < filteredList->Length; i++) {
        cout << (*filteredList)[i]->ToString();
    }

    return 0;
}