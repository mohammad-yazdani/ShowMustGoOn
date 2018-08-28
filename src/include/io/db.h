//
// Created by Mohammad Yazdani on 8/21/18.
//

#ifndef S0_DB_H
#define S0_DB_H
#include <sqlite3.h>

sqlite3 * db_init();
int db_insert(char * key, char * value);
char * db_find(char * key);

#endif //S0_DB_H
