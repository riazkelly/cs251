#include "value.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "linkedlist.h"
#include "talloc.h"

#ifndef _TOKENIZER
#define _TOKENIZER

//Helper function that adds a boolean to the front of tokensList
Value *boolean (Value *tokensList, char nextChar) {
    Value *carNode = makeNull();
    carNode -> type = BOOL_TYPE;
    nextChar = (char)fgetc(stdin);
    if(nextChar == 't') {
        carNode -> i = 1;
    }
    else if (nextChar == 'f') {
        carNode -> i = 0;
    }
    else {
        printf("Syntax Error: Invalid Boolean Identifier (boolean should be t or f).\n");
        texit(1);
    }

    //Checks for invalid input such as #tt
    nextChar = (char)fgetc(stdin);
    if (nextChar != ' ' && nextChar != ')' && nextChar != EOF && nextChar != '\n') {
        printf("Syntax Error: Invalid Boolean Identifier (boolean has too many characters).\n");
        texit(1);
    }
    ungetc(nextChar, stdin);
    return cons(carNode, tokensList);
}

//Helper function that adds a parentheses Node to the front of tokensList
Value *addParentheses (Value *tokensList, char nextChar) {
    Value *carNode = makeNull();
    switch (nextChar){
        case '(':
            carNode -> type = OPEN_TYPE;
            break;
        case ')':
            carNode -> type = CLOSE_TYPE;
            break;
    }
    return cons(carNode, tokensList);
}

//Helper function that adds a string to the front of tokensList
Value *addString (Value *tokensList, char nextChar) {
    Value *carNode = makeNull();
    carNode -> type = STR_TYPE;
    int length = 1;
    char string[301];
    string[0] = nextChar;
    nextChar = (char)fgetc(stdin);

    //Loop until we reach end of string
    while (nextChar != '"') {
        if (nextChar == EOF) {
            printf("Syntax Error: Invalid String Input\n");
            texit(1);
        }
        length++;
        string[length - 1] = nextChar;
        nextChar = (char)fgetc(stdin);
    }
    length += 2;
    string[length - 2] = nextChar;
    string[length - 1] = '\0';
    char *real_string = talloc(length * sizeof(char));
    strcpy(real_string, string);
    carNode -> s = real_string;
    return cons(carNode, tokensList);
}

//Helper function that adds an int or a double to the front of tokensList
Value *makeNumber(Value *tokensList, char nextChar) {
    Value *myNumber = makeNull();
    int length = 1;
    char myString[301];
    myString[0] = nextChar;
    bool isDouble = false;
    nextChar = (char)fgetc(stdin);

    //Loop until we reach end of number
    while (nextChar != ' ' && nextChar != '\n') {
        if (nextChar == EOF) {
            printf("Syntax error: cannot tokenize with character %c. Reached end of line without ending.\n",nextChar);
            texit(1);
        } 
        else if (nextChar == ')') {
            ungetc(nextChar, stdin);
            break;
        }
        else if (nextChar == '.' && isDouble) {
            printf("Syntax error: cannot tokenize with character %c. Cannot have multiple decimal points.\n",nextChar);
            texit(1);
        }
        else if (nextChar == '.') {
            isDouble = true;
        } 
        else if (!isdigit(nextChar) && nextChar != '-' && nextChar != '+') {
            printf("Syntax error: cannot tokenize with character %c. Cannot have non-digit in number\n",nextChar);
            texit(1);
        }
        length++;
        myString[length - 1] = nextChar;
        nextChar = (char)fgetc(stdin);
    }
    length++;
    myString[length - 1] = '\0';
    if (isDouble) {
        myNumber -> type = DOUBLE_TYPE;
        myNumber -> d = strtod(myString, NULL);
    } 
    else {
        myNumber -> type = INT_TYPE;
        myNumber -> i = strtol(myString, NULL, 10);
    }
    return cons(myNumber,tokensList);
}

//Helper function that adds a symbol to the front of tokensList
Value *addSymbol (Value *tokensList, char nextChar) {
    Value *carNode = makeNull();
    carNode -> type = SYMBOL_TYPE;
    char symbols[] = "!$&^*_/:<>=?~%%+-.";
    int length = 0;
    char string[301];

    //Loop until we reach end of symbol
    while (nextChar != ' ' && nextChar != '\n') {
        if (nextChar == EOF) {
            printf("Syntax Error: Invalid Symbol Input\n");
            texit(1);
        }
        else if (nextChar == ')') {
            ungetc(nextChar, stdin);
            break;
        }
        else if (isalpha(nextChar) || strchr(symbols, nextChar) != NULL || isdigit((int)nextChar)) {
            length++;
            string[length - 1] = nextChar;
            nextChar = (char)fgetc(stdin);
        }
        else {
            printf("%c", nextChar);
            printf("Syntax Error: Invalid Symbol Input\n");
            texit(1);
        }
    }
    length++;
    string[length - 1] = '\0';
    char *real_string = talloc(length * sizeof(char));
    strcpy(real_string, string);
    carNode -> s = real_string;
    return cons(carNode, tokensList);
}

// Read source code that is input via stdin, and return a linked list consisting of the
// tokens in the source code. Each token is represented as a Value struct instance, where
// the Value's type is set to represent the token type, while the Value's actual value
// matches the type of value, if applicable. For instance, an integer token should have
// a Value struct of type INT_TYPE, with an integer value stored in struct variable i.
// See the assignment instructions for more details. 
Value *tokenize() {

    // Prepare list of tokens
    Value *tokensList = makeNull();

    // Prepare the character stream
    char nextChar;
    nextChar = (char)fgetc(stdin);
    char secondChar;

    char symbols[] = "!$&^*_/:<>=?~%%";

    // Start tokenizing!
    while (nextChar != EOF) {

        //Adds a parentheses to tokensList
        if (nextChar == '(' || nextChar == ')') {
            tokensList = addParentheses(tokensList, nextChar);
        }

        //Adds an int or double to tokensList 
        else if (isdigit((nextChar)) || nextChar == '.' || nextChar == '-' || nextChar == '+') {
            secondChar = (char)fgetc(stdin);
            if (isdigit((secondChar)) && (nextChar == '-' || nextChar == '+')) {
                ungetc(secondChar, stdin);
                tokensList = makeNumber(tokensList,nextChar);
            }

            //Undoes getc and adds + or - as a symbol
            else if (nextChar == '-' || nextChar == '+') {
                ungetc(secondChar, stdin);
                tokensList = addSymbol(tokensList, nextChar);
            }

            //Undoes getc and adds appropriate symbol (e.g. 9function would trigger this)
            else if (!isdigit((secondChar)) && secondChar != '.' && secondChar != ')' && secondChar != ' ' && secondChar != '\n') {
                ungetc(secondChar, stdin);
                tokensList = addSymbol(tokensList, nextChar);
            }

            //Adds an int or double to tokensList
            else {
                ungetc(secondChar, stdin);
                tokensList = makeNumber(tokensList,nextChar);
            }
        }

        //Adds a string to tokensList
        else if (nextChar == '"'){
            tokensList = addString(tokensList, nextChar);
        }

        //Adds a boolean to tokensList
        else if (nextChar == '#') {
            tokensList = boolean(tokensList, nextChar);
        }

        //Passes over a comment
        else if (nextChar == ';') {
            while (nextChar != EOF && nextChar != '\n') {
                nextChar = (char)fgetc(stdin);
            }
        }

        //Adds a symbol to tokensList
        else if (isalpha(nextChar) || strchr(symbols, nextChar) != NULL) {
            tokensList = addSymbol(tokensList, nextChar);
        }

        //Skipsthe current character
        else if (nextChar == ' ' || nextChar == '\n') {
        }
        else {
            printf("Syntax Error: Couldn't read input\n");
            texit(1);
        }
        // Read next character
        nextChar = (char)fgetc(stdin);
    }

    // Reverse the tokens list, to put it back in order
    Value *reversedList = reverse(tokensList);
    return reversedList;
}

// Display the contents of the list of tokens, along with associated type information.
// The tokens are displayed one on each line, in the format specified in the instructions.
void displayTokens(Value *list) {
    Value *curCar;

    //Loops until we reach the last node
    while (list -> type == CONS_TYPE) {
        curCar = car(list);

        //Determines appropriate output
        switch (curCar -> type) {
            case INT_TYPE:
                printf("%i:integer\n", curCar -> i);
                break;
            case DOUBLE_TYPE:
                printf("%f:double\n", curCar -> d);
                break;
            case STR_TYPE:
                printf("%s:string\n", curCar -> s);
                break;
            case SYMBOL_TYPE:
                printf("%s:symbol\n", curCar -> s);
                break;
            case BOOL_TYPE:
                if (curCar -> i) {
                    printf("#t:boolean\n");
                }
                else {
                    printf("#f:boolean\n");
                }
                break;
            case OPEN_TYPE:
                printf("(:open\n");
                break;
            case CLOSE_TYPE:
                printf("):close\n");
                break;
            case CONS_TYPE:
                printf("NESTED LOOP ERROR IN CAR\n");
                break;
            case NULL_TYPE:
                printf("NULL ERROR IN CAR\n");
                break;
            case PTR_TYPE:
                printf("POINTER TYPE ERROR IN CAR\n");
                break;
            case VOID_TYPE:
                printf("VOID TYPE IN CAR\n");
                break;
            case CLOSURE_TYPE: 
                printf("CLOSURE TYPE IN CAR\n");
                break;
            case PRIMITIVE_TYPE:
                printf("PRIMITIVE TYPE IN CAR\n");
                break;
            case UNSPECIFIED_TYPE:
                printf("UNSPECIFIED TYPE IN CAR\n");
                break;
        } 
        list = cdr(list);
    }
}
#endif
