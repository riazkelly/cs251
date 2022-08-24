#ifndef _EVAL_LETREC
#define _EVAL_LETREC

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "eval_let.h"
#include "eval_letrec.h"
#include "errors.h"
#include "interpreter.h"
#include "parser.h"


//evaluates scheme let statements
Value *evalLetRec(Value *tree, Frame* frame) {
    //Sets bindings
    Frame *currentFrame = talloc(sizeof(Frame));
    currentFrame -> parent = frame;
    Value *bindings = makeNull(); 
    currentFrame -> bindings = bindings;//In case there is a nested let call, we need to set this frame's bindings to null right away
    Value *nodes = car(tree);
    Value *valueList = makeNull();
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
        
        //we dont want to evaluate right away so save these for later
        valueList = cons(car(cdr(current)),valueList);

        Value *binding = cons(symbol, makeUnspecified());
        bindings = cons(binding, bindings);

        if (!isNull(cdr(cdr(current)))) {
            evaluateError("Too many arguments in let");
        }
        nodes = cdr(nodes);
    }

    currentFrame -> bindings = bindings;
    Value *ogBindings = bindings;

    //Evaluate let expression
    if (isNull(cdr(tree))) {
        evaluateError("No let body");
    } else {
        tree = cdr(tree);
    }
    Value *curBinding;
    Value *tempBindings = makeNull();
    while (!isNull(ogBindings)) {
        curBinding = car(ogBindings);
        tempBindings = cons(eval(car(valueList),currentFrame),tempBindings);
        valueList = cdr(valueList);
        ogBindings = cdr(ogBindings);
    }
    tempBindings = reverse(tempBindings);
    while (!isNull(tempBindings)) {
        curBinding = car(bindings);
        curBinding -> c.cdr = car(tempBindings);
        tempBindings = cdr(tempBindings);
        bindings = cdr(bindings);
    }
   
    Value* expression;
    while (!isNull(tree)) {
        expression = eval(car(tree),currentFrame);
        tree = cdr(tree);
    }
    return expression;
}
#endif