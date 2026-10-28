#include <bits/stdc++.h>
using namespace std;

enum TokenType {
    SEMICOLON,IF,THEN,END,REPEAT,UNTIL,IDENTIFIER,
    ASSIGN,READ,WRITE,LESSTHAN,EQUAL,PLUS,MINUS,
    MULT,DIV,OPENBRACKET,CLOSEDBRACKET,NUMBER,ENDFILE, ERROR
};
struct TokenRecord {
    string value;
    TokenType type;
};
TokenType CheckKeyword(string word);
TokenType CheckSymbol(char symbol);
string ScanNumber(ifstream& file, char firstChar);
string ScanIdentifier(ifstream& file, char firstChar);
TokenRecord GetToken(ifstream& file){
    TokenRecord currentToken;
    char c;
    while (file.get(c)) {
        if (c == ' ' || c == '\n' || c == '\t') {
            continue;
        }
        if (isalpha(c)) {
            currentToken.value = ScanIdentifier(file, c);
            currentToken.type = CheckKeyword(currentToken.value);
        }
        else if (isdigit(c)) {
            currentToken.value = ScanNumber(file, c);
            currentToken.type = NUMBER;
        }
        else {
            if (c == ':') {
                char nextC;
                if (file.get(nextC) && nextC == '=') {
                    currentToken.value = ":=";
                    currentToken.type = ASSIGN;
                } else {
                    file.unget(); // typing error
                    currentToken.value = ":";
                    currentToken.type = ERROR;
                }
            } else {
                currentToken.value = string(1, c);
                currentToken.type = CheckSymbol(c);
            }
        }

        break;
    }
    if (file.eof()) {
        currentToken.type = ENDFILE;
    }
    return currentToken;
}

int main() {
    return 0;
}