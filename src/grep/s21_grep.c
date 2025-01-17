#include "s21_grep.h"

void s21_print_only_matches(const char *line, const GrepOptions *options) {
  for (int i = 0; i < options->pattern_count; i++) {
    regex_t regex;
    regcomp(&regex, options->pattern[i],
            REG_EXTENDED | (options->ignore_case ? REG_ICASE : 0));
    const char *match_start = line;
    while ((match_start = strstr(match_start, options->pattern[i])) != NULL) {
      printf("%s\n", options->pattern[i]);
      match_start += strlen(options->pattern[i]);
    }
    regfree(&regex);
  }
}
void s21_count_matches(int *total_matches, const char *line,
                       const GrepOptions *options) {
  for (int i = 0; i < options->pattern_count; i++) {
    regex_t regex;
    regcomp(&regex, options->pattern[i],
            REG_EXTENDED | (options->ignore_case ? REG_ICASE : 0));
    if (!regexec(&regex, line, 0, NULL, 0)) {
      (*total_matches)++;
    }
    regfree(&regex);
  }
}

void s21_grep(const GrepOptions *options, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (!options->silent) {
      perror(filename);
    }
    return;
  }

  char line[MAX_LINE_LENGTH];
  int line_number = 0;
  int total_matches = 0;
  int file_has_match = 0;

  while (fgets(line, sizeof(line), file)) {
    line_number++;
    int match_found = 0;

    for (int i = 0; i < options->pattern_count; i++) {
      regex_t regex;
      regcomp(&regex, options->pattern[i],
              REG_EXTENDED | (options->ignore_case ? REG_ICASE : 0));
      if (!regexec(&regex, line, 0, NULL, 0)) {
        match_found = 1;
        regfree(&regex);
        break;
      }
      regfree(&regex);
    }

    if ((match_found && !options->invert_match) ||
        (!match_found && options->invert_match)) {
      file_has_match = 1;

      if (options->list_files) {
        printf("%s\n", filename);
        fclose(file);
        return;
        break;
      }

      if (options->count_only) {
        s21_count_matches(&total_matches, line, options);
      } else {
        if (options->show_filename) {
          printf("%s:", filename);
        }

        if (options->show_line_numbers) {
          printf("%d:", line_number);
        }

        if (options->only_matches) {
          s21_print_only_matches(line, options);
        } else {
          printf("%s", line);
        }
      }
    }
  }
  if (options->count_only && !options->list_files) {
    printf("%d\n", total_matches);
  }

  if (!file_has_match && !options->silent && !options->list_files) {
    printf("No matches found in %s\n", filename);
  }

  fclose(file);
}

void s21_init_options(GrepOptions *options) {
  options->show_filename = 0;
  options->only_matches = 0;
  options->invert_match = 0;
  options->count_only = 0;
  options->list_files = 0;
  options->show_line_numbers = 0;
  options->pattern_count = 0;
  options->ignore_case = 0;
  options->silent = 0;
  options->pattern = malloc(INITIAL_PATTERN_CAPACITY * sizeof(char *));
  if (!options->pattern) {
    exit(EXIT_FAILURE);
  }
}

void s21_add_pattern(GrepOptions *options, char *pattern,
                     int *pattern_capacity) {
  if (options->pattern_count >= *pattern_capacity) {
    *pattern_capacity *= 2;
    options->pattern =
        realloc(options->pattern, *pattern_capacity * sizeof(char *));
    if (!options->pattern) {
      exit(EXIT_FAILURE);
    }
  }
  options->pattern[options->pattern_count] =
      malloc((strlen(pattern) + 1) * sizeof(char));
  if (!options->pattern[options->pattern_count]) {
    exit(EXIT_FAILURE);
  }
  strcpy(options->pattern[options->pattern_count++], pattern);
}

static void s21_parse_flags(int *pos, int argc, char *argv[],
                            GrepOptions *options, int *pat_cap) {
  while (*pos < argc && argv[*pos][0] == '-') {
    if (strcmp(argv[*pos], "-e") == 0) {
      s21_parse_minus_e(pos, argc, argv, options, pat_cap);
    } else if (strcmp(argv[*pos], "-f") == 0) {
      s21_parse_minus_f(pos, argc, argv, options, pat_cap);
    } else {
      s21_parse_single_flag(argv[*pos], options);
    }
    (*pos)++;
  }
}

void s21_parse_arguments(int argc, char *argv[], GrepOptions *options) {
  s21_init_options(options);
  int pattern_capacity = INITIAL_PATTERN_CAPACITY;
  int pos = 1;

  s21_parse_flags(&pos, argc, argv, options, &pattern_capacity);

  if (options->pattern_count == 0 && pos < argc) {
    s21_add_pattern(options, argv[pos++], &pattern_capacity);
  }

  if (options->pattern_count == 0) {
    fprintf(stderr, "Error: pattern not found\n");
    exit(EXIT_FAILURE);
  }

  if (pos >= argc) {
    fprintf(stderr, "Error: files not found\n");
    exit(EXIT_FAILURE);
  }

  for (; pos < argc; pos++) {
    s21_grep(options, argv[pos]);
  }
}

static void s21_parse_single_flag(const char *flag, GrepOptions *options) {
  for (int i = 1; flag[i] != '\0'; i++) {
    switch (flag[i]) {
      case 'i':
        options->ignore_case = 1;
        break;
      case 'v':
        options->invert_match = 1;
        break;
      case 'n':
        options->show_line_numbers = 1;
        break;
      case 'h':
        options->show_filename = 0;
        break;
      case 's':
        options->silent = 1;
        break;
      case 'l':
        options->list_files = 1;
        break;
      case 'c':
        options->count_only = 1;
        break;
      case 'o':
        options->only_matches = 1;
        break;
      default:
        fprintf(stderr, "Error: cant resolve flag -%c\n", flag[i]);
        break;
    }
  }
}

static void s21_parse_minus_e(int *pos, int argc, char *argv[],
                              GrepOptions *options, int *pat_cap) {
  if (*pos + 1 >= argc) {
    fprintf(stderr, "Error: -e requires template\n");
    exit(EXIT_FAILURE);
  }
  (*pos)++;
  s21_add_pattern(options, argv[*pos], pat_cap);
}

static void s21_parse_minus_f(int *pos, int argc, char *argv[],
                              GrepOptions *options, int *pat_cap) {
  if (*pos + 1 >= argc) {
    fprintf(stderr, "Error: -f file is missing\n");
    exit(EXIT_FAILURE);
  }
  (*pos)++;
  FILE *pf = fopen(argv[*pos], "r");
  if (!pf) {
    perror(argv[*pos]);
    exit(EXIT_FAILURE);
  }
  char line[1024];
  while (fgets(line, sizeof(line), pf)) {
    line[strcspn(line, "\n")] = '\0';
    s21_add_pattern(options, line, pat_cap);
  }
  fclose(pf);
}

int main(int argc, char *argv[]) {
  GrepOptions options;
  s21_parse_arguments(argc, argv, &options);
  return 0;
}
