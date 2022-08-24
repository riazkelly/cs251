#ifndef _EVAL_LET
#define _EVAL_LET

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_let.h"
#include "errors.h"
#include "interpreter.h"
#include "parser.h"

//checks if the given set of bindings already contains the given binding (so we dont double dip)
bool containsBinding (Value *bindings, Value *binding) {
    while (!isNull(bindings)) {
        if (!strcmp(binding -> s, car(car(bindings)) -> s)) {
            return true;
        }
        bindings = cdr(bindings);
    }
    return false;
}

//evaluates scheme let statements
Value *evalLet(Value *tree, Frame* frame) {
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

        if (containsBinding(bindings, symbol)) {
            evaluateError("Tried to bind a symbol more than once");
        }
        
        Value *value = eval(car(cdr(current)), frame);
        Value *binding = cons(symbol, value);
        bindings = cons(binding, bindings);

        if (!isNull(cdr(cdr(current)))) {
            evaluateError("Too many arguments in let");
        }
        nodes = cdr(nodes);
    }
    currentFrame -> bindings = bindings;

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