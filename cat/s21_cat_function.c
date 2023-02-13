#include <stdio.h>
#include <string.h>

#include "s21_cat.h"

int condition_args(char *argv) {
  int flag = 0;
  if (strcmp(argv, "-e") == 0) {
    flag = 1;
  } else if (strcmp(argv, "-b") == 0 ||
             strcmp(argv, "--number-nonblank") == 0) {
    flag = 2;
  } else if (strcmp(argv, "-n") == 0 || strcmp(argv, "--number") == 0) {
    flag = 3;
  } else if (strcmp(argv, "-s") == 0 || strcmp(argv, "--squeeze-blank") == 0) {
    flag = 4;
  } else if (strcmp(argv, "-t") == 0) {
    flag = 5;
  } else if (strcmp(argv, "-v") == 0) {
    flag = 6;
  } else if (strcmp(argv, "-T") == 0) {
    flag = 7;
  } else if (strcmp(argv, "-E") == 0) {
    flag = 8;
  } else if (strcmp(argv, "-i") == 0) {
    flag = 9;
  } else if (strcmp(argv, "-l") == 0) {
    flag = 10;
  }
  return flag;
}
int void_string(char ch, int *flag_end_str, int *flag_str_void,
                int *count_void_str) {
  if (ch == '\n') {
    if (!(*flag_str_void) && !(*flag_end_str)) {
      *flag_end_str = 1;
    } else if ((*flag_end_str) && !(*flag_str_void)) {
      *flag_str_void = 1;
      (*count_void_str)++;
    } else if ((*flag_str_void) && (*flag_end_str)) {
      (*count_void_str)++;
    }
  } else {
    *flag_str_void = 0;
    *flag_end_str = 0;
    *count_void_str = 0;
  }
  return (*count_void_str);
}
