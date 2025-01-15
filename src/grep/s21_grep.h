#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PATTERN_LENGTH 256
#define INITIAL_PATTERN_CAPACITY 10

typedef struct {
  char **pattern;
  int pattern_count;
  int show_filename;      // Флаг -h:
  int only_matches;       // Флаг -o:
  int invert_match;       // Флаг -v:
  int count_only;         // Флаг -c:
  int list_files;         // Флаг -l:
  int show_line_numbers;  // Флаг -n:
  int ignore_case;        // Флаг -i:
  int silent;             // Флаг -s:
} GrepOptions;

void s21_print_only_matches(const char *line, const GrepOptions *options);
void s21_count_matches(int *total_matches, const char *line,
                       const GrepOptions *options);
void s21_grep(const GrepOptions *options, const char *filename);
void s21_parse_arguments(int argc, char *argv[], GrepOptions *options);

#endif  // S21_GREP_H_
