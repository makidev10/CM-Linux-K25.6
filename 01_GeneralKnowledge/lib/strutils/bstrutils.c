#include "strutils.h"
#include <ctype.h>
#include <string.h>

char *str_reverse(char *str, size_t length) {
  if (str == NULL)
    return NULL;

  for (size_t i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }

  return str;
}

char *str_trim(char *str) {
  if (str == NULL)
    return NULL;

  while (isspace((unsigned char)*str))
    str++;

  char *end = str + strlen(str) - 1;

  while (end > str && isspace((unsigned char)*end))
    end--;

  *(end + 1) = '\0';

  return str;
}

int str_to_int(char *str, size_t length) {
  if (str == NULL)
    return 0;

  int result = 0;
  int sign = 1;
  size_t index = 0;
  int temp = 0;
  (void)str_trim(str);

  if (str[0] == '-') {
    sign = -1;
    index++;
  }

  for (; index < length; index++) {
    temp = str[index] - '0';
    result = result * 10 + temp;
  }

  result = result * sign;

  return result;
}
