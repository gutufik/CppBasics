#include <iostream>
#include "TabletScanner.h"

using namespace std;

struct Node {
    Node* Next;
    TabletScanner* Value;

    Node(TabletScanner* scanner) {
        Next = NULL;
        Value = scanner;
    }
};