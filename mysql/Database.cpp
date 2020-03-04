#include "Database.h"
using namespace yazi::mysql;

#include "Logger.h"
using namespace yazi::utility;


Database::Database()
{
    mysql_init(&m_mysql);

    mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "utf8");
}

Database::~Database()
{
}

bool Database::connect(const string &host,
                       int port,
                       const string & username,
                       const string & password,
                       const string & database)
{
    if (mysql_real_connect(&m_mysql,
                           host.c_str(),
                           username.c_str(),
                           password.c_str(),
                           database.c_str(),
                           port, NULL, 0) == NULL)
    {
        error("mysql_real_connect errno:%d error:%s", mysql_errno(&m_mysql), mysql_error(&m_mysql));
        return false;
    }
    return true;
}

void Database::close()
{
    mysql_close(&m_mysql);
}
