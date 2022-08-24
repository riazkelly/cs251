#ifndef _LOOK_UP_SYMBOL
#define _LOOK_UP_SYMBOL

#include "value.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "look_up_symbol.h"
#include "talloc.h"
#include "linkedlist.h"
#include "errors.h"

//looks up a symbol to see if it is defined in the current frame or any previous frames
Value *lookUpSymbol (Value *value, Frame *frame){
    char *target = value -> s;
    Value *bindings = frame -> bindings;
    //Loops through the current frame to check for the target symbol
    while (!isNull(bindings)) {
        if (!strcmp(car(car(bindings)) -> s, target)) {
            Value *value = cdr(car(bindings));
            if (value -> type == UNSPECIFIED_TYPE) {
                evaluateError("Trying to evaluate an Unspecified type");
            }
            return value;
        }
        bindings = cdr(bindings);
    }

    //Goes to parent frame to check for the target symbol
    if (frame -> parent != NULL) {
        return lookUpSymbol(value, frame -> parent);
    } 

    //Error occurs if the target symbol is not contained in the frame or its parents
    //printf("%s",target);
    evaluateError("Variable has not been bound");

    return NULL;
}

#endif