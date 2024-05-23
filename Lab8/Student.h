#include <string>
#include <vector>
#include "Split.h"

using namespace std;

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

        return float(sum) / float(MarksCount);
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

