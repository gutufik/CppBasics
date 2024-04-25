#include <string>
#include <iostream>

using namespace std;

bool IsSizeValid(float size, string notValidMessage) {
    bool valid = size > 0;
    if (!valid) cout << notValidMessage;
    return valid;
}

bool TryParseFloat(string str, float& result) {
    if (sscanf_s(str.data(), "%f", &result) != 1) {
        cout << "Ќевозможно преобразовать значение в число\n";
        return false;
    }
    return true;
}
