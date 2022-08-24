#ifndef _EVAL_SET
#define _EVAL_SET
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
#include "eval_set.h"
#include "errors.h"
#include "interpreter.h"
#include "look_up_symbol.h"
#include "parser.h"

Value *evalSet(Value *args, Frame *frame) {
    if (length(args) != 2) {
        evaluateError("Invalid number of arguments in set");
    }
    Value *bindings;
    Value *symbol = car(args);
    Value *value = car(cdr(args));
    bool containsBinding = false;

    if (symbol -> type != SYMBOL_TYPE) {
        evaluateError("Invalid node type in set");
    } 
    value = eval(value, frame);
    do {
        bindings = frame -> bindings;
        while (!isNull(bindings)) {
            Value *binding = car(bindings);
            if (!strcmp(symbol -> s, car(binding) -> s)) {
                binding ->c.cdr = value;
                containsBinding = true;
                break;
            }
            bindings = cdr(bindings);
        }
        if (frame ->parent) {
            frame = frame ->parent;
        } else {
            break;
        }
    } while (frame ->parent != NULL);

    if (!containsBinding) {
        evaluateError("Set variable has not yet been defined");
    }

    return makeVoid();
}

#endif