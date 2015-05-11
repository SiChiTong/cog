#ifndef __UTILS_H__
#define __UTILS_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


/* DEBUG / LOG */
#ifdef NDEBUG
  #define debug(M, ...)
#else
  #define debug(M, ...) \
      fprintf(stderr, \
          "[DEBUG] %s:%d: " M "\n", \
          __func__, \
          __LINE__, \
          ##__VA_ARGS__ \
      )
#endif
#define log_err(M, ...) \
    fprintf(stderr,\
        "[ERROR] (%s:%d) " M "\n",\
        __FILE__,\
        __LINE__,\
        ##__VA_ARGS__\
    )
#define log_warn(M, ...) \
    fprintf(stderr, "[WARN] " M "\n", ##__VA_ARGS__)
#define log_info(M, ...) \
    fprintf(stderr, "[INFO] " M "\n", ##__VA_ARGS__)



/* CONTROL FLOW */
#define check(A, M, ...) \
    if (!(A)) { \
        log_err(M, ##__VA_ARGS__); \
        goto error; \
    }
#define check_mem(A) check((A), "out of memory.")
#define check_debug(A, M, ...) \
    if (!(A)) { \
        debug(M, ##__VA_ARGS__); \
        goto error; \
    }
#define silent_check(A) \
    if (!(A)) { \
        goto error; \
    }



/* MEMORY */
#define INTEGER 0
#define FLOAT 1
#define DOUBLE 2
#define STRING 3

void *copy_value(int value_type, void *value);
int *malloc_int(int i);
float *malloc_float(float f);
double *malloc_double(double d);
char *malloc_string(const char *s);
#define free_mem(TARGET, FREE_FUNC) \
    if (TARGET) { \
        if (FREE_FUNC != NULL) { \
            FREE_FUNC((void *) TARGET); \
        } else { \
            log_err("free function not set!"); \
        } \
    }

#define free_mem_arr(TARGET, NELEM, FREE_FUNC) \
    int _i; \
    if (TARGET) { \
        for (_i = 0; _i < NELEM; _i++) { \
            FREE_FUNC((void *) TARGET[_i]); \
        } \
        FREE_FUNC((void *) TARGET); \
    }

#define free_mem_2darr(TARGET, ROWS, COLS, FREE_FUNC) \
    int _j; \
    int _k; \
    if (TARGET) { \
        for (_j = 0; _j < COLS; _j++) { \
            for (_k = 0; _k < ROWS; _k++) { \
                FREE_FUNC((void *) TARGET[_j][_k]); \
            } \
            FREE_FUNC((void *) TARGET[_j]); \
        } \
        FREE_FUNC((void *) TARGET); \
    }



/* STRING */
int trim_char(const char c);
char *trim(const char *s);
char **split_kv(const char *s, const char token);
char **split(const char *s, const char *token);


/* RANDOM */
int randi(int min, int max);
float randf(float min, float max);
char *randstr(size_t length);
void *sample(void **array, int array_length);



/* COMPARATOR */
#ifndef FLOAT_EPSILON
    #define FLOAT_EPSILON 0.00001
#endif

int intcmp(const void *v1, const void *v2);
int intcmp_asc(const void *v1, const void *v2);
int intcmp_desc(const void *v1, const void *v2);

int fltcmp(const void *v1, const void *v2);
int fltcmp_asc(const void *v1, const void *v2);
int fltcmp_desc(const void *v1, const void *v2);

int dblcmp(const void *v1, const void *v2);
int dblcmp_asc(const void *v1, const void *v2);
int dblcmp_desc(const void *v1, const void *v2);

int cmp_values(int value_type, void *v1, void *v2);


/* FILE UTILS */
off_t fsize(const char *file_path);
char *fstring(const char *file_path);
char **flines(const char *file_path);
int fexists(const char *file_path);
char *fext(const char *file_path);


/* PATH UTILS */
char *path_join(int len, ...);


/* MISC */
#define UNUSED(X) (void)(X)


#endif
