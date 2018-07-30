#include <stdio.h>
#include "page.h"

int main() {
    printf("Hello, World!\n");
    page *test_page = malloc(sizeof(page));
    int res = page_create(test_page, 0, "01234567");
    if (res) {
        exit(res);
    }

    char test[12] = "01234567891";
    res = page_insert(test_page, (uintptr_t) test);
    if (res) {
        exit(res);
    }

    char json[1] = "";
    page_dump(test_page, json);
    printf(json);

    return 0;
}