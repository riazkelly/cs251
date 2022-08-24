#ifndef _EVAL_LAMBDA
#define _EVAL_LAMBDA

Value *evalLambda(Value *args, Frame *frame);

Value *apply(Value *function, Value *args);

#endif