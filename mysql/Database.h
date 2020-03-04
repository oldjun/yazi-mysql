#pragma once

#include <string>
using namespace std;

#include <mysql/mysql.h>

namespace yazi {
namespace mysql {

class Database
{
    friend class Table;
    
public:
    Database();
    ~Database();

    bool connect(const string &host,
                 int port,
                 const string & username,
                 const string & password,
                 const string & database);

    void close();

private:
    MYSQL m_mysql;
};

}}
