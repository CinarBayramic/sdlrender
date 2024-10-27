#include <iostream> 
#pragma warning(disable : 4996)
void tokenizeString(char* str, char**out) {
    const char* delimiters = "  "; // Define delimiters
    char* token = strtok(str, delimiters); // Get the first token
    int i = 0;
    while (token != nullptr) {
        out[i] = token;
        token = strtok(nullptr, delimiters); // Get the next token
        i++;
    }
}