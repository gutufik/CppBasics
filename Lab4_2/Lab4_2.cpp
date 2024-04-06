#include <iostream>

struct TabletScanner {
    char* ModelName;
    float Price;
    float HorizontalSize;
    float VerticalSize;
};


struct Node {
    Node* Next;
    TabletScanner* Value;

    Node(TabletScanner* scanner) {
        Next = NULL;
        Value = scanner;
    }
};



struct LinkedList
{
    Node* Head;
    int Length;

    void PushBack(TabletScanner scanner) {

    }

    LinkedList Filter() {

    }
};


int main()
{
    std::cout << "Hello World!\n";
}
