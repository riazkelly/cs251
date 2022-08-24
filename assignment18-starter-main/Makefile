# Change "no" to "yes" to use our binaries
USE_BINARIES = no

ifeq ($(USE_BINARIES),yes)
  SRCS = lib/linkedlist.o lib/talloc.o lib/tokenizer.o lib/parser.o \
				 main.c interpreter.c
  HDRS = lib/parser.h lib/linkedlist.h lib/talloc.h lib/tokenizer.h \
	       lib/value.h interpreter.h
else
  SRCS = linkedlist.c talloc.c main.c tokenizer.c parser.c interpreter.c eval_if.c eval_let.c look_up_symbol.c errors.c eval_define.c eval_lambda.c eval_each.c eval_null.c eval_plus.c eval_quote.c eval_car.c eval_cdr.c eval_cons.c eval_and.c eval_begin.c eval_cond.c eval_divide.c eval_equals.c eval_greaterthan.c eval_lessthan.c eval_letrec.c eval_letStar.c eval_modulo.c eval_mult.c eval_or.c eval_set.c eval_subtract.c
  HDRS = tokenizer.h linkedlist.h talloc.h parser.h value.h interpreter.h eval_if.h eval_let.h look_up_symbol.h errors.h eval_define.h eval_lambda.h eval_each.h eval_null.h eval_plus.h eval_quote.h eval_car.h eval_cdr.h eval_cons.h eval_and.h eval_begin.h eval_cond.h eval_divide.h eval_equals.h eval_greaterthan.h eval_lessthan.h eval_letrec.h eval_letStar.h eval_modulo.h eval_mult.h eval_or.h eval_set.h eval_subtract.h
endif

CC = clang
CFLAGS = -g

OBJS = $(SRCS:.c=.o)

.PHONY: interpreter
interpreter: $(OBJS)
	$(CC)  $(CFLAGS) $^  -o $@
	rm -f *.o
	rm -f vgcore.*

.PHONY: phony_target
phony_target:

%.o : %.c $(HDRS) phony_target
	$(CC)  $(CFLAGS) -c $<  -o $@

clean:
	rm -f *.o
	rm -f interpreter

