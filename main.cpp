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

// ============================================================================
// 1. CheckKeyword Implementation
// Checks if the given word is a TINY reserved keyword (case-insensitive)
// ============================================================================
TokenType CheckKeyword(string word){
    string lowerWord = word;
    for (char &ch : lowerWord) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    if (lowerWord == "if") return IF;
    if (lowerWord == "then") return THEN;
    if (lowerWord == "end") return END;
    if (lowerWord == "repeat") return REPEAT;
    if (lowerWord == "until") return UNTIL;
    if (lowerWord == "read") return READ;
    if (lowerWord == "write") return WRITE;
    return IDENTIFIER;
}

// ============================================================================
// 2. CheckSymbol Implementation
// Checks if the given character is a valid TINY special symbol
// ============================================================================
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

// ============================================================================
// 3. ScanNumber Implementation
// Scans consecutive digits from the file stream and returns the number string
// ============================================================================
string ScanNumber(ifstream& file, char firstChar){
    string num = string(1, firstChar);
    char nextChar;

    while (file.get(nextChar)) {
        if (isdigit(static_cast<unsigned char>(nextChar)))
            num += nextChar;
        else {
            file.unget(); // return non digit character back into the stream
            break;
        }
    }
    return num;
}

// ============================================================================
// 4. ScanIdentifier Implementation
// Scans alphanumeric characters from the file stream and returns identifier string
// ============================================================================
string ScanIdentifier(ifstream& file, char firstChar){
    string id = string(1, firstChar);
    char nextChar;

    while (file.get(nextChar)) {
        if (isalnum(static_cast<unsigned char>(nextChar)))
            id += nextChar;
        else {
            file.unget(); // return non letter character back into the stream
            break;
        }
    }
    return id;
}

// ============================================================================
// Core GetToken Function
// ============================================================================
TokenRecord GetToken(ifstream& file){
    TokenRecord currentToken;
    char c;
    while (file.get(c)) {   // ignore spaces and new lines
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            continue;
        }
        if (c == '{') {     // ignore comments
            while (file.get(c)) {
                if (c == '}')
                    break;
            }
            if (file.eof()) break;
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

        return currentToken;
    }
    currentToken.value = "";
    currentToken.type = ENDFILE;
    return currentToken;
}

string tokenNames[] = { // mapping enumerable integer values to their respective token types
    "SEMICOLON", "IF", "THEN", "END", "REPEAT", "UNTIL", "IDENTIFIER",
    "ASSIGN", "READ", "WRITE", "LESSTHAN", "EQUAL", "PLUS", "MINUS",
    "MULT", "DIV", "OPENBRACKET", "CLOSEDBRACKET", "NUMBER", "ENDFILE", "ERROR"
};

int main(int argc, char* argv[]) {
    string inPath = "input.txt";
    string outPath = "tokens.txt";
    if (argc >= 2) inPath = argv[1];
    if (argc >= 3) outPath = argv[2];

    ifstream inputFile(inPath);
    ofstream fileout(outPath);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << inPath << endl;
        return 1;
    }

    while (!inputFile.eof()) {
        TokenRecord token = GetToken(inputFile);
        if (token.type == ENDFILE) {
            break;
        }
        fileout << token.value << " , " << tokenNames[token.type] << endl;
        cout << token.value << " , " << tokenNames[token.type] << endl;
    }
    inputFile.close();
    fileout.close();
    return 0;
}
