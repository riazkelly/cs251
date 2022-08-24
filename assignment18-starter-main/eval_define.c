#ifndef _EVAL_DEFINE
#define _EVAL_DEFINE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_define.h"
#include "errors.h"
#include "interpreter.h"
#include "parser.h"
#include "eval_lambda.h"

//evaluates the define function from scheme: defines a given symbol as the given body
Value *evalDefine(Value *args, Frame *frame) {
    if (length(args) != 2) {
        evaluateError("Invalid number of arguments in define");
    }
    Value *bindings = frame -> bindings;
    Value *symbol = car(args);
    Value *value = car(cdr(args));
    if (symbol -> type == CONS_TYPE) { //the third version of define OPTIONAL
        Value *lambdaArgs = cons(cdr(symbol),cdr(args));
        value = evalLambda(lambdaArgs,frame);
        symbol = car(symbol);
    } else if (symbol -> type == SYMBOL_TYPE) {
        value = eval(value, frame);
    } else {
        evaluateError("Invalid node type in Define");
    }
    
    Value *binding = cons(symbol,value);
    bindings = cons(binding,bindings);
    frame -> bindings = bindings;
    return makeVoid();
}

#endif