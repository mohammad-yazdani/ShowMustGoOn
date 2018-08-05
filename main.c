#include <stdio.h>
#include <stdlib.h>
#include <json.h>
#include "page.h"

int main() {
    printf("Hello, World!\n");
    page *test_page = malloc(sizeof(page));
    char key0[] = "0123456";
    int res = page_create(test_page, key0, 0);
    if (res) exit(res);

    char test[12] = "01234567891";
    uintptr_t res_push = page_insert(test_page, "test", (uintptr_t) test);
    if (res_push) exit((int) res_push);

	char test1[12] = "01234567891";
    res_push = page_insert(test_page, "test1", (uintptr_t) test1);
    if (res_push) exit((int) res_push);

    char test2[2] = "0";
    res_push = page_insert(test_page, "test2", (uintptr_t) test2);
    if (res_push == 1) exit((int) res_push);

    page *test_page1 = malloc(sizeof(page));
    char key1[] = "0122456";
    res = page_create(test_page1, key1, 0);
    if (res) exit(res);

    char test01[12] = "01234567891";
    res_push = page_insert(test_page1, "test", (uintptr_t) test01);
    if (res_push) exit((int) res_push);

    char test02[12] = "01234567891";
    res_push = page_insert(test_page1, "test1", (uintptr_t) test02);
    if (res_push) exit((int) res_push);

    char test03[2] = "0";
    res_push = page_insert(test_page1, "test2", (uintptr_t) test03);
    if (res_push == 1) exit((int) res_push);

    page *test_page2 = malloc(sizeof(page));
    char key2[] = "test";
    res = page_create(test_page2, key2, 0);
    if (res) exit(res);

    char test11[12] = "01234567891";
    res_push = page_insert(test_page2, "test", (uintptr_t) test11);
    if (res_push) exit((int) res_push);

    char test12[12] = "01234567891";
    res_push = page_insert(test_page2, "test1", (uintptr_t) test12);
    if (res_push) exit((int) res_push);

    char test13[2] = "0";
    res_push = page_insert(test_page2, "test2", (uintptr_t) test13);
    if (res_push == 1) exit((int) res_push);

    page_insert(test_page, NULL, (uintptr_t) test_page1);
    page_insert(test_page, NULL, (uintptr_t) test_page2);
    char * json_unwrapped = page_to_json(test_page);
    char * json = block_wrap(json_unwrapped);
    free(json_unwrapped);
    printf("%s\n", json);
    free(json);

    page_destroy(test_page);

    return 0;
}
