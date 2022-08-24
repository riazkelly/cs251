#ifndef _EVAL_CONS
#define _EVAL_CONS
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
#include "eval_car.h"
#include "eval_cdr.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalCons(Value *args) {
    if (length(args) != 2) {
        evaluateError("Invalid number of arguments in cons");
    }
    Value *myCar = car(args);
    Value *myCdr;
    myCdr = car(cdr(args));
    return cons(myCar, myCdr);
}

#endif