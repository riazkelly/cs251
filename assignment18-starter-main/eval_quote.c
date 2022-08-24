#ifndef _EVAL_QUOTE
#define _EVAL_QUOTE
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

Value *evalQuote(Value *args) {
    if (length(args) != 1) {
        evaluateError("Invalid number of arguments in quote");
    }

    return car(args);
}

#endif