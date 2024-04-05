#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void print_help() {
    printf("Usage: cvb [OPTION]... [FILENAME]\n"
           "Options:\n"
           "  --help             Display this help message and exit\n"
           "  -s n               Specify the starting line (n-th) to print\n"
           "  -e n               Specify the ending line (m-th) to print\n"
           "  -n [format]        Print lines with leading line numbers\n"
           "                     Optional format parameters:\n"
           "                       uint: Width of the line number field (numeric)\n"
           "                       R: Right-aligned (default)\n"
           "                       0: Right-aligned with leading zeros\n"
           "                       L: Left-aligned\n"
           "                       N: Line numbers start with zero\n"
           "  -v                 Print additional status and file information\n"
           "  -q                 Print only additional status and file information\n"
           "  --version          Display version information and exit\n");
}

void print_version() {
    printf("cvb version 1.0\n");
}

void print_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void print_lines(FILE *file, int start, int end, int number_width) {
    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (line_number >= start && line_number <= end) {
            if (number_width > 0) {
                printf("%*d: %s", number_width, line_number, line);
            } else {
                printf("%s", line);
            }
        }
        if (line_number > end) {
            break;
        }
        line_number++;
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    int start = 1, end = -1, number_width = 0;
    int print_info = 0;
    char *filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                start = atoi(argv[++i]);
            } else {
                print_error("Option -s requires an argument.");
            }
        } else if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc) {
                end = atoi(argv[++i]);
            } else {
                print_error("Option -e requires an argument.");
            }
        } else if (strcmp(argv[i], "-n") == 0) {
            number_width = 0;  // default
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                if (strcmp(argv[i + 1], "R") == 0 || strcmp(argv[i + 1], "0") == 0 || strcmp(argv[i + 1], "L") == 0 || strcmp(argv[i + 1], "N") == 0) {
                    i++;
                    if (strcmp(argv[i], "0") == 0) {
                        number_width = atoi(argv[++i]);
                    }
                }
            }
        } else if (strcmp(argv[i], "-v") == 0) {
            print_info = 1;
        } else if (strcmp(argv[i], "-q") == 0) {
            print_info = 2;
        } else {
            filename = argv[i];
        }
    }

    if (filename == NULL || strcmp(filename, "-") == 0) {
        file = stdin;
    } else {
        file = fopen(filename, "r");
        if (file == NULL) {
            print_error("Error opening file.");
        }
    }

    if (print_info == 1) {
        printf("Printing information...\n");
        // print additional status and file information
    } else if (print_info == 2) {
        printf("Printing only additional information...\n");
        // print only additional status and file information
    }

    print_lines(file, start, end, number_width);

    if (file != stdin) {
        fclose(file);
    }

    return 0;
}




//./cvb -s 8 -e 18 70salbumcharts.txt