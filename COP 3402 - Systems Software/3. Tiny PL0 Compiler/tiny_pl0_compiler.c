//Alex Reyes
//Jesus Molina

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Defince The Array Scopes
#define IDENTIFIER_LENGTH 11
#define MAX_NUM_LENGTH 5
#define MAX_LENGTH 10000
#define MAX_SYMBOL_TABLE_SIZE 5000 
#define MAX_TOKENS 5000

//Struct For Lexical Conventions
typedef enum {
    oddsym = 1,         // oddsym Replaced skipsym
    identsym = 2,       // Letter {letter | Digit}
    numbersym = 3,      // Digit {Digit}
    plussym = 4,        // 
    minussym = 5,       // - 
    multsym = 6,        // *
    slashsym = 7,       // /
    fisym = 8,          // fisym
    eqlsym = 9,         // =
    neqsym = 10,        // <>
    lessym = 11,        // <
    leqsym = 12,        // <=
    gtrsym = 13,        // >
    geqsym = 14,        // >=
    lparentsym = 15,    // (
    rparentsym = 16,    // )
    commasym = 17,      // ,
    semicolonsym = 18,  // ;
    periodsym = 19,     // .
    becomessym = 20,    // :=
    beginsym = 21,      // begin
    endsym = 22,        // end
    ifsym = 23,         // if 
    thensym = 24,       // then
    whilesym = 25,      // while
    dosym = 26,         // do 
    // callsym = 27,    // Deleted HW3 call
    constsym = 28,      // const
    varsym = 29,        // var
    // procsym = 30,    // Deleted HW3 procedure
    writesym = 31,      // write
    readsym = 32,       // read
    // elsesym = 33     // Deleted HW3 else
} token_type;

//Struct For Symbols 
typedef struct {
    int kind; // const = 1, var = 2, proc = 3
    char name[10]; // Name Up To 11 Chars
    int val; // Number (ASCII value)
    int level; // L Level
    int addr; // M Address
    int mark; // To Indicate Unavailable Or Deleted
} symbol;

//Struct For Instructions Table 
typedef struct {
    char OP[IDENTIFIER_LENGTH];
    int L;
    int M;
} instructions;

//Global Variables
//Symbol Table
symbol symbolTable[MAX_SYMBOL_TABLE_SIZE] = { 0 }; // Array To Store The Table List
int symbolTableIndex = 0; // Table Size Index To keep Track Of Position And Size
int addSymbolIndex = 0; // Add Symbol Index To Keep Track Of Position And Size Of Added Symbols

// Token List
char tokenList[MAX_LENGTH] = { 0 }; // Array To Store The Token List
int tokenIndex = 0; // Token List Index To keep Track Of Position And Size

// Token List Of Strings
char tokenStrings[MAX_TOKENS][IDENTIFIER_LENGTH];
int amountOfTokens = 0;

// Instructions List
instructions instructionsList[MAX_LENGTH] = { 0 }; // Array To Store The Instructions List
int instructionsListIndex = 0; // Instructions Index To keep Track Of Position And Size

// Function Declarations 
void lexAnalyzer(FILE* fp);
int SYMBOLTABLECHECK(char* name);
void PROGRAM();
void BLOCK();
void CONST_DECLARATION();
int VAR_DECLARATION();
void STATEMENT();
void CONDITION();
void EXPRESSION();
void TERM();
void FACTOR();
void emit(char* OP, int L, int M);
void addSymbol(int kind, char* name, int val, int level, int addr, int mark);
void tokenToString();
void printSource(FILE* fp);
void printSymbolTable();

// Pass Token List To String List For Easier Formatting 
void tokenToString() {
    // Split The Input String Into Tokens
    char* token = strtok(tokenList, " ");
    int tokenCount = 0;

    // Iterate Through The Tokens
    while (token != NULL) {

        strcpy(tokenStrings[tokenCount], token); // Copy The Token To The Current String List

        tokenCount++; // Increase The String Count

        token = strtok(NULL, " "); // Get The Next Token
    }
}

//Linear Search Through Symbol Table Looking At Name
int SYMBOLTABLECHECK(char* name) {
    // Variables To Handle The Size And Index 
    int tokenIndex = 0;
    int listSize = 0;
    bool isFound = false;

    listSize = sizeof(symbolTable) / sizeof(symbolTable[0]); // Accomodate The Size Of The List Divide By The Amount Of Elements On Each Struct

    // Iterate Through The Symbol Table
    for (int i = 0; i < listSize; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            tokenIndex = i;
            isFound = true;
        }
    }

    //Return Index If Found, -1 If Not
    if (isFound == true) {
        return tokenIndex;
    }
    else {
        return -1;
    }
}

//Linear Search Through Symbol Table Looking At Name
void PROGRAM() {
    emit("JMP", 0, 3);

    BLOCK();

    if (atoi(tokenStrings[symbolTableIndex]) != periodsym) {
        printf("Error: Program Must End With A Period\n");
        exit(0);
    }

    emit("SYS", 0, 3);
}

// Create The Chart For Storing The Variable 
void BLOCK() {
    CONST_DECLARATION();

    int numVars = VAR_DECLARATION();

    emit("INC", 0, (3 + numVars));

    STATEMENT();
}

// Check If The Current Token Is To Be A Constant 
void CONST_DECLARATION() {
    // Check If The Current Token Is 'const' 
    if (atoi(tokenStrings[symbolTableIndex]) == constsym) {
        do {
            symbolTableIndex++;

            if (atoi(tokenStrings[symbolTableIndex]) != identsym) {
                printf("Error: Identifier expected after 'const'\n");
                exit(0);
            }

            symbolTableIndex++;

            char savedName[IDENTIFIER_LENGTH] = { 0 };

            strcpy(savedName, tokenStrings[symbolTableIndex]);

            symbolTableIndex++;

            if (atoi(tokenStrings[symbolTableIndex]) != eqlsym) {
                printf("Error: '=' expected after identifier\n");
                exit(0);
            }

            symbolTableIndex++;

            if (atoi(tokenStrings[symbolTableIndex]) != numbersym) {
                printf("Error: Number expected after '='\n");
                exit(0);
            }

            symbolTableIndex++;


            addSymbol(1, savedName, atoi(tokenStrings[symbolTableIndex]), 0, 0, 0);

            symbolTableIndex++;
        } while (atoi(tokenStrings[symbolTableIndex]) == commasym);

        if (atoi(tokenStrings[symbolTableIndex]) != semicolonsym) {
            printf("Error: ';' expected after constant declaration\n");
            exit(0);
        }

        symbolTableIndex++;
    }
}

// Check If The Current Token Is To Be A Variable 
int VAR_DECLARATION() {
    int numVars = 0;

    // Check If The Current Token Is 'var' 
    if (atoi(tokenStrings[symbolTableIndex]) == varsym) {
        do {
            numVars++;

            symbolTableIndex++;

            if (atoi(tokenStrings[symbolTableIndex]) != identsym) {
                printf("Error: Identifier expected after 'var'\n");
                exit(0);
            }

            symbolTableIndex++;

            if (SYMBOLTABLECHECK(tokenStrings[symbolTableIndex]) != -1) {
                printf("Error: Duplicate variable declaration\n");
                exit(0);
            }

            char identName[IDENTIFIER_LENGTH] = { 0 };

            strcpy(identName, tokenStrings[symbolTableIndex]);

            addSymbol(2, identName, 0, 0, (numVars + 2), 0);

            symbolTableIndex++;
        } while (atoi(tokenStrings[symbolTableIndex]) == commasym);

        if (atoi(tokenStrings[symbolTableIndex]) != semicolonsym) {
            printf("Error: ';' expected after variable declaration\n");
            exit(0);
        }

        symbolTableIndex++;
    }

    return numVars;
}

// Handle Multiple Statements Functions 
void STATEMENT() {
    // Check If The Current Token Is An Idendtifier
    if (atoi(tokenStrings[symbolTableIndex]) == identsym) {
        char identifierName[IDENTIFIER_LENGTH + 1];

        symbolTableIndex++;

        // Get The Identifier Index From The Chart
        int symIdx = SYMBOLTABLECHECK(tokenStrings[symbolTableIndex]);

        if (symIdx == -1) {
            printf("Error: unknown identifier: %s", tokenStrings[symbolTableIndex]);
            exit(0);
        }

        if (symbolTable[symIdx].kind != 2) {
            printf("Assignment to non-variable");
            exit(0);
        }

        symbolTableIndex++;

        if (atoi(tokenStrings[symbolTableIndex]) != becomessym) {
            printf("':=' expected");
            exit(0);
        }

        symbolTableIndex++;

        EXPRESSION();

        emit("STO", 0, (symbolTable[symIdx].addr));

        return;
    }

    // Check If The Current Token Is "begin"
    if (atoi(tokenStrings[symbolTableIndex]) == beginsym) {
        do {
            symbolTableIndex++;

            STATEMENT();
        } while (atoi(tokenStrings[symbolTableIndex]) == semicolonsym);

        if (atoi(tokenStrings[symbolTableIndex]) != endsym) {
            printf("'end' expected");
            exit(0);
        }

        symbolTableIndex++;

        return;
    }

    // Check If The Current Token Is "if"
    if (atoi(tokenStrings[symbolTableIndex]) == ifsym) {
        symbolTableIndex++;

        CONDITION();

        int jpcIdx = instructionsListIndex;

        emit("JPC", 0, (instructionsList[jpcIdx].M));

        if (atoi(tokenStrings[symbolTableIndex]) != thensym) {
            printf("'then' expected");
            exit(0);
        }

        symbolTableIndex++;

        STATEMENT();

        if (atoi(tokenStrings[symbolTableIndex]) != fisym) {
            printf("'then' expected");
            exit(0);
        }

        symbolTableIndex++;

        instructionsList[jpcIdx].M = instructionsListIndex * 3;

        return;
    }

    // Check If The Current Token Is "while"
    if (atoi(tokenStrings[symbolTableIndex]) == whilesym) {
        symbolTableIndex++;

        int loopIdx = instructionsListIndex;

        CONDITION();

        if (atoi(tokenStrings[symbolTableIndex]) != dosym) {
            printf("'do' expected");
            exit(0);
        }

        symbolTableIndex++;

        int jpcIdx = instructionsListIndex;

        emit("JPC", 0, (instructionsList[jpcIdx].M));

        STATEMENT();

        emit("JMP", 0, loopIdx * 3);

        instructionsList[jpcIdx].M = instructionsListIndex * 3;

        return;
    }

    // Check If The Current Token Is "read"
    if (atoi(tokenStrings[symbolTableIndex]) == readsym) {
        symbolTableIndex++;

        if (atoi(tokenStrings[symbolTableIndex]) != identsym) {
            printf("Identifier expected");
            exit(0);
        }

        symbolTableIndex++;

        int symIdx = SYMBOLTABLECHECK(tokenStrings[symbolTableIndex]);

        if (symIdx == -1) {
            printf("Identifier not found");
            exit(0);
        }

        if (symbolTable[symIdx].kind != 2) {
            printf("Assignment to non-variable");
            exit(0);
        }

        symbolTableIndex++;

        emit("SIN", 0, 2);

        emit("STO", 0, symbolTable[symIdx].addr);

        return;
    }

    // Check If The Current Token Is An "write"
    if (atoi(tokenStrings[symbolTableIndex]) == writesym) {
        symbolTableIndex++;

        EXPRESSION();

        emit("SOU", 0, 1);

        return;
    }

}

//Check For The Current Token And Its Condition
void CONDITION() {
    // Check If The Current Token Is An "odd" 
    if (atoi(tokenStrings[symbolTableIndex]) == oddsym) {
        symbolTableIndex++;

        EXPRESSION();

        emit("ODD", 0, 11);
    }
    else { // If The Current Token Is Not "odd" 

        EXPRESSION();

        if (atoi(tokenStrings[symbolTableIndex]) == eqlsym) { // Check If The Current Token Is An "="
            symbolTableIndex++;

            EXPRESSION();

            emit("EQL", 0, 5);
        }
        else if (atoi(tokenStrings[symbolTableIndex]) == neqsym) { // Check If The Current Token Is An "<>"
            symbolTableIndex++;

            EXPRESSION();

            emit("NEQ", 0, 6);
        }
        else if (atoi(tokenStrings[symbolTableIndex]) == lessym) { // Check If The Current Token Is An "<"
            symbolTableIndex++;

            EXPRESSION();

            emit("LSS", 0, 7);
        }
        else if (atoi(tokenStrings[symbolTableIndex]) == leqsym) { // Check If The Current Token Is An "<="
            symbolTableIndex++;

            EXPRESSION();

            emit("LEQ", 0, 8);
        }
        else if (atoi(tokenStrings[symbolTableIndex]) == gtrsym) { // Check If The Current Token Is An ">"
            symbolTableIndex++;

            EXPRESSION();

            emit("GTR", 0, 9);
        }
        else if (atoi(tokenStrings[symbolTableIndex]) == geqsym) { // Check If The Current Token Is An ">="
            symbolTableIndex++;

            EXPRESSION();

            emit("GEQ", 0, 10);
        }
        else { // Invalid Character 
            printf("Error: Invalid Condition");
            exit(0);
        }
    }
}

//Check For The Current Token And Its Expression
void EXPRESSION() {
    // Check If The Current Token Is An "-"
    if (atoi(tokenStrings[symbolTableIndex]) == minussym) {
        symbolTableIndex++;

        TERM();

        emit("NEG", 0, 6);

        while (atoi(tokenStrings[symbolTableIndex]) == plussym || atoi(tokenStrings[symbolTableIndex]) == minussym) {
            if (atoi(tokenStrings[symbolTableIndex]) == plussym) {
                symbolTableIndex++;

                TERM();

                emit("ADD", 0, 1);
            }
            else {
                symbolTableIndex++;

                TERM();

                emit("SUB", 0, 2);
            }
        }


    }
    else { // If The Current Token Is Not "-"
        // Check If The Current Token Is An "+"
        if (atoi(tokenStrings[symbolTableIndex]) == plussym) {
            symbolTableIndex++;
        }

        TERM();

        // Loop If The Current Token Is An "+" Or "-"
        while (atoi(tokenStrings[symbolTableIndex]) == plussym || atoi(tokenStrings[symbolTableIndex]) == minussym) {
            // Check If The Current Token Is An "+"
            if (atoi(tokenStrings[symbolTableIndex]) == plussym) {
                symbolTableIndex++;

                TERM();

                emit("ADD", 0, 1);
            }
            else {
                symbolTableIndex++;

                TERM();

                emit("SUB", 0, 2);
            }
        }
    }
}

//Check For The Current Token And Its Term
void TERM() {
    FACTOR();

    // Loop If The Current Token Is An "*" Or "/"
    while (atoi(tokenStrings[symbolTableIndex]) == multsym || atoi(tokenStrings[symbolTableIndex]) == slashsym) {
        // Check If The Current Token Is An "*"
        if (atoi(tokenStrings[symbolTableIndex]) == multsym) {
            symbolTableIndex++;

            FACTOR();

            emit("MUL", 0, 3);
        }
        else if (atoi(tokenStrings[symbolTableIndex]) == slashsym) {
            symbolTableIndex++;

            FACTOR();

            emit("DIV", 0, 4);
        }
    }
}

//Linear Search Through Symbol Table Looking At Name
void FACTOR() {
    int symIdx = 0;

    // Check If The Current Token Is An Identifier 
    if (atoi(tokenStrings[symbolTableIndex]) == identsym) {
        symbolTableIndex++;

        symIdx = SYMBOLTABLECHECK(tokenStrings[symbolTableIndex]);

        if (symIdx == -1) {
            printf("Undefined Identifier");
            exit(0);
        }

        if (symbolTable[symIdx].kind == 1) { // Token is a "const"
            emit("LIT", 0, symbolTable[symIdx].val);
        }
        else { // Token is a "var" or "procedure"
            emit("LOD", 0, symbolTable[symIdx].addr);
        }

        symbolTableIndex++;

    }
    else if (atoi(tokenStrings[symbolTableIndex]) == numbersym) {
        symbolTableIndex++;

        emit("LIT", 0, atoi(tokenStrings[symbolTableIndex]));

        symbolTableIndex++;

    }
    else if (atoi(tokenStrings[symbolTableIndex]) == lparentsym) {
        symbolTableIndex++;

        EXPRESSION();

        if (atoi(tokenStrings[symbolTableIndex]) != rparentsym) {
            printf("Right Parenthesis Expected");
        }

        symbolTableIndex++;
    }
    else {
        printf("Error: Undeclared Identifier");
        exit(0);
    }
}

// Handle Emit Data And Add it To The Instructions Struct Array 
void emit(char* OP, int L, int M) {
    strcpy(instructionsList[instructionsListIndex].OP, OP);
    instructionsList[instructionsListIndex].L = L;
    instructionsList[instructionsListIndex].M = M;

    instructionsListIndex++;
}

// Handle Token Data And Add it To The Symbol Table Struct Array 
void addSymbol(int kind, char* name, int val, int level, int addr, int mark) {
    symbolTable[addSymbolIndex].kind = kind;
    strcpy(symbolTable[addSymbolIndex].name, name);
    symbolTable[addSymbolIndex].val = val;
    symbolTable[addSymbolIndex].level = level;
    symbolTable[addSymbolIndex].addr = addr;
    symbolTable[addSymbolIndex].mark = mark;

    addSymbolIndex++;
}

// Function To Process File 
void lexAnalyzer(FILE* fp) {
    char buffer[MAX_LENGTH] = { 0 }; // Buffer To Handle File Data
    int index = 0; // Index To Handle Buffer 
    char ch; // Character To Handle Delimeters 
    int isComment = 0; // Flag To Handle Comments
    int isNumber = 0;

    char numArr[100] = { 0 }; // Array To Store The Number
    int tempValue = 0; // Temporary Value 

    // Read File Character By Character 
    while ((ch = fgetc(fp)) != EOF) {
        // Check If Character Is Alphanumerical
        if (isalnum(ch)) {
            if (index == 0) {
                isNumber = isdigit(ch); // Check If First Character Is A Digit
            }
            else if (isNumber && !isdigit(ch)) { // Check If Character Is Not A Digit
                buffer[index] = '\0'; // Null Terminate The Buffer

                // Test If Word Is Not Greather Than The Max Lenght Permitted For Letters
                if (strlen(buffer) > IDENTIFIER_LENGTH) {
                    printf("%-13s Error: Name too long\n", buffer);
                    exit(0); // Terminate Execution
                }

                // Test If Word Is Not Greather Than The Max Lenght Permitted For Digits
                if (isdigit(buffer[0]) && strlen(buffer) > MAX_NUM_LENGTH) {
                    printf("%-13s Error: Number too long\n", buffer);
                    exit(0); // Terminate Execution
                }

                tempValue = atoi(buffer); // Store The Temporary Value Convert Character Of Buffer To Digit With Atoi

                sprintf(numArr, "%d", numbersym);  // Store Digit As A String Of Character In The Array
                for (int i = 0; i < strlen(numArr); i++) {
                    tokenList[tokenIndex] = numArr[i]; // If Word Match Set Its Appropiate Type Value To Token List
                    tokenIndex++; // Update Token List Index
                }

                tokenList[tokenIndex] = ' '; // Add Space To The Token List
                tokenIndex++; // Update Token List Index

                sprintf(numArr, "%d", tempValue);
                for (int i = 0; i < strlen(numArr); i++) {
                    tokenList[tokenIndex] = numArr[i];
                    tokenIndex++;
                }
                tokenList[tokenIndex] = ' ';
                tokenIndex++;

                memset(buffer, 0, MAX_LENGTH); // Clear The Buffer
                index = 0; // Reset Index To Zero
                isNumber = 0; // Reset Flag To Zero
            }
            buffer[index++] = ch; // Add Character To Buffer And Increment Index
        }
        // If Character Is Not Alphanumerical A Delimeter Is Found
        else {
            // If Index Is Not Zero Then The Buffer Contains A Word
            if (index > 0) {
                buffer[index] = '\0'; // Add Null Terminator To Enclose The Word

                // Test To Check If The Word Is A Comment
                if (isComment == 1) {
                    goto end_of_nested_ifs; // Avoid All Nested Ifs If This Condition Was Reached And Go To Skip
                }

                // Test If Word Is Not Greather Than The Max Lenght Permitted For Letters
                if (strlen(buffer) > IDENTIFIER_LENGTH) {
                    printf("%-13s Error: Name too long\n", buffer);
                    exit(0); // Terminate Execution
                }

                // Test If Word Is Not Greather Than The Max Lenght Permitted For Digits
                if (isdigit(buffer[0]) && strlen(buffer) > MAX_NUM_LENGTH) {
                    printf("%-13s Error: Number too long\n", buffer);
                    exit(0); // Terminate Execution
                }

                // Compare The Word And Find Its Token Type
                if (strcmp(buffer, "odd") == 0) { // Lexical Convention 1 oddsym
                    sprintf(numArr, "%d", oddsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "fi") == 0) { // Lexical Convention 8 fisym
                    sprintf(numArr, "%d", fisym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "begin") == 0) { // Lexical Convention 21 beginsym
                    sprintf(numArr, "%d", beginsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "end") == 0) { // Lexical Convention 22 endsym
                    sprintf(numArr, "%d", endsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "if") == 0) { // Lexical Convention 23 ifsym
                    sprintf(numArr, "%d", ifsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "then") == 0) { // Lexical Convention 24 thensym
                    sprintf(numArr, "%d", thensym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "while") == 0) { // Lexical Convention 25 whilesym
                    sprintf(numArr, "%d", whilesym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "do") == 0) { // Lexical Convention 26  dosym
                    sprintf(numArr, "%d", dosym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "const") == 0) { // Lexical Convention 28 constsym
                    sprintf(numArr, "%d", constsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "var") == 0) { // Lexical Convention 29 varsym
                    sprintf(numArr, "%d", varsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "write") == 0) { // Lexical Convention 31 writesym
                    sprintf(numArr, "%d", writesym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else if (strcmp(buffer, "read") == 0) { // Lexical Convention 32 readsym
                    sprintf(numArr, "%d", readsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                }
                else { // Lexical Convention 2 & 3
                    // Compare If The Character Is A Digit Or A Letter 
                    if (isdigit(buffer[0])) { // Lexical Convention 3 numbersym
                        sprintf(numArr, "%d", numbersym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;

                        tempValue = atoi(buffer); // Store The Temporary Value Convert Character Of Buffer To Digit With Atoi

                        sprintf(numArr, "%d", tempValue);

                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    else { // Lexical Convention 2 identsym
                        sprintf(numArr, "%d", identsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;

                        // Loop Through The Variable Word And Store Them In The Token List As One Word
                        for (int i = 0; i < strlen(buffer); i++) {
                            tokenList[tokenIndex] = buffer[i]; // Store The Letter To Make The Word
                            tokenIndex++; // Update Token List Index   
                        }

                        tokenList[tokenIndex] = ' '; // Add Space To The Token List For The Full Word
                        tokenIndex++; // Update Token List Index
                    }
                }

            end_of_nested_ifs: // Skip Was Reached Avoided All Nested Ifs As A Exception Was Found 

                memset(buffer, 0, MAX_LENGTH); // Clear The Buffer For The Next Word
                index = 0; // Reset The Index To 0 For The Next Word
                isNumber = 0; // Reset The Is Number Flag To 0 For The Next Word
            }
            // Check If The Ch Character Is currently An Valid Delimeter 
            if (!isspace(ch)) {
                // Search For The Given Cases If Not Found Then It Is Not A Valid Solution
                switch (ch) {
                case '+': // Lexical Convention 4 plussym
                    sprintf(numArr, "%d", plussym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case '-':  // Lexical Convention 5 minussym
                    sprintf(numArr, "%d", minussym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case '*':  // Lexical Convention 6 multsym
                    ch = fgetc(fp); // Read Next Character

                    // If Next Character equals / That Means It Is */ Meaning We Are Exiting A Comment
                    if (ch == '/') {
                        isComment = 0; // Set Comment Flag To 1 We Are Exiting A Comment
                    }
                    else {
                        ungetc(ch, fp); // If Next Character Does Not Equal = Then Unget The Character Back To The File
                        sprintf(numArr, "%d", multsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    break;

                case '/':  // Lexical Convention 7  slashsym
                    ch = fgetc(fp); // Read Next Character

                    // If Next Character equals * That Means It Is /* Meaning We Are Entering A Comment
                    if (ch == '*') {
                        isComment = 1; // Set Comment Flag To 1 We Are Inside A Commnet 
                    }
                    else {
                        ungetc(ch, fp); // If Next Character Does Not Equal / Then Unget The Character Back To The File

                        sprintf(numArr, "%d", slashsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    break;

                case '=': // Lexical Convention 9 eqlsym
                    sprintf(numArr, "%d", eqlsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case '<': // Lexical Convention 10 & 11 & 12
                    ch = fgetc(fp); // Read Next Character

                    // If Next Character equals > or = That Means It Is <> ot <= Meaning neqsym Or leqsym
                    if (ch == '>') { // Lexical Convention 10 neqsym
                        sprintf(numArr, "%d", neqsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    else if (ch == '=') { // Lexical Convention 12 leqsym
                        sprintf(numArr, "%d", leqsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    else { // Lexical Convention 11 lessym
                        ungetc(ch, fp); // If Next Character Does Not Equal = or < Then Unget The Character Back To The File

                        sprintf(numArr, "%d", lessym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    break;

                case '>': // Lexical Convention 13 & 14
                    ch = fgetc(fp); // Read Next Character

                    // If Next Character equals = That Means It >= Meaning neqsym Or leqsym
                    if (ch == '=') { // Lexical Convention 14 geqsym 
                        sprintf(numArr, "%d", geqsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i]; // If Word Match Set Its Appropiate Type Value To Token List
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    else { // Lexical Convention 13 gtrsym
                        ungetc(ch, fp); // If Next Character Does Not Equal = Then Unget The Character Back To The File

                        sprintf(numArr, "%d", gtrsym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    break;

                case '(': // Lexical Convention 15 lparentsym
                    sprintf(numArr, "%d", lparentsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case ')': // Lexical Convention 16 rparentsym
                    sprintf(numArr, "%d", rparentsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case ',': // Lexical Convention 17 commasym
                    sprintf(numArr, "%d", commasym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case ';': // Lexical Convention 18 semicolonsym
                    sprintf(numArr, "%d", semicolonsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case '.': // Lexical Convention 19 periodsym
                    sprintf(numArr, "%d", periodsym);
                    for (int i = 0; i < strlen(numArr); i++) {
                        tokenList[tokenIndex] = numArr[i];
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                    break;

                case ':': // Lexical Convention 20 becomessym
                    ch = fgetc(fp); // Read Next Character

                    // If Next Character equals = That Means It Is := Meaning It Is Becomessym 
                    if (ch == '=') {
                        sprintf(numArr, "%d", becomessym);
                        for (int i = 0; i < strlen(numArr); i++) {
                            tokenList[tokenIndex] = numArr[i]; // If Word Match Set Its Appropiate Type Value To Token List
                            tokenIndex++; // Update Token List Index
                        }

                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                    }
                    else {
                        ungetc(ch, fp); // If Next Character Does Not Equal = Then Unget The Character Back To The File
                    }
                    break;

                default: // If The Symbol Was Not Recognized Then Print Error
                    printf("%-13c Error: Invalid Symbol\n", ch);
                    exit(0);
                    break;
                }
            }
        }
    }
}

void printSource(FILE* fp) {
    printf("Source Program:\n");

    // Print The File As It Is
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    printf("\n\n"); // Adjust Last Line
}

void printSymbolTable() {
    printf("LINE\tOP    L   M\n");
    int counter = 0;

    // Print The Token List
    for (int i = 0; i < instructionsListIndex; i++) {
        printf("%d\t%s   %d   %d\n", counter, instructionsList[i].OP, instructionsList[i].L, instructionsList[i].M);
        counter++;
    }

    printf("\n"); // Adjust Last Line

    printf("\nSymbol Table:\n");
    printf("\n");

    // Print The Symbol Table
    printf("Kind | Name       | Value | Level | Address | Mark\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < symbolTableIndex; i++) {
        symbolTable[i].mark = 1;

        if (symbolTable[i].kind != 0) {
            printf("%4d | %10s | %5d | %5d | %7d | %4d\n", symbolTable[i].kind, symbolTable[i].name, symbolTable[i].val, symbolTable[i].level, symbolTable[i].addr, symbolTable[i].mark);
        }
    }

    printf("\n"); // Adjust Last Line
}

int main(int argc, char* argv[]) {
    //Ask For Input To Open Desired File
    FILE* fp = fopen(argv[1], "r+");
    if (!fp) {
        printf("Unable to open file\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END); // Move The File Pointer To The End Of The File

    fputc(' ', fp); // Write The Character You Want To Insert

    rewind(fp); // Rewind The File Pointer To The Beginning Of The File

    //printSource(fp); // Print The Source File 

    rewind(fp); // Rewind The File Pointer To The Beginning Of The File

    lexAnalyzer(fp); // Call The Process File Function

    fclose(fp); // Close The File 

    tokenToString(); // Convert The Token List To A String List

    PROGRAM(); // Start The Parser Code Generator 

    printSymbolTable(); // Print The Symbol Table Filled Final Data 

    return 0; // Return 0 If Program Runs Succefully
}