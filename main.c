#include <stdio.h>
#include <tlb.h>
#include <time.h>
#include <util/strutil.h>
#include <string.h>
#include <io/db.h>

#define TLB_SZ 9
#define ALPH_BEGIN 65

void setup();

int
main(int argc, char * argv[]) {
    setup();

    db_init();

    printf("S0 Running...\n");
    printf("%d arg(s): \n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]);
    }

    int res = 0;
    for (int i = 0; i < TLB_SZ; i++) {
        char * key = alloc_string(3);
        key[0] = 'i';
        key[1] = (char) (i + ALPH_BEGIN);
        key[2] = '\0';

        char * value = strdup(key);

        res = tlb_push(key, value);
        if (res) exit(res);
    }

    for (int i = 0; i < TLB_SZ; i++) {
        char * key = alloc_string(3);
        key[0] = 'i';
        key[1] = (char) (i + ALPH_BEGIN);
        key[2] = '\0';

        char * value = tlb_get(key);
        printf("%s\n", value);

        free(key);
    }

    for (int i = 0; i < TLB_SZ; i++) {
        char * key = alloc_string(3);
        key[0] = 'i';
        key[1] = (char) (i + ALPH_BEGIN);
        key[2] = '\0';

        char * value = strdup(key);
        value[1] = 'c';

        res = tlb_push(key, value);
        if (res) exit(res);
    }

    res = tlb_full_flush();
    if (res) exit(res);

    for (int i = 0; i < TLB_SZ; i++) {
        char * key = alloc_string(3);
        key[0] = 'i';
        key[1] = (char) (i + ALPH_BEGIN);
        key[2] = '\0';

        char * value = strdup(key);
        value[1] = 'e';

        res = tlb_push(key, value);
        if (res) exit(res);
    }

    res = tlb_full_flush();
    if (res) exit(res);

    for (int i = 0; i < TLB_SZ; i++) {
        char * key = alloc_string(3);
        key[0] = 'i';
        key[1] = (char) (TLB_SZ + i + ALPH_BEGIN);
        key[2] = '\0';

        char * value = strdup(key);
        value[1] = 'x';

        res = tlb_push(key, value);
        if (res) exit(res);
    }

    res = tlb_full_flush();
    if (res) exit(res);

    db_close();

    return 0;
}

void
setup()
{
    time_t t;
    srand((unsigned) time(&t));
    tlb_init(TLB_SZ);
}