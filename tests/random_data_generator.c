#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "utils.h"

#define DATAFILE_INTEGER 1
#define DATAFILE_FLOAT 2
#define DATAFILE_STRING 3

/* PROTOYPES */
void print_usage(void);
struct options *parse_args(int argc, char *argv[]);
int randfile_gen(struct options *options);


struct options
{
    /* general */
    char *file_dest;
    int type;

    /* bounds for integer and float */
    int lower_bound;
    int upper_bound;

    /* random string length */
    size_t str_len;

    /* number of elements to generate */
    int size;
};

void print_usage(void)
{
    char *prog_name = "randdfile";

    printf("Program: %s\n", prog_name);
    printf("Description: The program generates a random data file, each\n");
    printf("line containing an integer, float, or string.\n");
    printf("\n");

    printf("Usage: %s [-t TYPE][SETTINGS][-s NUMBER]\n", prog_name);
    printf("\n");

    printf("Type -t:\n");
    printf("\t- integer\n");
    printf("\t- float\n");
    printf("\t- string\n");
    printf("\n");

    printf("Settings :\n");
    printf("\tIf TYPE is int or float, lower and upper bound bounds is \n");
    printf("\trequired like so:\n");
    printf("\t\t%s -t integer 0 100 output.txt -s 100\n", prog_name);
    printf("\n");

    printf("-s Size:\n");
    printf("Number to define how many randome elements to generate\n\n");
    printf("\n");
}

struct options *parse_args(int argc, char *argv[])
{
    struct options *options = malloc(sizeof(struct options));
    options->type = 0;
    options->str_len = 0;

    /* parse type */
    if (argc < 6) {
        goto error;

    } else if (strcmp(argv[1], "-t") == 0) {
        if (strcmp(argv[2], "integer") == 0
                && argv[3] != NULL
                && argv[4] != NULL
                && argv[5] != NULL) {
            options->type = DATAFILE_INTEGER;
            options->lower_bound = atoi(argv[3]);
            options->upper_bound = atoi(argv[4]);
            options->file_dest = argv[5];

        } else if (strcmp(argv[2], "float") == 0
                && argv[3] != NULL
                && argv[4] != NULL
                && argv[5] != NULL) {
            options->type = DATAFILE_FLOAT;
            options->lower_bound = atoi(argv[3]);
            options->upper_bound = atoi(argv[4]);
            options->file_dest = argv[5];

        } else if (strcmp(argv[2], "string") == 0
                && argv[3] != NULL
                && argv[4] != NULL) {
            options->type = DATAFILE_STRING;
            options->str_len = (size_t) atoi(argv[3]);
            options->file_dest = argv[4];

        } else {
            printf("ERROR! Failed to parse type settings!\n");
            goto error;

        }

    } else {
        printf("ERROR! Failed to parse type!\n");
        goto error;

    }

    /* parse size */
    if (argv[6] == NULL) {
        goto error;
    }

    if (options->type == DATAFILE_INTEGER || options->type == DATAFILE_FLOAT) {
        if (strcmp(argv[6], "-s") == 0 && argv[7] != NULL) {
            options->size = atoi(argv[7]);
        } else {
            printf("ERROR! Failed to parse Size!\n");
            goto error;
        }
    } else if (options->type == DATAFILE_STRING) {
        if (strcmp(argv[5], "-s") == 0 && argv[6] != NULL) {
            options->size = atoi(argv[6]);
        } else {
            printf("ERROR! Failed to parse size!\n");
            goto error;
        }
    } else {
        goto error;
    }

    return options;

error:

    printf("Missing or Invalid arguments!\n");
    printf("\n\n");
    print_usage();

    free(options);
    options = NULL;

    return options;
}

int randfile_gen(struct options *options)
{
    char *file_dest = options->file_dest;
    int type = options->type;
    size_t str_len = options->str_len;
    int size = options->size;

    int i = 0;
    float f = 0.0;
    char *s;

    int j = 0;

    FILE *fp = fopen(file_dest, "wb");
    check(fp, "Failed to open file for writing!");

    printf("Creating data file\n");
    for (j = 0; j < size; j++) {
        switch (type) {
            case DATAFILE_INTEGER:
                i = randi(0, 100);
                fprintf(fp, "%d\n", i);
                break;
            case DATAFILE_FLOAT:
                f = randf(0, 100);
                fprintf(fp, "%.2f\n", f);
                break;
            case DATAFILE_STRING:
                s = randstr(str_len);
                fprintf(fp, "%s\n", s);
                break;
            default:
                goto error;
        }

        if (j != 0 && (j % 1000) == 0) {
            printf("wrote [%d] lines\n", j);
        }
    }

    /* display last "wrote ... lines" */
    if (j != 0 && (j % 1000) == 0) {
        printf("wrote [%d] lines\n", j);
    }

    /* clean up */
    fclose(fp);
    free(options);

    return 0;

error:

    /* clean up */
    if (fp != NULL) {
        fclose(fp);
    }
    free(options);
    return -1;
}

int main(int argc, char *argv[])
{
    struct options *opts;

    /* SEED RANDOM! VERY IMPORTANT!! */
    srand((unsigned int) time(NULL));

    /* parse arguments and generate data file */
    if ((opts = parse_args(argc, argv)) != NULL) {
        if (randfile_gen(opts) == 0) {
            printf("Done! :)\n");
        } else {
            printf("ERROR! Failed to generate file\n");
            goto error;
        }
    } else {
        goto error;
    }

    return 0;
error:
    return -1;
}
