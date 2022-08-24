#ifndef _EVAL_EQUALS
#define _EVAL_EQUALS
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
#include "eval_equals.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalEquals(Value *args) {
    if (length(args) != 2) {
        evaluateError("Invalid number of args in equals");
    }
    int num1 = car(args) -> i;
    int num2 = car(cdr(args)) -> i;
    return makeBool(num1==num2);
}

#endif