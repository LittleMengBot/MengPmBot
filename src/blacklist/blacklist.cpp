#include <iostream>
#include "blacklist.h"
#include "SQLiteCpp/SQLiteCpp.h"

BlackListDb init_db() {
    BlackListDb db("data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    std::cout << "SQLite database file '" << db.get_filename() << "' opened successfully"<<std::endl;
    db.create_table();
    return db;
}
