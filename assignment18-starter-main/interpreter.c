#ifndef _INTERPRETER
#define _INTERPRETER

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
#include "eval_car.h"
#include "eval_cdr.h"
#include "eval_cons.h"
#include "eval_null.h"
#include "eval_quote.h"
#include "eval_plus.h"
#include "eval_and.h"
#include "eval_or.h"
#include "eval_letrec.h"
#include "eval_letStar.h"
#include "eval_set.h"
#include "eval_begin.h"
#include "eval_cond.h"
#include "eval_divide.h"
#include "eval_modulo.h"
#include "eval_mult.h"
#include "eval_greaterthan.h"
#include "eval_lessthan.h"
#include "eval_subtract.h"
#include "eval_equals.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"


//evaluates a given S-Expression
Value *eval(Value *tree, Frame *frame) {
   switch (tree->type)  {
     case INT_TYPE: {
        return tree;
        break;
     }
     case DOUBLE_TYPE: {
        return tree;
        break;
     } 
     case BOOL_TYPE: {
        return tree;
        break;
     } 
     case STR_TYPE: {
        return tree;
        break;
     }
     case NULL_TYPE: {
        return tree;
     }
     case SYMBOL_TYPE: {
        return lookUpSymbol(tree, frame);
        break;
     } 
     case OPEN_TYPE: {
        evaluateError("Open Type in eval()");
     }
     case CLOSE_TYPE: {
        evaluateError("Close Type in eval()");
     }
     case PTR_TYPE: {
        evaluateError("PTR Type in eval()");
     }
     case VOID_TYPE: {
         evaluateError("Void Type in eval()");
     }
     case CLOSURE_TYPE: {
         evaluateError("Closure Type in eval()");
     }
     case PRIMITIVE_TYPE: {
        evaluateError("Primitive Type in eval()"); 
        break;
     }
     case UNSPECIFIED_TYPE: {
         evaluateError("Unspecified Type in eval()"); 
        break;
     }
     case CONS_TYPE: {
        Value *first = car(tree);
        Value *args = cdr(tree);
        
        if (first -> type == SYMBOL_TYPE) {
            //the calls for our scheme functions that require frame inputs
            if (!strcmp(first->s, "if")) {
                return evalIf(args, frame);
            }
            else if (!strcmp(first->s, "let")) {
                return evalLet(args, frame);
            }
            else if (!strcmp(first->s, "define")) {
                return evalDefine(args,frame);
            }
            else if (!strcmp(first->s, "quote")) {
                return evalQuote(args);
            }
            else if (!strcmp(first->s, "lambda")) {
                return evalLambda(args,frame);
            }
            else if (!strcmp(first->s, "and")) {
                return evalAnd(args,frame);
            }
            else if (!strcmp(first->s, "or")) {
                return evalOr(args,frame);
            }
            else if (!strcmp(first->s, "cond")) {
                return evalCond(args,frame);
            }
            else if (!strcmp(first->s, "set!")) {
                return evalSet(args,frame);
            }
            else if (!strcmp(first->s, "begin")) {
                return evalBegin(args,frame);
            }
            else if (!strcmp(first->s, "letrec")) {
                return evalLetRec(args,frame);
            }
            else if (!strcmp(first->s, "let*")) {
                return evalLetStar(args,frame);
            }
            else {
                // If it's not a special form, evaluate 'first', evaluate the args, then
                // apply 'first' on the args.
                Value *evaluatedOperator = eval(first, frame);
                Value *evaluatedArgs = evalEach(args, frame);
                if (evaluatedOperator -> type == PRIMITIVE_TYPE) {
                    return (*evaluatedOperator -> pf)(evaluatedArgs);
                }
                return apply(evaluatedOperator, evaluatedArgs);
            }
        } else if (first -> type == CONS_TYPE) {
            // If it's not a special form, evaluate 'first', evaluate the args, then
            // apply 'first' on the args.
            Value *evaluatedOperator = eval(first, frame);
            Value *evaluatedArgs = evalEach(args, frame);
            if (evaluatedOperator -> type == PRIMITIVE_TYPE) {
                return (*evaluatedOperator -> pf)(evaluatedArgs);
            }
            return apply(evaluatedOperator, evaluatedArgs);
        } else {
            evaluateError("Error with first in eval");
        }
        break;
     }
    }
    return NULL;    
}

void bindPrimitiveFunction(char *name, Value *(*function)(struct Value *), Frame *frame) {
    // Bind 'name' to 'function' in 'frame'
    Value *bindings = frame -> bindings;
    Value *value = makePrimitive(function);
    Value *symbol = makeString(name);
    Value *binding = cons(symbol,value);
    bindings = cons(binding, bindings);
    frame->bindings = bindings;
}

//interprets a parse tree
void interpret(Value *tree) {
    Frame *globalFrame = talloc(sizeof(Frame));
    globalFrame -> parent = NULL;
    Value *bindings = makeNull();
    globalFrame -> bindings = bindings;

    // Create bindings in the global frame for all of
    // the built-in functions.
    bindPrimitiveFunction("+", &evalPlus, globalFrame);
    bindPrimitiveFunction("null?", &evalNull, globalFrame);
    bindPrimitiveFunction("car", &evalCar, globalFrame);
    bindPrimitiveFunction("cdr", &evalCdr, globalFrame);
    bindPrimitiveFunction("cons", &evalCons, globalFrame);
    bindPrimitiveFunction("-", &evalSubtract, globalFrame);
    bindPrimitiveFunction("*", &evalMult, globalFrame);
    bindPrimitiveFunction("/", &evalDivide, globalFrame);
    bindPrimitiveFunction("modulo", &evalModulo, globalFrame);
    bindPrimitiveFunction("<", &evalLessThan, globalFrame);
    bindPrimitiveFunction(">", &evalGreaterThan, globalFrame);
    bindPrimitiveFunction("=", &evalEquals, globalFrame);

    Value *output = makeNull();
    while (!isNull(tree)) {
        output = eval(car(tree), globalFrame);
        printValue(output);
        tree = cdr(tree);
    }
}


#endif

