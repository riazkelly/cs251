#ifndef _EVAL_CDR
#define _EVAL_CDR
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
#include "eval_quote.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalCdr(Value *args) {
    if (length(args) != 1) {
        evaluateError("Invalid number of arguments in cdr");
    }
    Value *myList = car(args);

    if (myList -> type != CONS_TYPE) {
        evaluateError("Not CONS type node in CDR");
    }
    return cdr(myList);
}

#endif