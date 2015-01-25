#include <stdlib.h>
#include <string.h>
#include <math.h>

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
