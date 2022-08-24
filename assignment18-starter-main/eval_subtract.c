#ifndef _EVAL_SUBTRACT
#define _EVAL_SUBTRACT
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
#include "eval_subtract.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalSubtract(Value *args) {
    if (length(args) != 2) {
        evaluateError("Invalid number of arguments in subtract, should be 2");
    }
    Value *firstArg = car(args);
    Value *secondArg = car(cdr(args));
    bool isDouble = false;
    double minuend;
    double subtrahend;

    if (firstArg -> type == INT_TYPE) {
        minuend = (double)firstArg -> i;
    } else if (firstArg -> type == DOUBLE_TYPE) {
        minuend = firstArg -> d;
        isDouble = true;
    } else {
        evaluateError("Invalid node type in divide");
    }
    if (secondArg -> type == INT_TYPE) {
        subtrahend = (double)secondArg -> i;
    } else if (secondArg -> type == DOUBLE_TYPE) {
        subtrahend = secondArg -> d;
        isDouble = true;
    } else {
        evaluateError("Invalid node type in divide");
    }
    double difference = minuend - subtrahend;
    if (!isDouble) {
        return makeInt((int)difference);
    }
    return makeDouble(difference);
}

#endif