#ifndef _EVAL_LET
#define _EVAL_LET

bool containsBinding (Value *bindings, Value *binding);

Value *evalLet(Value *tree, Frame *frame);

#endif
