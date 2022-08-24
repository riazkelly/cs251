#ifndef _EVAL_EACH
#define _EVAL_EACH

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

//evaluates each expression in a list of S-Expressions
Value *evalEach(Value *tree, Frame *frame) {
    Value *evaluatedExpressions = makeNull();
    Value *current;
    while (!isNull(tree)) {
        current = eval(car(tree),frame);
        evaluatedExpressions = cons(current,evaluatedExpressions);
        tree = cdr(tree);
    }
    return reverse(evaluatedExpressions);
}

#endif