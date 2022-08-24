#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "talloc.h"

//provides a simple way to print errors and texit
void evaluateError(char *errorMessage) {
    printf("%s: %s\n", "Evaluation error", errorMessage);
    texit(1);
}