#ifndef _EVAL_IF
#define _EVAL_IF

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_if.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"

//takes in a value and returns whether or not it is true or false, even with numbers and strings
bool booleanValue(Value *value) {
    switch (value -> type) {
            case INT_TYPE:
                return value -> i;
                break;
            case DOUBLE_TYPE:
                return value -> d;
                break;
            case STR_TYPE:
                return value -> s;
                break;
            case SYMBOL_TYPE:
                evaluateError("Symbol type in booleanValue");
                break;
            case BOOL_TYPE:
                return value -> i;
                break;
            case OPEN_TYPE:
                evaluateError("Opentype in booleanValue");
                break;
            case CLOSE_TYPE:
                evaluateError("Close type in booleanValue");
                break;
            case CONS_TYPE:
                evaluateError("Cons type in booleanValue");
                break;
            case NULL_TYPE:
                return false;
                break;
            case PTR_TYPE:
                evaluateError("Ptr type in booleanValue");
                break;
            case VOID_TYPE:
                evaluateError("Void type in booleanValue");
                break;
            case CLOSURE_TYPE:
                evaluateError("Closure type in booleanValue");
                break;
            case PRIMITIVE_TYPE:
                evaluateError("Primitive type in booleanValue");
                break;
            case UNSPECIFIED_TYPE:
                evaluateError("Unspecified type in booleanValue");
                break;
        }
        return NULL;
}

//evaluates the if function from scheme
Value *evalIf(Value *args, Frame *frame) {
    if (length(args) != 3) {
        evaluateError("Invalid number of arguments in if");
    }
    Value *firstArg = car(args);
    Value *secondArg = car(cdr(args));
    Value *thirdArg = car(cdr(cdr(args)));

    if (booleanValue(eval(firstArg, frame))) {
        return eval(secondArg, frame);
    } else {
        return eval(thirdArg, frame);
    }
    
}
#endif