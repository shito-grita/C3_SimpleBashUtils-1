#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define PNAME "s21_cat"
#define FLAGS "benstv"

typedef struct {
    char **files;
    int num_files;
    int num_flags;
    int num_all_lines;
    int num_not_empty_lines;
    int show_hidden;
    int show_line_feed;
    int show_tab;
    int squeeze_blank;
} s21_cat_settings;

typedef struct {
    int line_cnt;
    int num_chars;
    int ch;
    int previous_ch;
    int num_line_feeds_in_row;
    int is_new_line;
    int is_print_line_num;
} s21_cat_state;
void s21_print_error(const char *name, const char *str);
void s21_cat_print_error(char *str);
void s21_cat_print_dir_error(char *filename);
void s21_cat_print_fopen_error(char *filename);
void s21_cat_print_usage_error(char *str);

s21_cat_settings s21_get_cat_settings(int argc, char *argv[]);
void s21_cat_parse_short_settings(char argv, s21_cat_settings *settings);
void s21_cat_parse_long_settings(char *argv, s21_cat_settings *settings);

void s21_reset_state(s21_cat_state *state);
void s21_cat_file(char *filename, s21_cat_settings settings);
void s21_print_special_char(int c, s21_cat_settings settings);
void s21_cat_proccess_flag_b(s21_cat_state *state);
void s21_cat_proccess_flag_n(s21_cat_state *state);
int s21_cat_proccess_flag_s(s21_cat_state *state, s21_cat_settings settings);
void s21_destroy_settings(s21_cat_settings settings);
void s21_push_to_string_array(char ***array, char *value, int *size);

#endif  // S21_CAT_H