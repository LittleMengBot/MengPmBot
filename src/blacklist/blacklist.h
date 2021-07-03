#ifndef PMBOT_BLACKLIST_H
#define PMBOT_BLACKLIST_H

#include <iostream>
#include "SQLiteCpp/SQLiteCpp.h"
class BlackListDb:SQLite::Database {
    using SQLite::Database::Database;

public:
    void create_table() {
        if (this->tableExists("blacklist")) {
            return;
        }
        this->exec("CREATE TABLE blacklist (user_id text PRIMARY KEY, name text)");
    }

    auto get_filename() {
        return this->getFilename().c_str();
    }

    void add_blacklist(int64_t &user_id, const std::string& user_full_name) {
        SQLite::Statement query(*this, "INSERT INTO blacklist VALUES (?, ?)");
        query.bind(1, user_id);
        query.bind(2, user_full_name);
        query.exec();
    }

    bool check_blacklist(int64_t &user_id) {
        SQLite::Statement query(*this, "SELECT * FROM blacklist WHERE user_id = ?");
        query.bind(1, user_id);
        if (query.executeStep()) {
            return true;
        } else {
            return false;
        }
    }

    std::string get_blacklist() {
        SQLite::Statement query(*this, "SELECT * FROM blacklist");
        std::string result("BlackList:\n");
        while (query.executeStep()) {
            result.append(query.getColumn(0).getString() + "\t" + query.getColumn(1).getString() + "\n");
        }
        return result;
    }

    void delete_blacklist(int64_t &user_id) {
        SQLite::Statement query(*this, "DELETE FROM blacklist WHERE user_id = ?");
        query.bind(1, user_id);
        query.exec();
    }

};

BlackListDb init_db();
#endif //PMBOT_BLACKLIST_H
