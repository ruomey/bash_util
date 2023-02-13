#include <stdio.h>
#include <string.h>

#include "s21_cat.h"

void open_file(int argc, char *argv[1000], int option, int isFlag) {
  int k = 0;
  if (option == 2) {
    k = 1;
  }
  int i = 1;
  for (; i < argc; i++) {
    if (i != isFlag) {
      FILE *file = fopen(argv[i], "r");
      char ch = ' ';
      if (file != NULL) {
        int word = 0;
        int flag_end_str = 1, flag_str_void = 0;
        int count_string = 0, start_str = 1;
        while ((ch = fgetc(file)) != EOF) {
          if (option == 0) {
            non_flag(ch);
          }
          if (option == 2) {
            flag_b(ch, &word, &k);
          } else if (option == 1) {
            flag_e(ch, option);
          } else if (option == 3) {
            flag_n(ch, &k, &flag_end_str, &start_str);
          } else if (option == 4) {
            void_string(ch, &flag_end_str, &flag_str_void, &count_string);
            flag_s(ch, count_string);
          } else if (option == 6) {
            flag_v(ch, option);
          } else if (option == 5) {
            flag_t(ch, option);
          } else if (option == 7) {
            if (ch == 9) {
              printf("^I");
            } else {
              printf("%c", ch);
            }
          } else if (option == 8) {
            if (ch == 10) {
              printf("$\n");
            } else {
              printf("%c", ch);
            }
          }
        }
      } else if (file == NULL) {
        fprintf(stderr, "%s: No such file in dir\n", argv[i]);
        continue;
      }
      fclose(file);
    }
  }
}

void flag_e(char ch, int option) {
  flag_v(ch, option);
  if (ch == '\n') {
    printf("$\n");
  }
}
void flag_t(char ch, int option) {
  flag_v(ch, option);
  if (ch == '\t') {
    printf("^I");
  }
}
void flag_n(char ch, int *count, int *end_str, int *start_str) {
  if ((*end_str) && ch) {
    *start_str = 1;
  } else if (ch == '\n' && !(*end_str)) {
    (*end_str) = 1;
  }
  if ((*end_str) && (*start_str)) {
    (*count)++;
    printf("%6d\t%c", *count, ch);
    if (ch == '\n') {
      (*end_str) = 1;
    } else {
      (*end_str) = 0;
    }
    (*start_str) = 0;
  } else {
    printf("%c", ch);
  }
}

void flag_b(char ch, int *word, int *n) {
  if (ch == '\n') {
    printf("\n");
    *word = 0;
  } else {
    if (!*word) {
      printf("%6d\t%c", *n, ch);
      *word = 1;
      *n = *n + 1;
    } else {
      printf("%c", ch);
    }
  }
}

void flag_s(char ch, int count_string) {
  if (!count_string) {
    printf("%c", ch);
  } else {
    if (count_string == 1) {
      printf("\n");
    }
  }
}

void non_flag(char ch) { printf("%c", ch); }

void flag_v(char ch, int option) {
  if (ch == 10 && option != 1) {
    printf("\n");
  }
  if (ch == 9 && option != 5) {
    printf("\t");
  }
  if (ch <= 31 && ch != 10 && ch != '\t') {
    ch = ch + 64;
    printf("^%c", ch);
  } else if (ch > 31 && ch != 127) {
    printf("%c", ch);
  } else if (ch == 127) {
    printf("^?");
  }
}
