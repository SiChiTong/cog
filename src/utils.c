#include "utils.h"


/* MEMORY */
void *copy_value(int value_type, void *value)
{
    void *copy = NULL;

    switch (value_type) {
    case INTEGER:
        copy = malloc(sizeof(int));
        *(int *) copy = *(int *) value;
        break;
    case FLOAT:
        copy = malloc(sizeof(float));
        *(float *) copy = *(float *) value;
        break;
    case DOUBLE:
        copy = malloc(sizeof(double));
        *(double *) copy = *(double *) value;
        break;
    case STRING:
        copy = malloc(sizeof(char) * strlen(value) + 1);
        strcpy(copy, value);
        break;
    }

    return copy;
}

int *malloc_int(int i)
{
    int *int_ptr = malloc(sizeof(int));
    *(int *) int_ptr = i;
    return int_ptr;
}

float *malloc_float(float f)
{
    float *float_ptr = malloc(sizeof(float));
    *(float *) float_ptr = f;
    return float_ptr;
}

double *malloc_double(double d)
{
    double *double_ptr = malloc(sizeof(double));
    *(double *) double_ptr = d;
    return double_ptr;
}

char *malloc_string(const char *s)
{
    char *str_ptr = malloc(sizeof(char) * strlen(s) + 1);
    strcpy(str_ptr, s);
    return str_ptr;
}


/* STRING */
int trim_char(const char c)
{
    int i;
    const char trim[4] = {'\n', '\t', '\r', ' '};

    for (i = 0; i < (int) strlen(trim); i++) {
        if (c == trim[i]) {
            return 1;
        }
    }

    return 0;
}

char *trim(const char *s)
{
    int i = 0;
    int left = 0;
    int right= 0;
    char *trimmed = NULL;

    /* pre-check */
    silent_check(s != NULL);

    /* trim left */
    while (i < (int) strlen(s) && trim_char(s[i])) i++;
    left = i;

    /* trim right */
    i = (int) strlen(s) - 1;
    while (i > 0 && trim_char(s[i])) i--;
    right = i;

    /* return trimmed string */
    trimmed = malloc(sizeof(char) * (unsigned long) (right - left + 2));
    strncpy(trimmed, s + left, (unsigned long) (right - left + 1));
    trimmed[(right - left) + 1] = '\0';

    return trimmed;
error:
    return NULL;
}


/* RANDOM */
int randi(int min, int max)
{
    int divisor = RAND_MAX / (max + 1);
    int retval = rand() / divisor;

    check(max > min, "Lower bound is bigger than upper bound!");
    while (retval < min || retval > max) {
        retval = rand() / divisor;
    }

    return retval;
error:
    return min + 1;
}

float randf(float min, float max)
{
    float divisor = (float) RAND_MAX / (float) (max + 1.0);
    float retval = rand() / divisor;

    check(max > min, "Lower bound is bigger than upper bound!");
    while (retval < min || retval > max) {
        retval = rand() / divisor;
    }

    return retval;
error:
    return min + 1;
}

char *randstr(size_t length)
{
    size_t i;
    char *r_str;

    r_str  = malloc(sizeof(char *) * length);
    check_mem(r_str);

    /* generate random ASCII char */
    memset(r_str, '\0', sizeof(char *) * length);
    for (i = 0; i < length; i++) {
        r_str[i] = (char) randi(32, 122);
    }

    r_str[length] = '\0'; /* add null terminator for safety */
    return r_str;
error:
    free_mem(r_str, free);
    return NULL;
}

void *sample(void **array, int array_length)
{
    return array[randi(0, array_length)];
}


/* COMPARATOR */
int intcmp(const void *v1, const void *v2)
{
    /* null-check */
    if (v1 == NULL || v2 == NULL) {
        if (v1 == NULL) {
            return -1;
        } else if (v1 == NULL) {
            return 1;
        } else {
            return 0;
        }
    }

    if (*(int *) v1 > *(int *) v2) {
        return 1;
    } else if (*(int *) v1 < *(int *) v2) {
        return -1;
    } else {
        return 0;
    }
}

int intcmp_asc(const void *v1, const void *v2)
{
    return intcmp(v1, v2);
}

int intcmp_desc(const void *v1, const void *v2)
{
    return intcmp(v1, v2) * -1;
}

int fltcmp(const void *v1, const void *v2)
{
    /* null-check */
    if (v1 == NULL || v2 == NULL) {
        if (v1 == NULL) {
            return -1;
        } else if (v1 == NULL) {
            return 1;
        } else {
            return 0;
        }
    }

    /* compare floats */
    if (fabs(*(float *) v1 - *(float *) v2) <= FLOAT_EPSILON) {
        return 0;
    } else if (*(float *) v1 > *(float *) v2) {
        return 1;
    } else if (*(float *) v1 < *(float *) v2) {
        return -1;
    } else {
        printf("Error! Undefined runtime behaviour!\n");
        return -1;
    }
}

int fltcmp_asc(const void *v1, const void *v2)
{
    return fltcmp(v1, v2);
}

int fltcmp_desc(const void *v1, const void *v2)
{
    return fltcmp(v1, v2) * -1;
}

int dblcmp(const void *v1, const void *v2)
{
    /* null-check */
    if (v1 == NULL || v2 == NULL) {
        if (v1 == NULL) {
            return -1;
        } else if (v1 == NULL) {
            return 1;
        } else {
            return 0;
        }
    }

    /* compare doubles */
    if (fabs(*(double *) v1 - *(double *) v2) <= FLOAT_EPSILON) {
        return 0;
    } else if (*(double *) v1 > *(double *) v2) {
        return 1;
    } else if (*(double *) v1 < *(double *) v2) {
        return -1;
    } else {
        printf("Error! Undefined runtime behaviour!\n");
        return -1;
    }
}

int dblcmp_asc(const void *v1, const void *v2)
{
    return dblcmp(v1, v2);
}

int dblcmp_desc(const void *v1, const void *v2)
{
    return dblcmp(v1, v2) * -1;
}

int cmp_values(int value_type, void *v1, void *v2)
{
    switch (value_type) {
    case INTEGER:
        return intcmp(v1, v2);
    case FLOAT:
        return fltcmp(v1, v2);
    case DOUBLE:
        return fltcmp(v1, v2);
    case STRING:
        return strcmp(v1, v2);
    default:
        return -2;
    }
}


/* FILE UTILS */
off_t fsize(const char *file_path)
{
    struct stat st;

    if (stat(file_path, &st) == 0) {
        return st.st_size;
    }

    return -1;
}

char *fstring(const char *file_path)
{
    FILE *fp;
    char *str;
    off_t file_size;

    fp = fopen(file_path, "r");
    file_size = fsize(file_path);
    str = calloc((size_t) file_size + 1, 1);
    fread(str, (size_t) file_size, 1, fp);

    return str;
}

int fexists(const char *file_path)
{
    if (access(file_path, F_OK) != -1) {
        return 1;
    } else {
        return 0;
    }
}


/* PATH UTILS */
char *path_join(int len, ...)
{
    int i;
    va_list args;
    char cache[256];
    char buf[1024];
    size_t path_length;
    size_t pointer;

    /* setup */
    pointer = 0;
    path_length = 0;
    bzero(buf, 1024);
    va_start(args, len);

    /* join */
    for (i = 0; i < len; i++) {
        bzero(cache, 256);
        strcpy(cache, va_arg(args, char *));

        /* add necessary slash */
        if (strlen(buf) != 0 && buf[strlen(buf) - 1] != '/') {
            sprintf(buf + pointer, "/%s", cache);
        } else {
            sprintf(buf + pointer, "%s", cache);
        }

        pointer += strlen(cache);
    }

    return malloc_string(buf);
}
