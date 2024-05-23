#include "Node.h"
#include <string> 
#include <fstream>

using namespace std;

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
};