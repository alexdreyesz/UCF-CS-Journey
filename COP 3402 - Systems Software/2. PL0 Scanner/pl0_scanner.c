//Alex Reyes
//Jesus Molina

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defince The Array Scopes
#define IDENTIFIER_LENGTH 11
#define MAX_NUM_LENGTH 5
#define MAX_LENGTH 10000

//Struct For Lexical Conventions
typedef enum {
  skipsym = 1,        // skip
  identsym = 2,       // Letter {letter | Digit}
  numbersym = 3,      // Digit {Digit}
  plussym = 4,        // +
  minussym = 5,       // - 
  multsym = 6,        // *
  slashsym = 7,       // /
  fisym = 8,          // fi
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
  callsym = 27,       // call
  constsym = 28,      // const
  varsym = 29,        // var
  procsym = 30,       // procedure
  writesym = 31,      // write
  readsym = 32,       // read
  elsesym = 33        // else
} token_type;

// Function To Process File 
void lexAnalyzer(FILE *fp){
    char buffer[MAX_LENGTH] = {0}; // Buffer To Handle File Data
    int index = 0; // Index To Handle Buffer 
    char ch; // Character To Handle Delimeters 
    int isComment = 0; // Flag To Handle Comments
    int isNumber = 0;

    char tokenList[MAX_LENGTH] = {0}; // Array To Store The Token List
    int tokenIndex = 0; // Token List Index To keep Track Of Position And Size

    char numArr[100] = {0}; // Array To Store The Number
    int tempValue = 0; // Temporary Value 

    // Read File Character By Character 
    while ((ch = fgetc(fp)) != EOF) {
          // Check If Character Is Alphanumerical
          if (isalnum(ch)) {
              if (index == 0) {
                  isNumber = isdigit(ch); // Check If First Character Is A Digit
              } else if (isNumber && !isdigit(ch)) { // Check If Character Is Not A Digit
                  buffer[index] = '\0'; // Null Terminate The Buffer

                  // Test If Word Is Not Greather Than The Max Lenght Permitted For Letters
                  if(strlen(buffer) > IDENTIFIER_LENGTH){
                    printf("%-13s Error: Name too long\n", buffer);
                    goto jump_to; // Avoid All Nested Ifs If This Condition Was Reached And Go To Jump To
                  }

                  // Test If Word Is Not Greather Than The Max Lenght Permitted For Digits
                  if(isdigit(buffer[0]) && strlen(buffer) > MAX_NUM_LENGTH){ 
                    printf("%-13s Error: Number too long\n", buffer);
                    goto jump_to; // Avoid All Nested Ifs If This Condition Was Reached And Go To Jump TO
                  }

                  tempValue = atoi(buffer); // Store The Temporary Value Convert Character Of Buffer To Digit With Atoi
                  printf("%-13d %d\n", tempValue, numbersym);
                
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

                  jump_to: // Skip Was Reached Avoided All Nested Ifs As A Exception Was Found 

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
                if(isComment == 1){
                  goto end_of_nested_ifs; // Avoid All Nested Ifs If This Condition Was Reached And Go To Skip
                }

                // Test If Word Is Not Greather Than The Max Lenght Permitted For Letters
                if(strlen(buffer) > IDENTIFIER_LENGTH){
                  printf("%-13s Error: Name too long\n", buffer);
                  goto end_of_nested_ifs; // Avoid All Nested Ifs If This Condition Was Reached And Go To Skip
                }

                // Test If Word Is Not Greather Than The Max Lenght Permitted For Digits
                if(isdigit(buffer[0]) && strlen(buffer) > MAX_NUM_LENGTH){ 
                  printf("%-13s Error: Number too long\n", buffer);
                  goto end_of_nested_ifs; // Avoid All Nested Ifs If This Condition Was Reached And Go To Skip
                }

                // Compare The Word And Find Its Token Type
                if (strcmp(buffer, "fi") == 0) { // Lexical Convention 8 fisym
                  printf("%-13s %d\n", buffer, fisym); 
                  
                  sprintf(numArr, "%d", fisym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  } 
                  
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "begin") == 0) { // Lexical Convention 21 beginsym
                  printf("%-13s %d\n", buffer, beginsym);
                  
                  sprintf(numArr, "%d", beginsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++; 
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "end") == 0) { // Lexical Convention 22 endsym
                  printf("%-13s %d\n", buffer, endsym);
                  
                  sprintf(numArr, "%d", endsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++; 
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "if") == 0) { // Lexical Convention 23 ifsym
                  printf("%-13s %d\n", buffer, ifsym); 
                  
                  sprintf(numArr, "%d", ifsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "then") == 0) { // Lexical Convention 24 thensym
                  printf("%-13s %d\n", buffer, thensym); 
                  
                  sprintf(numArr, "%d", thensym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "while") == 0) { // Lexical Convention 25 whilesym
                  printf("%-13s %d\n", buffer, whilesym); 
                  
                  sprintf(numArr, "%d", whilesym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "do") == 0) { // Lexical Convention 26  dosym
                  printf("%-13s %d\n", buffer, dosym); 
                  
                  sprintf(numArr, "%d", dosym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "call") == 0) { // Lexical Convention 27 callsym
                  printf("%-13s %d\n", buffer, callsym);
                  
                  sprintf(numArr, "%d", callsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "const") == 0) { // Lexical Convention 28 constsym
                  printf("%-13s %d\n", buffer, constsym);
                  
                  sprintf(numArr, "%d", constsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "var") == 0) { // Lexical Convention 29 varsym
                  printf("%-13s %d\n", buffer, varsym);
                  
                  sprintf(numArr, "%d", varsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "procedure") == 0) { // Lexical Convention 30 procsym
                  printf("%-13s %d\n", buffer, procsym);
                  
                  sprintf(numArr, "%d", procsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else if (strcmp(buffer, "write") == 0) { // Lexical Convention 31 writesym
                  printf("%-13s %d\n", buffer, writesym);
                  
                  sprintf(numArr, "%d", writesym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                }  else if (strcmp(buffer, "read") == 0) { // Lexical Convention 32 readsym
                  printf("%-13s %d\n", buffer, readsym);
                  
                  sprintf(numArr, "%d", readsym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i];
                      tokenIndex++;
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                }  else if (strcmp(buffer, "else") == 0) { // Lexical Convention 33 elsesym
                  printf("%-13s %d\n", buffer, elsesym);
                  
                  sprintf(numArr, "%d", elsesym);
                  for(int i = 0; i < strlen(numArr); i++){
                      tokenList[tokenIndex] = numArr[i]; // If Word Match Set Its Appropiate Type Value To Token List
                      tokenIndex++; // Update Token List Index
                  }
              
                  tokenList[tokenIndex] = ' ';
                  tokenIndex++;
                } else { // Lexical Convention 2 & 3
                  // Compare If The Character Is A Digit Or A Letter 
                  if(isdigit(buffer[0])){ // Lexical Convention 3 numbersym
                    printf("%-13s %d\n", buffer, numbersym);
                    
                    sprintf(numArr, "%d", numbersym);
                    for(int i = 0; i < strlen(numArr); i++){
                        tokenList[tokenIndex] = numArr[i]; 
                        tokenIndex++;
                    }
                    
                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;

                    tempValue = atoi(buffer); // Store The Temporary Value Convert Character Of Buffer To Digit With Atoi
                    
                    sprintf(numArr, "%d", tempValue);
                    
                    for(int i = 0; i < strlen(numArr); i++){
                        tokenList[tokenIndex] = numArr[i]; 
                        tokenIndex++;
                    }

                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;
                  } else { // Lexical Convention 2 identsym
                    printf("%-13s %d\n", buffer, identsym); 
                    
                    sprintf(numArr, "%d", identsym);
                    for(int i = 0; i < strlen(numArr); i++){
                        tokenList[tokenIndex] = numArr[i]; 
                        tokenIndex++;
                    }
                    
                    tokenList[tokenIndex] = ' ';
                    tokenIndex++;

                    // Loop Through The Variable Word And Store Them In The Token List As One Word
                    for(int i = 0; i < strlen(buffer); i++) {
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
                switch(ch) {
                    case '+': // Lexical Convention 4 plussym
                        printf("%-13c %d\n", ch, plussym);
                        
                        sprintf(numArr, "%d", plussym);
                        for(int i = 0; i < strlen(numArr); i++){
                            tokenList[tokenIndex] = numArr[i]; 
                            tokenIndex++; 
                        }
                      
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                        break;
                  
                    case '-':  // Lexical Convention 5 minussym
                        printf("%-13c %d\n", ch, minussym);
                        
                        sprintf(numArr, "%d", minussym);
                        for(int i = 0; i < strlen(numArr); i++){
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
                        } else {
                            ungetc(ch, fp); // If Next Character Does Not Equal = Then Unget The Character Back To The File
                            printf("* %13d\n", multsym);
                         
                            sprintf(numArr, "%d", multsym);
                            for(int i = 0; i < strlen(numArr); i++){
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
                        } else {
                            ungetc(ch, fp); // If Next Character Does Not Equal / Then Unget The Character Back To The File
                            printf("/ %13d\n", slashsym);
                      
                            sprintf(numArr, "%d", slashsym);
                            for(int i = 0; i < strlen(numArr); i++){
                            tokenList[tokenIndex] = numArr[i]; 
                            tokenIndex++;
                      }
                            tokenList[tokenIndex] = ' ';
                            tokenIndex++;
                        }
                        break;
                  
                    case '=': // Lexical Convention 9 eqlsym
                        printf("%-13c %d\n", ch, eqlsym);
                      
                        sprintf(numArr, "%d", eqlsym);
                        for(int i = 0; i < strlen(numArr); i++){
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
                            printf("<> %13d\n",  neqsym);
                          
                            sprintf(numArr, "%d", neqsym);
                            for(int i = 0; i < strlen(numArr); i++){
                                tokenList[tokenIndex] = numArr[i];
                                tokenIndex++; 
                            }
                          
                            tokenList[tokenIndex] = ' ';
                            tokenIndex++;
                        } else if (ch == '=') { // Lexical Convention 12 leqsym
                            printf("<= %13d\n",  leqsym);
                          
                            sprintf(numArr, "%d", leqsym);
                            for(int i = 0; i < strlen(numArr); i++){
                                tokenList[tokenIndex] = numArr[i]; 
                                tokenIndex++; 
                          }
                            tokenList[tokenIndex] = ' ';
                            tokenIndex++;
                        } else { // Lexical Convention 11 lessym
                            ungetc(ch, fp); // If Next Character Does Not Equal = or < Then Unget The Character Back To The File
                            printf("<  %13d\n", lessym); 
                            
                            sprintf(numArr, "%d", lessym);
                            for(int i = 0; i < strlen(numArr); i++){
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
                            printf(">= %13d\n",  geqsym); 
                            
                            sprintf(numArr, "%d", geqsym);
                            for(int i = 0; i < strlen(numArr); i++){
                                tokenList[tokenIndex] = numArr[i]; // If Word Match Set Its Appropiate Type Value To Token List
                                tokenIndex++; 
                            }
                          
                            tokenList[tokenIndex] = ' ';
                            tokenIndex++;
                        } else { // Lexical Convention 13 gtrsym
                            ungetc(ch, fp); // If Next Character Does Not Equal = Then Unget The Character Back To The File
                            printf(">  %13d\n", gtrsym);
                            
                            sprintf(numArr, "%d", gtrsym);
                            for(int i = 0; i < strlen(numArr); i++){
                                tokenList[tokenIndex] = numArr[i]; 
                                tokenIndex++; 
                            } 
                          
                            tokenList[tokenIndex] = ' ';
                            tokenIndex++;
                        }
                        break;
                  
                    case '(': // Lexical Convention 15 lparentsym
                        printf("%-13c %d\n", ch, lparentsym);
                        
                        sprintf(numArr, "%d", lparentsym);
                        for(int i = 0; i < strlen(numArr); i++){
                            tokenList[tokenIndex] = numArr[i]; 
                            tokenIndex++; 
                        }
                      
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                        break;
                  
                    case ')': // Lexical Convention 16 rparentsym
                        printf("%-13c %d\n", ch, rparentsym);
                      
                        sprintf(numArr, "%d", rparentsym);
                        for(int i = 0; i < strlen(numArr); i++){
                          tokenList[tokenIndex] = numArr[i];
                          tokenIndex++; 
                        }
                      
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                        break;   
                  
                    case ',': // Lexical Convention 17 commasym
                        printf("%-13c %d\n", ch, commasym);
                      
                        sprintf(numArr, "%d", commasym);
                        for(int i = 0; i < strlen(numArr); i++){
                            tokenList[tokenIndex] = numArr[i];
                            tokenIndex++;
                        }
                      
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                        break;       
                  
                    case ';': // Lexical Convention 18 semicolonsym
                        printf("%-13c %d\n", ch, semicolonsym);
                      
                        sprintf(numArr, "%d", semicolonsym);
                        for(int i = 0; i < strlen(numArr); i++){
                            tokenList[tokenIndex] = numArr[i]; 
                            tokenIndex++;
                        }
                      
                        tokenList[tokenIndex] = ' ';
                        tokenIndex++;
                        break;
                  
                    case '.': // Lexical Convention 19 periodsym
                        printf("%-13c %d\n", ch, periodsym);
                      
                        sprintf(numArr, "%d", periodsym);
                        for(int i = 0; i < strlen(numArr); i++){
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
                            printf(":= %13d\n", becomessym); 
                          
                            sprintf(numArr, "%d", becomessym);
                            for(int i = 0; i < strlen(numArr); i++){
                                tokenList[tokenIndex] = numArr[i]; // If Word Match Set Its Appropiate Type Value To Token List
                                tokenIndex++; // Update Token List Index
                            }
                          
                            tokenList[tokenIndex] = ' ';
                            tokenIndex++;
                        } else {
                            ungetc(ch, fp); // If Next Character Does Not Equal = Then Unget The Character Back To The File
                        }
                        break;
                  
                    default: // If The Symbol Was Not Recognized Then Print Error
                        printf("%-13c Error: Invalid Symbol\n", ch);
                        break;
                }
            }
        }
    }

    printf("\nToken List:\n");
  
    // Print The Token List
    for(int i = 0; i < tokenIndex; i++){
        printf("%c", tokenList[i]);
    }
     
  printf("\n"); // Adjust Last Line
}

int main(int argc, char *argv[]) {
  //Ask For Input To Open Desired File
  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
      printf("Unable to open file\n");
      return 1;
  }

  printf("Source Program:\n");

  // Print The File As It Is
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
      putchar(ch);
  }

  rewind(fp); // Rewind The File Pointer To The Beginning Of The File

  printf("\n\nLexeme Table:\n\n");

  printf("lexeme token type\n");

  lexAnalyzer(fp); // Call The Process File Function

  fclose(fp); // Close The File 

  return 0; // Return 0 If Program Runs Succefully
}