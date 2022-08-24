#include "linkedlist.h"
#include "value.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "talloc.h"
#include "parser.h"

// Create a new NULL_TYPE value node.
Value *makeNull(){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = NULL_TYPE;
    return newNode;
}

// Create a new INT_TYPE value node.
Value *makeInt(int i){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = INT_TYPE;
    newNode -> i = i;
    return newNode;
}

// Create a new DOUBLE_TYPE value node.
Value *makeDouble(double d){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = DOUBLE_TYPE;
    newNode -> d = d;
    return newNode;
}

// Create a new CLOSURE_TYPE value node.
Value *makeClosure(Value *paramNames, Value *functionCode, Frame *frame){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = CLOSURE_TYPE;
    newNode -> cl.paramNames = paramNames;
    newNode -> cl.functionCode = functionCode;
    newNode -> cl.frame = frame;
    return newNode;
}

// Create a new PRIMITIVE_TYPE value node.
Value *makePrimitive(Value *(*function)(struct Value *)){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = PRIMITIVE_TYPE;
    newNode -> pf = function;
    return newNode;
}

// Create a new STR_TYPE value node.
Value *makeString(char *string){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = STR_TYPE;
    newNode -> s = string;
    return newNode;
}

// Create a new VOID_TYPE value node.
Value *makeVoid() {
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = VOID_TYPE;
    return newNode;
}

// Create a pointer to a new BOOL_TYPE Value
Value *makeBool(bool i) {
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = BOOL_TYPE;
    newNode -> i = i;
    return newNode;
}
// Create a pointer to a new BOOL_TYPE Value
Value *makeUnspecified() {
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = UNSPECIFIED_TYPE;
    return newNode;
}

// Create a new CONS_TYPE value node.
Value *cons(Value *newCar, Value *newCdr){
    Value *newNode = talloc(sizeof(Value));
    newNode -> type = CONS_TYPE;
    newNode -> c.car = newCar;
    newNode -> c.cdr = newCdr;
    return newNode;
}

//helper method for display, prints value of node
void printValue(Value *val) {
    switch (val -> type) {
        case INT_TYPE:
            printf("%i\n", val -> i);
            break;
        case DOUBLE_TYPE:
            printf("%f\n", val -> d);
            break;
        case STR_TYPE:
            if (val -> s[0] == '\"') {
                printf("%s\n", val -> s);
            } else {
                printf("\"%s\"\n", val -> s);
            }
            break;
        case CONS_TYPE:
            printTree(val);
            break;
        case NULL_TYPE:
            printf("()\n");
            break;
        case PTR_TYPE:
            printf("ERROR: Pointer\n");
            break;
        case SYMBOL_TYPE:
            printf("%s\n", val -> s);
            break;
        case BOOL_TYPE:
            if (val -> i) {
            printf("#t\n");
        }
        else {
            printf("#f\n");
        }
            break;
        case OPEN_TYPE:
            printf("Open\n");
            break;
        case CLOSE_TYPE:
            printf("Close\n");
            break;
        case VOID_TYPE:
            break;
        case CLOSURE_TYPE:
            printf("#<procedure>\n");
            break;
        case PRIMITIVE_TYPE:
            printf("Primitive\n");
            break;
        case UNSPECIFIED_TYPE:
            printf("Unspecified\n");
            break;
    } 
}


// Prints the type of the value passed in
void printType(Value *val){
    switch (val -> type) {
        case INT_TYPE:
            printf("INT_TYPE\n");
            break;
        case DOUBLE_TYPE:
            printf("DOUBLE_TYPE\n");
            break;
        case STR_TYPE:
            printf("STR_TYPE\n");
            break;
        case CONS_TYPE:
            printf("CONS_TYPE\n");
            break;
        case NULL_TYPE:
            printf("NULL_TYPE\n");
            break;
        case PTR_TYPE:
            printf("PTR_TYPE\n");
            break;
        case SYMBOL_TYPE:
            printf("SYMBOL_TYPE\n");
            break;
        case BOOL_TYPE:
            printf("BOOL_TYPE\n");
            break;
        case OPEN_TYPE:
            printf("OPEN_TYPE\n");
            break;
        case CLOSE_TYPE:
            printf("CLOSE_TYPE\n");
            break;
        case VOID_TYPE:
            printf("VOID_TYPE\n");
            break;
        case CLOSURE_TYPE:
            printf("CLOSURE_TYPE\n");
            break;
        case PRIMITIVE_TYPE:
            printf("PRIMITIVE_TYPE\n");
            break;
        case UNSPECIFIED_TYPE:
            printf("UNSPECIFIED_TYPE\n");
            break;
    }
}

// Display the contents of the linked list to the screen in some kind of
// readable format
void display(Value *list){
    printf("( ");
    while (!isNull(list)) {
        printValue(car(list));
        printf(" ");
        list = cdr(list);
    }
    printf(")");
}


// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory whatsoever between the original list and the new one.
//
// FAQ: What if there are nested lists inside that list?
//
// ANS: There won't be for this assignment. There will be later, but that will
// be after we've got an easier way of managing memory.
Value *reverse(Value *list){
    Value *new_list = makeNull();
    while (!isNull(list)) {
        new_list = cons(car(list),new_list);
        list = cdr(list);
    }
    //cleanup(list);
    return new_list;
}

// Frees up all memory directly or indirectly referred to by list. This includes strings.
//
// FAQ: What if a string being pointed to is a string literal? That throws an
// error when freeing.
//
// ANS: Don't put a string literal into the list in the first place. All strings
// added to this list should be able to be freed by the cleanup function.
//
// FAQ: What if there are nested lists inside that list?
//
// ANS: There won't be for this assignment. There will be later, but that will
// be after we've got an easier way of managing memory.

// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
Value *car(Value *list){
    assert(list -> type == CONS_TYPE && "Input Invalid: Not CONS");
    return list -> c.car;
    
}

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
Value *cdr(Value *list){
    assert(list -> type == CONS_TYPE && "Input Invalid: Not CONS");
    return list -> c.cdr;
}

// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isNull(Value *value){
    return (value -> type == NULL_TYPE);
}

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(Value *value){
    int len = 0;
    while (!isNull(value)) {
        len++;
        value = cdr(value);
    }
    return len;
}

bool contains(Value *list, Value *value) {
    bool found = false;
        while (!isNull(list)) {
            switch (list -> type) {
                case INT_TYPE:
                    found = list -> i == value -> i;
                    break;
                case DOUBLE_TYPE:
                    found = list -> d == value -> d;
                    break;
                case STR_TYPE:
                    found = !strcmp(list -> s, value -> s);
                    break;
                case CONS_TYPE:
                    found = contains(car(list),value);
                    break;
                case NULL_TYPE:
                    printf("NULL_TYPE\n");
                    break;
                case PTR_TYPE:
                    printf("PTR_TYPE\n");
                    break;
                case SYMBOL_TYPE:
                    found = !strcmp(list -> s, value -> s);
                    break;
                case BOOL_TYPE:
                    printf("BOOL_TYPE\n");
                    break;
                case OPEN_TYPE:
                    printf("OPEN_TYPE\n");
                    break;
                case CLOSE_TYPE:
                    printf("CLOSE_TYPE\n");
                    break;
                case VOID_TYPE:
                    printf("VOID_TYPE\n");
                    break;
                case CLOSURE_TYPE:
                    printf("CLOSURE_TYPE\n");
                    break;
                case PRIMITIVE_TYPE:
                    printf("PRIMITIVE_TYPE\n");
                    break;
                case UNSPECIFIED_TYPE:
                    printf("UNSPECIFIED_TYPE\n");
                    break;
            }
            if (list -> type != CONS_TYPE) {
                break;
            } else {
                list = cdr(list);
            }
            if (found) {
                return found;
            }
        }
    return found;
}


