#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <Windows.h>

using namespace std;



vector<string> SplitString(string s, string del) {
    vector<string> words;
    int end = s.find(del);
    while (end != -1) {
        words.push_back(s.substr(0, end));
        s.erase(s.begin(), s.begin() + end + del.length());
        end = s.find(del);
    }
    words.push_back(s.substr(0, end));

    return words;
}

struct Bank
{
    string Title;
    int* Loans;
    int LoansCount;

    Bank(string stringBank)
    {
        vector<string> cols = SplitString(stringBank, "\t");

        int colsCount = cols.size();
        LoansCount = colsCount - 1;

        for (int i = 0; i < colsCount; i++)
        {
            if (i == 0)
            {
                Title = cols[i];
                Loans = new int[colsCount - 1];
            }
            else
            {
                Loans[i - 1] = stoi(cols[i]); //stoi преобразование строки в int
            }
        }
    }

    int GetLoansSum()
    {
        int sum = 0;
        if (sizeof(Loans) > 0)
        {
            for (int i = 0; i < LoansCount; i++)
            {
                sum += Loans[i];
            }
        }
        return sum;
    }

    string ToString() 
    {
        string result = Title;

        for (int i = 0; i < LoansCount; i++)
        {
            int li = Loans[i];
            result += "\t" + to_string(li);
        }
        result += "\t" + to_string(GetLoansSum());

        result += "\n";

        return result;
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string line;

    fstream file("Input.txt");

    fstream output("Output.txt");

    vector<Bank> banks;

    string header;

    bool headerPassed = false;

    if (file.fail())
    {
        cout << "Не удается открыть файл Input.txt";
        return 1;
    }
    if (output.fail())
    {
        cout << "Не удается открыть файл Output.txt";
        return 1;
    }

    if (file.is_open()) // Чтение файла
    {
        while (getline(file, line)) 
        {
            if (header == "")
            {
                header = line + "\t" + (string)"Общая сумма ссуд" + "\n";
            }
            else
            {
                banks.push_back(Bank(line));
            }
        }
    }
    file.close();

    //Сортировка

    for (int i = 0; i < banks.size(); i++)
    {
        for (int j = 0; j < banks.size() - i - 1; j++) 
        {
            if (banks[j].Title > banks[j + 1].Title)
            {
                swap(banks[j], banks[j + 1]);
            }
        }
    }

    //Запись в файл

    output << header;

    for (Bank bank : banks)
    {
        output << bank.ToString();
    }

    output.close();

    cout << "Данные успешно отформатированы и перенесены файл Output.txt" << endl;
}

