#include <stdio.h>
#include <stdlib.h>
#include "page.h"

int main() {
    printf("Hello, World!\n");
    page *test_page = malloc(sizeof(page));
    char key0[] = "0123456";
    int res = page_create(test_page, 0, (uintptr_t) key0);
    if (res) {
        exit(res);
    }

    char test[12] = "01234567891";
    res = page_insert(test_page, "test", (uintptr_t) test);
    if (res) {
        exit(res);
    }

    size_t size = 0;
    char * json = page_dump(test_page, &size);
    printf("%s", json);

    return 0;
}
