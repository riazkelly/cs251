#ifndef _INTERPRETER
#define _INTERPRETER

Value *eval(Value *expr, Frame *frame);

void interpret(Value *tree);

#endif

