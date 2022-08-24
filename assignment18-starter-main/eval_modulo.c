#ifndef _EVAL_MODULO
#define _EVAL_MODULO
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
#include "eval_modulo.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalModulo(Value *args) {
    if (length(args) != 2) {
        evaluateError("Invalid number of args in modulo");
    }
    int firstArg = car(args) -> i;
    int secondArg = car(cdr(args)) -> i;

    return (makeInt(firstArg%secondArg));
}

#endif