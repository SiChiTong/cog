# cog/utils.h

**Contents**:
- Debug / log
- Control flow
- Memory
- String
- Random
- Comparator
- File



## Debug / log

    void debug(M, ...);
    void log_err(M, ...);
    void log_warn(M, ...);
    void log_info(M, ...);

`debug()`, `log_err()`, `log_warn()` and `log_info()` provides functionatily to
log different levels of messages, from debug, error and warning to information
messages. The usage of these functions are similar to the usage of `printf`,
where `M` is the message, and `...` is where you may include the values the are
part of `M`, (e.g log_info("My lucky number is %i", 23)).

**Note**: The above functions all append a newline character `\n` at the end of
M.



## Control flow

    void check(A, M, ...);
    void check_mem(A);
    void check_debug(A, M, ...);
    void silent_check(A);

`check()`, `check_mem()`, `check_debug()` and `silent_check()` provide
functionality that helps with flow control, essentially they all encapsulate
if/else statments for convienice. Aside from encapsulating if/else in a
function they emulate the try/catch behaviour found in many modern object
oriented languages. If the condition in `A` fails, the message `M` will be
displayed, and a `goto` statement will be executed to `error` defined by the
user. Example:

    #include <stdio.h>
    #include "cog.h"

    int main()
    {
        int x = 1;

        check_debug(x != 0, "x is not 0, its %d", x);

        return 0;

    error:  /* must have this when you use any of the check functions */
        return -1;
    }




## Memory

    void *copy_value(int value_type, void *value);

`copy_value()` copies `value` with type `value_type`:

- `INTEGER`
- `FLOAT`
- `DOUBLE`
- `STRING`

And returns a pointer.


---

    int *malloc_int(int i);
    float *malloc_float(float f);
    double *malloc_double(double d);
    char *malloc_string(const char *s);

`malloc_int()`, `malloc_float()`, `malloc_double()` and `malloc_string()`
allocates addtional memory for an integer of value `i`, float of value `f` ,
`double` of value `d` and `char *` of value `s`, and returns a pointer to them.


---

    void free_mem(TARGET, FREE_FUNC);
    void free_mem_arr(TARGET, NELEM, FREE_FUNC);
    void free_mem_2darr(TARGET, ROWS, COLS, FREE_FUNC);

`free_mem()`, `free_mem_arr()` and `free_mem_2darr()` frees target `TARGET`,
with `FREE_FUNC`. If `TARGET` is a 2 dimensional array, rows `ROWS`, columns
`COLS` need to be supplied in `free_mem_2darr()`.



## String

    int trim_char(const char c);

`trim_char()` is a boolean function that determins whether character `c` should
be trimmed or not, if `c` should be trimmed, the function trims on:

- newline `\n` or `\r`
- tabs `\t`
- space `' '`

if the function matches any of the above it returns `1` else `0`.


---

    char *trim(const char *s);

`trim()` trims the string `s` of any newline characters `\n` or `\r`, tabs `\t`
and spaces `' '`. Then returns a trimmed version.



## Random

    int randi(int min, int max);
    float randf(float min, float max);

`randi()` and `randf()` generates a random integer or float between `min` and
`max`.



## Comparator

    int intcmp(const void *v1, const void *v2);
    int intcmp_asc(const void *v1, const void *v2);
    int intcmp_desc(const void *v1, const void *v2);
    int fltcmp(const void *v1, const void *v2);
    int fltcmp_asc(const void *v1, const void *v2);
    int fltcmp_desc(const void *v1, const void *v2);
    int dblcmp(const void *v1, const void *v2);
    int dblcmp_asc(const void *v1, const void *v2);
    int dblcmp_desc(const void *v1, const void *v2);

Compare between `v1` and `v2` of type integer, float or double with `intcmp*`,
`fltcmp*`, `dblcmp*` in ascending order or descending order. By default
`intcmp()`, `fltcmp()` and `dblcmp()` compares in descending order.

**Note**: Comparing floating and doubles points is hard, the implementation
used is by defining the error margin `FLOAT_EPSILON`, by default it is set to
`0.00001`, however depending on your use case you may want to adjust the
acceptable error margin. You can do this by defining your own `FLOAT_EPSILON`
when compiling cog, you must do that during the compilation of cog else it will
not take effect when you link it with your code.

In descending order the function will return:

- `1` if `v1` is larger than `v2`
- `-1` if `v2` is larger than `v1`
- `0` if `v1` equals `v2`

The reverse is true for ascending order.


---

    int cmp_values(int value_type, void *v1, void *v2);

`cmp_values()` provides a wrapper to conveniently compare `v1` and `v2` of
`value_type`:

- `INTEGER`
- `FLOAT`
- `DOUBLE`
- `STRING`


### File

    off_t fsize(const char *file_path)

Obtain the file size residing in `file_path`, returns the file size in type
`off_t` or `-1` on failure.

---

    char *fstring(const char *file_path)

Opens and reads the file residing in `file_path` as a string.

---

    int fexists(const char *file_path)

Determines whether a file at `file_path` exists, returns `1` and `0` for `true`
or `false`.


### Path

    char *path_join(int len, ...);

Join paths together, it operates similar to Python's `os.path.join()`.
