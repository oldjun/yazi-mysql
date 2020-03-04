#include <string>
using namespace std;

#include "Table.h"
using namespace yazi::mysql;

#include "Logger.h"
using namespace yazi::utility;

#include <sstream>
using std::ostringstream;

Table::Table(Database & db) : m_db(db), m_offset(0), m_limit(10)
{
}

Table::~Table()
{
}

Table & Table::select(const string & select)
{
    m_select = select;
    return *this;
}

Table & Table::from(const string & table)
{
    m_table = table;
    return *this;
}

Table & Table::join(const string & table, const string & on)
{
    m_join = table;
    m_on = on;
    return *this;
}

Table & Table::where(const string & where)
{
    m_where = where;
    return *this;
}

Table & Table::where(const string & field, const Value & value)
{
    eq(field, value);
    return *this;
}

Table & Table::where(const string & op, const string & field, const Value & value)
{
    if (op == "like")
    {
        like(field, value);
        return *this;
    }
    else if (op == "=")
    {
        eq(field, value);
        return *this;
    }
    else if (op == "!=")
    {
        ne(field, value);
        return *this;
    }
    else if (op == ">")
    {
        gt(field, value);
        return *this;
    }
    else if (op == ">=")
    {
        ge(field, value);
        return *this;
    }
    else if (op == "<")
    {
        lt(field, value);
        return *this;
    }
    else if (op == "<=")
    {
        le(field, value);
        return *this;
    }
    return *this;
}

Table & Table::eq(const string & field, const Value & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << "='" << (string)value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << "='" << (string)value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::ne(const string & field, const Value & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << "!='" << (string)value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << "!='" << (string)value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::gt(const string & field, const Value & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << ">'" << (string)value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << ">'" << (string)value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::ge(const string & field, const Value & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << ">='" << (string)value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << ">='" << (string)value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::lt(const string & field, const Value & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << "<'" << (string)value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << "<'" << (string)value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::le(const string & field, const Value & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << "<='" << (string)value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << "<='" << (string)value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::in(const string & field, const std::vector<Value> & values)
{
    ostringstream str;
    for (std::vector<Value>::const_iterator it = values.begin(); it != values.end(); it++)
    {
        if (it == values.begin())
        {
            str << "'" << (string)(*it) << "'";
        }
        else
        {
            str << ",'" << (string)(*it) << "'";
        }
    }
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << " IN (" << str.str() << ")";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << " IN (" << str.str() << ")";
        m_where = os.str();
    }
    return *this;
}

Table & Table::not_in(const string & field, const std::vector<Value> & values)
{
    ostringstream str;
    for (std::vector<Value>::const_iterator it = values.begin(); it != values.end(); it++)
    {
        if (it == values.begin())
        {
            str << "'" << (string)(*it) << "'";
        }
        else
        {
            str << ",'" << (string)(*it) << "'";
        }
    }
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << " NOT IN (" << str.str() << ")";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << " NOT IN (" << str.str() << ")";
        m_where = os.str();
    }
    return *this;
}

Table & Table::like(const string & field, const string & value)
{
    ostringstream os;
    if (m_where != "")
    {
        os << " AND " << escape_field(field) << " like '" << value << "'";
        m_where += os.str();
    }
    else
    {
        os << escape_field(field) << " like '" << value << "'";
        m_where = os.str();
    }
    return *this;
}

Table & Table::order(const string & order)
{
    m_order = order;
    return *this;
}

Table & Table::group(const string & group)
{
    m_group = group;
    return *this;
}

Table & Table::offset(int offset)
{
    m_offset = offset;
    return *this;
}

Table & Table::limit(int limit)
{
    m_limit = limit;
    return *this;
}

void Table::one(Row & row)
{
    m_limit = 1;
    string query = sql();
    debug("sql: %s", query.c_str());

    MYSQL mysql = m_db.m_mysql;
    if (mysql_query(&mysql, query.c_str()) != 0)
    {
        error("table one() errno: %d error: %s", mysql_errno(&mysql), mysql_error(&mysql));
        return;
    }

    MYSQL_RES * result = mysql_store_result(&mysql);
    int rs = mysql_num_rows(result);
	int fs = mysql_num_fields(result);
    debug("mysql_num_rows: %d, mysql_num_fields: %d", rs, fs);

    MYSQL_FIELD * fields = mysql_fetch_fields(result);
    MYSQL_ROW mysql_row = mysql_fetch_row(result);
    if (mysql_row == NULL)
    {
        mysql_free_result(result);
        return;
    }

    for (int i = 0; i < fs; i++)
    {
        row[fields[i].name] = mysql_row[i];
    }

    mysql_free_result(result);

    clear();
}

void Table::all(RowSet & rows)
{
    string query = sql();
    debug("sql: %s", query.c_str());

    MYSQL mysql = m_db.m_mysql;
    if (mysql_query(&mysql, query.c_str()) != 0)
    {
        error("table all() errno: %d error: %s", mysql_errno(&mysql), mysql_error(&mysql));
        return;
    }

    MYSQL_RES * result = mysql_store_result(&mysql);
    int rs = mysql_num_rows(result);
	int fs = mysql_num_fields(result);
    debug("mysql_num_rows: %d, mysql_num_fields: %d", rs, fs);

    MYSQL_FIELD * fields = mysql_fetch_fields(result);
    MYSQL_ROW mysql_row;
    while ((mysql_row = mysql_fetch_row(result)))
    {
        Row row;
        for (int i = 0; i < fs; i++)
        {
            row[fields[i].name] = mysql_row[i];
        }
        rows.push_back(row);
    }

    mysql_free_result(result);

    clear();
}

void Table::insert(const Row & row)
{
    insert_inner(row);

    clear();
}

void Table::insert(const RowSet & rows)
{
    for (RowSet::const_iterator it = rows.begin(); it != rows.end(); it++)
    {
        insert_inner(*it);
    }

    clear();
}

void Table::insert_inner(const Row & row)
{
    if (m_table == "")
    {
        return;
    }
    ostringstream field;
    ostringstream value;
    for (Row::const_iterator it = row.begin(); it != row.end(); it++)
    {
        if (it == row.begin())
        {
            field << escape_field(it->first);
            value << "'" << (string)it->second << "'";
        }
        else
        {
            field << "," << escape_field(it->first);
            value << ",'" << (string)it->second << "'";
        }
    }
    ostringstream os;
    os << "INSERT INTO " << escape_table(m_table) << "(" << field.str() << ")" << " VALUE(" << value.str() << ")";
    debug("sql: %s", os.str().c_str());
    
    MYSQL mysql = m_db.m_mysql;
    if (mysql_query(&mysql, os.str().c_str()) != 0)
    {
        error("table insert() errno: %d error: %s", mysql_errno(&mysql), mysql_error(&mysql));
    }
}

void Table::update(const Row & row)
{
    if (m_table == "")
    {
        return;
    }
    ostringstream set;
    for (Row::const_iterator it = row.begin(); it != row.end(); it++)
    {
        if (it == row.begin())
        {
            set << escape_field(it->first) << "='" << (string)it->second << "'";
        }
        else
        {
            set << "," << escape_field(it->first) << "='" << (string)it->second << "'";
        }
    }
    ostringstream os;
    if (m_where == "")
    {
        os << "UPDATE " << escape_table(m_table) << " SET " << set.str();
    }
    else
    {
        os << "UPDATE " << escape_table(m_table) << " SET " << set.str() << " WHERE " << m_where;
    }
    debug("sql: %s", os.str().c_str());
    
    MYSQL mysql = m_db.m_mysql;
    if (mysql_query(&mysql, os.str().c_str()) != 0)
    {
        error("table update() errno: %d error: %s", mysql_errno(&mysql), mysql_error(&mysql));
    }

    clear();
}

void Table::remove()
{
    if (m_table == "")
    {
        return;
    }
    ostringstream os;
    if (m_where == "")
    {
        os << "DELETE FROM " << escape_table(m_table) << "";
    }
    else
    {
        os << "DELETE FROM " << escape_table(m_table) << " WHERE " << m_where;
    }
    debug("sql: %s", os.str().c_str());
    
    MYSQL mysql = m_db.m_mysql;
    if (mysql_query(&mysql, os.str().c_str()) != 0)
    {
        error("table delete() errno: %d error: %s", mysql_errno(&mysql), mysql_error(&mysql));
    }

    clear();
}

string Table::sql()
{
    if (m_table == "")
    {
        return "";
    }

    ostringstream os;
    if (m_select == "")
    {
        os << "SELECT * ";
    }
    else
    {
        os << "SELECT " << m_select;
    }

    os << " FROM " << escape_table(m_table);

    if (m_join != "")
    {
        os << " INNER JOIN " << escape_table(m_join) << " ON " << m_on;
    }
    if (m_where != "")
    {
        os << " WHERE " << m_where;
    }

    if (m_order != "")
    {
        os << " ORDER BY " << m_order;
    }
    if (m_group != "")
    {
        os << " GROUP BY " << m_group;
    }
    os << " LIMIT " << m_offset << "," << m_limit;
    return os.str();
}

void Table::clear()
{
    m_select.clear();
    m_table.clear();
    m_where.clear();
    m_order.clear();
    m_group.clear();
    m_offset = 0;
    m_limit = 10;
}

string Table::escape_table(const string & table)
{
    ostringstream os;
    size_t pos = table.find(" as ");
    if (pos == string::npos)
    {
        os << "`" << table << "`";
        return os.str();
    }
    os << "`" << table.substr(0, pos) << "`" << table.substr(pos);
    return os.str();
}

string Table::escape_field(const string & field)
{
    ostringstream os;
    size_t pos = field.find(".");
    if (pos == string::npos)
    {
        os << "`" << field << "`";
        return os.str();
    }
    os << "`" << field.substr(0, pos) << "`" << field.substr(pos);
    return os.str();
}
