#ifndef _EVAL_DIVIDE
#define _EVAL_DIVIDE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_if.h"
#include "eval_let.h"
#include "eval_lambda.h"
#include "eval_define.h"
#include "eval_each.h"
#include "eval_and.h"
#include "eval_divide.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalDivide(Value *args) {
    if (length(args) != 2) {
        evaluateError("Invalid number of arguments in divide, should be 2");
    }
    Value *firstArg = car(args);
    Value *secondArg = car(cdr(args));
    double numerator;
    double denominator;

    if (firstArg -> type == INT_TYPE) {
        numerator = (double)firstArg -> i;
    } else if (firstArg -> type == DOUBLE_TYPE) {
        numerator = firstArg -> d;
    } else {
        evaluateError("Invalid node type in divide");
    }
    if (secondArg -> type == INT_TYPE) {
        denominator = (double)secondArg -> i;
    } else if (secondArg -> type == DOUBLE_TYPE) {
        denominator = secondArg -> d;
    } else {
        evaluateError("Invalid node type in divide");
    }
    double quotient = numerator/denominator;
    bool test = quotient-(int)quotient == 0;
    if (test) {
        return makeInt((int)quotient);
    }
    return makeDouble(quotient);
}

#endif