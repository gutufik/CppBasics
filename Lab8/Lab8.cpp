#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cstdlib>  
#include <fstream>


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



struct Student
{
    string FIO;
    int* Marks;
    int MarksCount;

    Student(string stringStudent)
    {
        vector<string> cols = SplitString(stringStudent, "\t");

        int colsCount = cols.size();
        MarksCount = colsCount - 1;

        for (int i = 0; i < colsCount; i++)
        {
            if (i == 0)
            {
                FIO = cols[i];
                Marks = new int[colsCount - 1];
            }
            else
            {
                Marks[i - 1] = stoi(cols[i]); //stoi преобразование строки в int
            }
        }
    }
    
    float GetAverageMark() 
    {
        int sum = 0;
        if (sizeof(Marks) > 0)
        {
            for (int i = 0; i < MarksCount; i++)
            {
                sum += Marks[i];
            }
        }

        return float(sum) / float(MarksCount); //|||;
    }

    int GetTwosCount() {
        int count = 0;

        if (sizeof(Marks) > 0)
        {
            for (int i = 0; i < MarksCount; i++)
            {
                if (Marks[i] == 2) count++;
            }
        }
        return count;
    }

    string ToString()
    {
        string result = FIO;

        for (int i = 0; i < MarksCount; i++)
        {
            int li = Marks[i];
            result += "\t" + to_string(li);
        }
        result += "\t" + to_string(GetAverageMark());

        result += "\n";

        return result;
    }
};

struct Node
{
    Node* Next;

    Student* Value; Node(Student* student) {
        Next = NULL;
        Value = student;
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

    bool IsEmpty() {
        return Length == 0;
    }

    void PushBack(Student* student) {
        Node* newNode = new Node(student);

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

    Student* operator[](int index) {
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

    LinkedList* Filter(string FIO) {
        LinkedList* filteredList = new LinkedList();

        for (int i = 0; i < Length; i++) {
            if ((*this)[i]->FIO.find(FIO) != string::npos) {
                Student* stud = (*this)[i];
                filteredList->PushBack(stud);
            }
        }

        return filteredList;
    }

    LinkedList* GetStudentsWithTwos() 
    {
        LinkedList* filteredList = new LinkedList();

        for (int i = 0; i < Length; i++) {
            if ((*this)[i]->Marks) {

                Student* stud = (*this)[i];
                if (stud->GetTwosCount() > 1) {
                    filteredList->PushBack(stud);
                }
            }
        }
        return filteredList;
    }

    LinkedList* Sort() 
    {
        
    }
};


void PrintMenu() {
    system("cls");
    puts("------------------------------------------------------");
    puts(" Выберите номер пункта меню:");
    puts("1 - средние баллы студентов");
    puts("2 - информация о заданном студенте");
    puts("3 - выход");
    puts("-------------------------------------------------------");
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string line;

    fstream file("Students.txt");

    fstream output("Output.txt");

    LinkedList* students = new LinkedList();

    string header;

    bool headerPassed = false;

    if (file.fail())
    {
        cout << "Не удается открыть файл Students.txt";
        return 1;
    }

    if (file.is_open()) // Чтение файла
    {
        while (getline(file, line))
        {
            students->PushBack(new Student(line));
        }
    }
    file.close();


    for (int i = 0; i < students->Length; i++)
    {
        cout << (*students)[i]->ToString();
    }

    cout << "Поиск по фамилии\n";

    string FIO = "Калинин";
    LinkedList* filteredList = students->Filter(FIO);

    for (int i = 0; i < filteredList->Length; i++)
    {
        cout << (*filteredList)[i]->ToString();
    }

    cout << "Больше 2 2\n";

    LinkedList* withTwos = students->GetStudentsWithTwos();

    for (int i = 0; i < withTwos->Length; i++)
    {
        cout << (*withTwos)[i]->ToString();
    }

    cout << "Сортировка\n";

    for (int i = 0; i < students->Length; i++)
    {
        for (int j = 0; j < students->Length; j++)
        {
            if ((*students)[i]->GetAverageMark() >(*students)[j]->GetAverageMark())
            {
                swap(*(*students)[i], *(*students)[j]);
            }
        }
    }

    for (int i = 0; i < students->Length; i++)
    {
        cout << (*students)[i]->ToString();
    }


}
