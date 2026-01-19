#ifndef HASH_CPP
#define HASH_CPP

#include <string>
#include <functional>

using namespace std;

//Simple hash function using std::hash. Turn password string input into a hashed string output
string hashString(const string& input) {
    hash<string> hasher;
    size_t hashValue = hasher(input);
    return to_string(hashValue);
}

#endif // HASH_CPP