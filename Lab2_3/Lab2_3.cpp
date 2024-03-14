#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <Windows.h>
#include <vector>


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

string ClearString(string s, string del)
{
    string vowelLetters = "����������aeiouy";

    string result;

    vector<string> words = SplitString(s, del);

    for (string word : words) 
    {
        if (vowelLetters.find(tolower(word[word.length() - 1])) == string::npos)
        {
            if (result == "") result = word;
            else result += del + word;

        }
    }
    return result;
}


int main()
{
    SetConsoleCP(1251); // Console input encoded in 1251
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    char str[100];
    char del[100];

    cout << "������� ����������� ���� \n";
    gets_s(del);

    if (!((string)del).compare(""))
    {
        cout << "����������� �� ����� ���� ������";
        return 1;
    }

    cout << "������� ������ \n";
    gets_s(str);

    if (!((string)str).compare(""))
    {
        cout << "������ �� ����� ���� ������";
        return 1;
    }
    
    cout << "������ ��� ����, ��������������� �� ������� �����\n";
    cout << ClearString(str, del);

    return 0;
}

