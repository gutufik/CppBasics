#include "Node.h"
#include <iostream>

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

    TabletScanner* operator[](int index) {
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

    LinkedList* Filter(float minVSize, float maxVSize, float minHSize, float maxHSize) {
        LinkedList* filteredList = new LinkedList();

        for (int i = 0; i < Length; i++) {
            if ((*this)[i]->VerticalSize >= minVSize &&
                (*this)[i]->VerticalSize < maxVSize &&
                (*this)[i]->HorizontalSize >= minHSize &&
                (*this)[i]->HorizontalSize < maxHSize) {

                TabletScanner* sc = (*this)[i];

                filteredList->PushBack(sc);
            }
        }


        return filteredList;
    }
};