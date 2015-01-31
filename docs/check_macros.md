### NAME

    `check`, `check_mem`, `check_debug` - macros to assert C statements

### SYNOPSIS

    #include <stdio.h>
    #include <errno.h>
    #include <string.h>

    check(A, M, ...)
    check_mem(A)
    check_debug(A, M, ...)

### DESCRIPTION
The `check()`, `check_mem()` and `check_debug()` macros are used to assert statment `A`. Upon failure to assert statment `A`, message `M` will be **logged as an error** (or debug message for `check_debug()`), and will use the `goto` statement to goto the `error` label (see examples section to see how it is used).

### ARGUMENTS

- **A** (`C statement`): C statement which you would like to assert
- **M** (`char *`): message to be outputted if assert `A` fails

### RETURNS
None

### EXAMPLES

    #include <stdio.h>
    #include <errno.h>
    #include <string.h>

    int main()
    {
        int some_variable = 1;
        char *malloced_var = malloc(sizeof(char) * 10);

        check(some_variable == 1, "some_variable should be 1");
        check_mem(malloced_var);  /* if fail display "Out of memory" */

        some_variable = 2;
        check_debug(some_variable == 2, "some_variable should have been 2");

        /* all checks passed */
        return 0;
    error:
        /* one or more checks failed */
        return -1;
    }
