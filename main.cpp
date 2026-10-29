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
TokenType CheckKeyword(string word){
    if (word == "if") return IF;
    if (word == "then") return THEN;
    if (word == "end") return END;
    if (word == "repeat") return REPEAT;
    if (word == "until") return UNTIL;
    if (word == "read") return READ;
    if (word == "write") return WRITE;
    return IDENTIFIER;
}
TokenType CheckSymbol(char symbol){
    switch (symbol) {
        case ';': return SEMICOLON;
        case '<': return LESSTHAN;
        case '=': return EQUAL;
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return MULT;
        case '/': return DIV;
        case '(': return OPENBRACKET;
        case ')': return CLOSEDBRACKET;
        default: return ERROR;
    }
}
string ScanNumber(ifstream& file, char firstChar){
    string num = string(1, firstChar);
    char nextChar;

    while (file.get(nextChar)) {
        if (isdigit(nextChar))
            num += nextChar;
        else {
            file.unget(); // return non digit character back into the stream
            break;
        }
    }
    return num;
}
string ScanIdentifier(ifstream& file, char firstChar){
    string id = string(1, firstChar);
    char nextChar;

    while (file.get(nextChar)) {
        if (isalpha(nextChar))
            id += nextChar;
        else {
            file.unget(); // return non letter character back into the stream
            break;
        }
    }
    return id;
}
TokenRecord GetToken(ifstream& file){
    TokenRecord currentToken;
    char c;
    while (file.get(c)) {   // ignore spaces and new lines
        if (c == ' ' || c == '\n' || c == '\t') {
            continue;
        }
        if (c == '{') {     // ignore comments
            while (file.get(c)) {
                if (c == '}')
                    break;
            }
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
            if (c == ':') {     // handle assign operator
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
string tokenNames[] = { // mapping enumerable integer values to their respective token types
    "SEMICOLON", "IF", "THEN", "END", "REPEAT", "UNTIL", "IDENTIFIER",
    "ASSIGN", "READ", "WRITE", "LESSTHAN", "EQUAL", "PLUS", "MINUS",
    "MULT", "DIV", "OPENBRACKET", "CLOSEDBRACKET", "NUMBER", "ENDFILE", "ERROR"
};
int main() {
    ifstream inputFile("input.txt");
    ofstream fileout("tokens.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    while (!inputFile.eof()) {
        TokenRecord token = GetToken(inputFile);
        if (token.type == ENDFILE) {
            break;
        }
        fileout << token.value << " , " << tokenNames[token.type] << endl;
    }
    inputFile.close();
    fileout.close();
    return 0;
}