#ifndef _EVAL_LETSTAR
#define _EVAL_LETSTAR

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_let.h"
#include "eval_letStar.h"
#include "errors.h"
#include "interpreter.h"
#include "parser.h"


//evaluates scheme letstar statements
Value *evalLetStar(Value *tree, Frame* frame) {
    //Sets bindings
    Frame *currentFrame = talloc(sizeof(Frame));
    currentFrame -> parent = frame;
    Value *bindings = makeNull();
    currentFrame -> bindings = bindings; //In case there is a nested let call, we need to set this frame's bindings to null right away
    Value *nodes = car(tree);
    while (!isNull(nodes)) {
        if (nodes -> type != CONS_TYPE) {
            evaluateError("Node not cons type");
        }

        Value *current = car(nodes);
        if (current -> type != CONS_TYPE) {
            evaluateError("Node not cons type");
        }
        Value *symbol = car(current);
    
        if (cdr(current)-> type != CONS_TYPE) {
            evaluateError("Node not cons type");
        }
        if (car(current) -> type != SYMBOL_TYPE){
            evaluateError("Node not symbol type");
        }
        
        Value *value = car(cdr(current));

        value = eval(value, currentFrame);
        if (value -> type == CLOSURE_TYPE) {
            //to test if applying the lambda function in this frame would throw an error, which it should for some
            //but usually has a delayed evaluation
            Value *test = eval(value,currentFrame);
        }
        Value *binding = cons(symbol, value);
        bindings = cons(binding, bindings);
        currentFrame -> bindings = bindings;
        
        if (!isNull(cdr(cdr(current)))) {
            evaluateError("Too many arguments in let");
        }
        nodes = cdr(nodes);
    }
    
    //Evaluate let expression
    if (isNull(cdr(tree))) {
        evaluateError("No let body");
    } else {
        tree = cdr(tree);
    }

    Value* expression;
    while (!isNull(tree)) {
        expression = eval(car(tree),currentFrame);
        tree = cdr(tree);
    }
    return expression;
}
#endif