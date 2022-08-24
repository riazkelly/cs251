#ifndef _EVAL_COND
#define _EVAL_COND
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
#include "eval_cond.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalCond(Value *args, Frame *frame) {
    if (length(args) == 0) {
        evaluateError("No arguments given in cond");
    }
    Value *curArg;
    Value *curCond;
    Value *curAction;
    while (!isNull(args)) {
        curArg = car(args);
        curAction = car(cdr(curArg));
        if (car(curArg) -> type == SYMBOL_TYPE && !strcmp(car(curArg) -> s,"else")) {
            return eval(curAction,frame);
        } else {
            curCond = eval(car(curArg),frame);
        }
        if (booleanValue(curCond)) {
            return eval(curAction,frame);
        }
        args = cdr(args);
    }
    return makeVoid();
}

#endif