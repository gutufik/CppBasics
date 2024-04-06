#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        cout << "Не удается открыть файл";
        return 1;
    }

    if (file.is_open())
    {
        while (getline(file, line))
        {
            float fline;

            if (!TryParseFloat(line, fline)) {
                cout << "Ошибка в строке " + to_string(lineNumber);
                return 1;
            }

            if (fline > 0)
            {
                sum += stof(line);
                arr.push_back(fline); // Добавляем в исходный вектор только положительные элементы
            }
            lineNumber++;
        }
    }
    file.close();

    if (arr.size() == 0) {
        cout << "В файле нет положительных чисел";
        return 1;
    }

    float avg = sum / arr.size();

    vector<float> output;

    for (float elem : arr)
    {
        if (elem > avg) output.push_back(elem);
    }

    cout << "Среднее значение положительных чисел = " << avg << endl;

    if (output.size() == 0) {
        cout << "В файле нет чисел превышающих среднее значение\n";
        return 1;
    }

    cout << "Числа превышающие среднее значение:\n";
    for (float elem : output)
    {
        cout << elem << endl;
    }
}

