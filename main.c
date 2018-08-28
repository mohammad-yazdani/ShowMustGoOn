#include <stdio.h>

int
main(int argc, char * argv[]) {
    printf("S0 Running...\n");
    printf("%d arg(s): \n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]);
    }
    return 0;
}