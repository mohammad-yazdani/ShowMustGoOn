//
// Created by Mohammad Yazdani on 8/21/18.
//

#include <stdio.h>
#include <db.h>
#include <page.h>
#include <sqlite3.h>
#include <string.h>
#include <util/strutil.h>

static sqlite3 * db;

int callback(void * value, int argc, char **argv, char **azColName);

int
db_init()
{
    int rc = sqlite3_open("../data/data.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char * err_msg;
    char *sql = "DROP TABLE IF EXISTS pages;"
                "CREATE TABLE pages(key TEXT PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    return 0;
}

int
db_close()
{
    sqlite3_close(db);
    return 0;
}

int
db_insert(const char * key, const char * value)
{
    char * sql0 = "INSERT INTO pages VALUES ('", * sql1 = "', '", * sql2 = "');";

    size_t query_size = strlen(sql0) +
                        strlen(sql1) +
                        strlen(sql2) +
                        strlen(key) +
                        strlen(value);
    char * final_sql = alloc_string(query_size);

    strcat(final_sql, sql0);
    strcat(final_sql, key);
    strcat(final_sql, sql1);
    strcat(final_sql, value);
    strcat(final_sql, sql2);

    char * err_msg;
    int rc = sqlite3_exec(db, final_sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    free(final_sql);
    return 0;
}

int
db_update(const char * key, const char * value)
{
    char * sql0 = "UPDATE pages SET value = '", * sql1 = "' WHERE key = '", * sql2 = "';";

    size_t query_size = strlen(sql0) +
                        strlen(sql1) +
                        strlen(sql2) +
                        strlen(key) +
                        strlen(value);
    char * final_sql = alloc_string(query_size);

    strcat(final_sql, sql0);
    strcat(final_sql, value);
    strcat(final_sql, sql1);
    strcat(final_sql, key);
    strcat(final_sql, sql2);

    char * err_msg;
    int rc = sqlite3_exec(db, final_sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    free(final_sql);
    return 0;
}

char *
db_find(const char * key)
{
    char * value = NULL;

    char * sql0 = "SELECT value FROM pages WHERE key = '", * sql1 = "';";

    size_t query_size = strlen(sql0) + strlen(sql1) + strlen(key);
    char * final_sql = alloc_string(query_size);
    strcat(final_sql, sql0);
    strcat(final_sql, key);
    strcat(final_sql, sql1);

    char * err_msg;
    int rc = sqlite3_exec(db, final_sql, callback, &value, &err_msg);
    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return NULL;
    }
    return value;
}

int
callback(void * value, int argc, char **argv, char **azColName)
{
    (void)argc; (void)azColName;
    *((char **) value) = argv[0];
    return 0;
}