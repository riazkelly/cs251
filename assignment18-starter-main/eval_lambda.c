#ifndef _EVAL_LAMBDA
#define _EVAL_LAMBDA

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_lambda.h"
#include "errors.h"
#include "interpreter.h"
#include "eval_let.h"
#include "eval_null.h"
#include "parser.h" 

//evaluates the lambda function from scheme: creates a function with given parameters and body
Value *evalLambda(Value *args, Frame *frame) {
    if (length(args) != 2) {
        evaluateError("Invalid number of arguments in lambda");     
    }
    Value *parameters = car(args);
    Value *curParam;
    while (!isNull(parameters) ) {
        curParam = car(parameters);
        if (curParam -> type != SYMBOL_TYPE) {
            evaluateError("Node not symbol type");
        } else if (isNull(cdr(parameters))) {
            break;
        } else if (contains(cdr(parameters),curParam)) {
            evaluateError("Tried to bind a symbol more than once");
        }
        parameters = cdr(parameters);
    }
    
    return makeClosure(car(args),car(cdr(args)),frame);
}

//runs the given function with the given parameters
Value *apply(Value *function, Value *args) {
    if (function -> type != CLOSURE_TYPE) {
        printType(function);
        evaluateError("Node not closure type");
    }
    Frame *currentFrame = talloc(sizeof(Frame));
    currentFrame -> parent = function ->cl.frame;
    Value *parameters = function ->cl.paramNames;
    Value *bindings = makeNull();

    if (length(parameters) != length(args)) {
        //printf("ParamLen: %i ArgLen: %i",length(parameters),length(args));
        evaluateError("Invalid number of arguments in apply");
    }
    
    Value *value;
    Value *symbol;
    while (!isNull(parameters)) {
        symbol = car(parameters);
        value = car(args);
        
        Value *binding = cons(symbol, value);
        bindings = cons(binding, bindings);
        args = cdr(args);
        parameters = cdr(parameters);
    }
    currentFrame -> bindings = bindings;
    Value *body = function -> cl.functionCode;

    return eval(body, currentFrame);
}

#endif