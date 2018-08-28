//
// Created by Mohammad Yazdani on 8/21/18.
//

#include <stdio.h>
#include <db.h>
#include <page.h>
#include <sqlite3.h>

sqlite3 *
db_init()
{
    sqlite3 *db;

    int rc = sqlite3_open("../data/data.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return NULL;
    }
    return db;
}

int
db_insert(char * key, page * p)
{
    return 0;
}

char *
db_find(char * key)
{
    return 0;
}