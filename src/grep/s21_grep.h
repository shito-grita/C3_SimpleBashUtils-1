#ifndef S21_GREP_H
#define S21_GREP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <dirent.h>

// Structure definitions
typedef struct {
    char **files;
    int num_files;
    char **patterns;
    int num_patterns;
    int ignore_case;
    int invert_match;
    int show_count_lines_only;
    int show_files_name_only;
    int show_lines_num;
    int show_no_files_name;
    int silent_mode;
    int show_matching_only;
    int has_empty_pattern;
    int regexp_cflags;
} s21_grep_settings;

// Function prototypes
void s21_push_to_string_array(char ***array, char *str, int *size);
char *s21_pull_from_string_array(char ***array, int *size);
void *s21_calloc(size_t count, size_t size);
void s21_grep_destroy_settings_files(s21_grep_settings *settings);
void s21_grep_destroy_settings_patterns(s21_grep_settings *settings);
void s21_grep_destroy_settings(s21_grep_settings *settings);
void s21_grep_print_instructions_and_exit();
void s21_grep_print_error(char *str);
s21_grep_settings s21_grep_get_settings(int argc, char *argv[]);
void s21_grep_print_settings(s21_grep_settings settings);
void s21_grep_parse_ffiles(s21_grep_settings *settings, char *filename);

#endif // S21_GREP_H
