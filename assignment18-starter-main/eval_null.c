#ifndef _EVAL_NULL
#define _EVAL_NULL

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

Value *evalNull(Value *args) {
    Value *boolean = makeNull();
    boolean -> type = BOOL_TYPE;
    boolean -> i = 0;

    if (length(args) != 1) {
        //printf("%i",length(args));
        evaluateError("Invalid number of arguments in null");
    }

    Value *curList = car(args);
    if (isNull(curList) && curList -> type != CONS_TYPE) {
        boolean -> i = 1;
    }
    
    return boolean;
}

#endif