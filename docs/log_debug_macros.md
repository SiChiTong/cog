### NAME

    `debug`, `log_err`, `log_warn`, `log_info` - debug and logging macros

### SYNOPSIS

    #include <stdio.h>
    #include <errno.h>
    #include <string.h>

    debug(M, ...)
    log_err(M, ...)
    log_warn(M, ...)
    log_info(M, ...)

### DESCRIPTION
The `debug()`, `log_err()`, `log_warn()` and `log_info()` macros are used to print useful debugging information to `sterr`. They include the source file which the function is called as well as the message you defined in `M`.


### ARGUMENTS

- **M** (`char *`): debug message which you wish to display

**Note**: You don't have to add a newline char '\n' at the end of message `M`.

### RETURNS
None

### EXAMPLES

    debug("Useful debug message, such as - We are at stage 1!");
    log_err("Error occured here!");
    log_warn("Warning something isn't quite right here!");
    log_info("Log some information");
