#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef _PARSER
#define _PARSER

Value *reset (Value *tree) {
    while(tree -> type != NULL_TYPE) {
        tree = cdr(tree);
    }
    return tree;
}

// Return a pointer to a parse tree representing the structure of a Scheme 
// program, given a list of tokens in the program.
Value *parse(Value *tokens) {
    Value *current = tokens;
    Value *stack = makeNull();
    Value *tree = makeNull();
    while (current -> type != NULL_TYPE) { //Loops through all tokens
        if (current -> c.car -> type == CLOSE_TYPE) { //We find a closed parentheses
            while (stack -> type != NULL_TYPE) {
                if (stack -> c.car -> type != OPEN_TYPE) { //Traversing the stack until we find an open parentheses
                    tree = cons(stack -> c.car, tree);
                    stack = cdr(stack);
                }
                else {
                    stack = cdr(stack);
                    stack = cons(tree, stack);
                    tree = reset(tree);
                    break;
                }
            }
            if (stack -> type == NULL_TYPE){ //If we reach the end of the stack without finding a open parentheses to match
                printf("Syntax error: not enough open parens\n");
                texit(1);
            }
        }
        else {
            stack = cons(current -> c.car, stack);
        }
        current = cdr(current);
    }
    tree = reverse(stack);
    if (tree -> c.car -> type == OPEN_TYPE){ //If there was still an open parentheses on the stack when we set the tree equal to it
        printf("Syntax error: too few clos parens\n");
        texit(1);
    }
    return tree;
}

// Print a parse tree to the screen in a readable fashion. It should look 
// just like Scheme code (use parentheses to mark subTrees).
void printTree(Value *tree) {
    Value *node = makeNull();
    if (tree -> type != CONS_TYPE) {
        printValue(tree);
    } else {
        printf("(");
        while (tree -> type == CONS_TYPE) {
            
            node = tree -> c.car;
            if (node -> type == CONS_TYPE) {
                //printf("(");
                printTree(node); //Calls recursively because the tree is nested and we know we need to print parentheses
                //printf(")");
            } else {
                printValue(node);
            }
            if (cdr(tree) -> type != CONS_TYPE && cdr(tree) -> type != NULL_TYPE) {
                printf(" . ");
                printValue(cdr(tree));
            } else if (cdr(tree) -> type != NULL_TYPE) {
                printf(" ");
            }
            tree = cdr(tree);
        }
        printf(")");
    }
    printf("\n");
}

#endif
