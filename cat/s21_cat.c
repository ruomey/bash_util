#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  int isFlag = 0;
  int option = 0;
  for (int i = 0; i < argc; i++) {
    if ((option = condition_args(argv[i]))) {
      isFlag = i;
      break;
    }
  }
  open_file(argc, argv, option, isFlag);
  return 0;
}
