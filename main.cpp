#include <bits/stdc++.h>
using namespace std;

enum TokenType {
    SEMICOLON,IF,THEN,END,REPEAT,UNTIL,IDENTIFIER,
    ASSIGN,READ,WRITE,LESSTHAN,EQUAL,PLUS,MINUS,
    MULT,DIV,OPENBRACKET,CLOSEDBRACKET,NUMBER,ENDFILE
};
struct TokenRecord {
    string value;
    TokenType type;
};
TokenType CheckKeyword(string word);
TokenType CheckSymbol(char symbol);
string ScanNumber(ifstream& file, char firstChar);
string ScanIdentifier(ifstream& file, char firstChar);
TokenRecord GetToken(ifstream& file);

int main() {
    return 0;
}