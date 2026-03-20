#include <iostream>
#include "httplib.h"
#include "sqlite3.h"

int main() {
    sqlite3* db;
    int rc = sqlite3_open("app.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    httplib::Server svr;

    svr.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("OK", "text/plain");
    });

    std::cout << "Server running on http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    sqlite3_close(db);
    return 0;
}
