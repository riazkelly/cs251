#ifndef _EVAL_BEGIN
#define _EVAL_BEGIN
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
#include "eval_begin.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalBegin(Value *args, Frame *frame) {
    Value *curEvaluation;
    while (!isNull(args)) {
        curEvaluation = eval(car(args),frame);
        args = cdr(args);
        if (isNull(args)) {
            return curEvaluation;
        }
    }
    return makeVoid();
}

#endif