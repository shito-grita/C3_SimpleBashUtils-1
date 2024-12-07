#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    const char *filename;
    int number_lines;       // Флаг -n
    int number_nonblank;    // Флаг -b
    int squeeze_blank;      // Флаг -s
    int show_ends;          // Флаг -e
    int show_tabs;          // Флаг -t
} CatOptions;

void print_file(CatOptions options) 
{
    FILE *file = fopen(options.filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }
    int c, prev_c = 0;
    int line_number = 1;
    while ((c = fgetc(file)) != EOF) 
    {
        if (c == '\n') 
        {
            if (options.number_lines) 
            {
                printf("%6d\t", line_number++);
            }
            putchar(c);
            prev_c = c;
            continue;
        }

        if (options.squeeze_blank && c == ' ' && prev_c == ' ') 
        {
            continue; 
        }

        if (options.number_nonblank && c != '\n' && prev_c == '\n') 
        {
            printf("%6d\t", line_number++);
        }

        if (options.show_ends && c == '\n') 
        {
            putchar('$');
        }

        if (options.show_tabs && c == '\t') 
        {
            putchar('^');
            putchar('I');
            prev_c = c;
            continue;
        }

        putchar(c);
        prev_c = c;
    }

    fclose(file);
}

int main(int argc, char *argv[]) 
{
    CatOptions options;
    for (int i = 1; i < argc; i++) 
    {
        options.filename = argv[i];
        options.number_lines = 0;
        options.number_nonblank = 0;
        options.squeeze_blank = 0;
        options.show_ends = 0;
        options.show_tabs = 0;

        for (int j = 1; argv[i][j] != '\0'; j++) 
        {
            switch (argv[i][j]) 
            {
                case 'b':
                    options.number_nonblank = 1; 
                    break;
                case 'e':
                    options.show_ends = 1;       
                    break;
                case 'n':
                    options.number_lines = 1;   
                    break;
                case 's':
                    options.squeeze_blank = 1;   
                    break;
                case 't':
                    options.show_tabs = 1;    
                    break;
                default:
                    break;
            }
        }
        if (argv[i][0] != '-') 
        {
            print_file(options);
        }
    }
    return 0;
}
