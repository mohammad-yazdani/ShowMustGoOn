#include <stdio.h>
#include <stdlib.h>
#include "page.h"

int main() {
    printf("Hello, World!\n");
    page *test_page = malloc(sizeof(page));
    char key0[] = "0123456";
    int res = page_create(test_page, key0, 0);
    if (res) {
        exit(res);
    }

    char test[12] = "01234567891";
    uintptr_t res_push = page_insert(test_page, "test", (uintptr_t) test);
    if (res_push) {
        // TODO : Critical
        exit((int) res_push);
    }

	char test1[12] = "01234567891";
    res_push = page_insert(test_page, "test2", (uintptr_t) test1);
    if (res_push) {
        // TODO : Critical
        exit((int) res_push);
    }

    printf("%s", page_to_json(test_page));

    return 0;
}
