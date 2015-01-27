#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

/* MACROS */
#define INT_DATA 1
#define FLOAT_DATA 2

#define INT_TESTDATA "tests/test_files/int_100000.txt"
#define FLOAT_TESTDATA "tests/test_files/float_100000.txt"

/* FUNCTIONS */
void *init_testdata(const int num_el, int data_type, const char *testfile_fp);
void print_array(void *array, int num_el, int type);
int assert_sorted_array(
    void *array,
    int num_el,
    size_t el_sz,
    int(*cmp)(const void *,const void *)
);

#endif
