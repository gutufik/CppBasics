#include <string>
#include "Student.h"

struct Node
{
    Node* Next;

    Student* Value; Node(Student* student) {
        Next = NULL;
        Value = student;
    }
};
