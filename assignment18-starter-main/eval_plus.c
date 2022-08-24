#ifndef _EVAL_PLUS
#define _EVAL_PLUS

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
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"


Value *evalPlus(Value *args) {
    Value *curArg;
    double curNum = 0;
    double sum = 0;
    bool isDouble = false;
    while (!isNull(args)) {
        curArg = car(args);
        if (curArg -> type == DOUBLE_TYPE) {
            curNum = curArg -> d;
            isDouble = true;
        } else if (curArg -> type == INT_TYPE) {
            curNum = (double)curArg -> i;
        } else {
            evaluateError("Invalid argument type in +");
        }
        sum += curNum;
        args = cdr(args);
    }
    
    if (!isDouble) {
        return makeInt((int)sum);
    }

    return makeDouble(sum);
}

#endif