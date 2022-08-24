#ifndef _EVAL_OR
#define _EVAL_OR
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
#include "eval_or.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalOr(Value *args, Frame *frame) {
    Value *curArg;

    while (!isNull(args)) {
        curArg = eval(car(args),frame);
        if (booleanValue(curArg)) {
            return makeBool(true);
        }
        args = cdr(args);
    }
    return makeBool(false);
}

#endif