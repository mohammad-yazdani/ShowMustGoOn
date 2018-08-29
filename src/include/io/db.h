//
// Created by Mohammad Yazdani on 8/21/18.
//

#ifndef S0_DB_H
#define S0_DB_H
#include <sqlite3.h>

int db_init();
int db_close();
int db_insert(const char * key, const char * value);
int db_update(const char * key, const char * value);
char * db_find(const char * key);

#endif //S0_DB_H
