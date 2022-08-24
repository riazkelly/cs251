#ifndef _EVAL_MULT
#define _EVAL_MULT
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
#include "eval_mult.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalMult(Value *args) {
    if (length(args) < 2) {
        evaluateError("Invalid number of args in mult");
    }
    Value *curArg;
    double product = 1;
    bool isDouble = false;
    
    while (!isNull(args)) {
        curArg = car(args);
        if (curArg -> type == INT_TYPE) {
            product *= curArg -> i;
        } else if (curArg -> type == DOUBLE_TYPE) {
            product *= curArg -> d;
            isDouble = true;
        } else {
            evaluateError("Invalid node type in divide");
        }
        args = cdr(args);
    }
    if (isDouble) {
        return makeDouble(product);
    }
    return makeInt((int)product);
    
}

#endif