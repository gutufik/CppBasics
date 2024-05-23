#include "LinkedList.h"
#include <iostream>

using namespace std;

void PrintList(LinkedList* list)
{
    for (int i = 0; i < list->Length; i++)
    {
        cout << (*list)[i]->ToString();
    }
}