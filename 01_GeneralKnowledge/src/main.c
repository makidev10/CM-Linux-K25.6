#include "../lib/strutils/strutils.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("Hello World\n");

    char str[] = "   Dung Tran ";
    printf("str: '%s'\n", str);

    printf("str after trim: '%s'\n", str_trim(str));

    printf("str after reverse: '%s'\n", str_reverse(str, strlen(str)));

    char num[] = "-10";
    printf("number: %d\n", str_to_int(num, strlen(num)));

    return 0;
}
