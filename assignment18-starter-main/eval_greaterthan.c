#ifndef _EVAL_GREATERTHAN
#define _EVAL_GREATERTHAN
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
#include "eval_greaterthan.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalGreaterThan(Value *args) {
    if (length(args) != 2) {
        evaluateError("Invalid number of args in greaterthan");
    }
    Value *firstArg = car(args);
    Value *secondArg = car(cdr(args));
    double first;
    double second;


    if (firstArg -> type == INT_TYPE) {
        first = (double)firstArg -> i;
    } else if (firstArg -> type == DOUBLE_TYPE) {
        first = firstArg -> d;
    } else {
        evaluateError("Invalid node type in divide");
    }
    if (secondArg -> type == INT_TYPE) {
        second = (double)secondArg -> i;
    } else if (firstArg -> type == DOUBLE_TYPE) {
        second = secondArg -> d;
    } else {
        evaluateError("Invalid node type in divide");
    }
    return makeBool(first > second);
}

#endif