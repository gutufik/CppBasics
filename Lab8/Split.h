#include <vector>
#include <string>

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