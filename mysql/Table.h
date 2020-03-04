#pragma once

#include <string>
using namespace std;

#include <vector>

#include "Row.h"
#include "Database.h"

namespace yazi {
namespace mysql {

class Table
{
public:
    Table(Database & db);
    ~Table();

    Table & select(const string & select);
    Table & from(const string & table);
    Table & join(const string & table, const string & on);
    Table & where(const string & where);
    Table & where(const string & field, const Value & value);
    Table & where(const string & op, const string & field, const Value & value);
    Table & eq(const string & field, const Value & value);
    Table & ne(const string & field, const Value & value);
    Table & gt(const string & field, const Value & value);
    Table & ge(const string & field, const Value & value);
    Table & lt(const string & field, const Value & value);
    Table & le(const string & field, const Value & value);
    Table & in(const string & field, const std::vector<Value> & values);
    Table & not_in(const string & field, const std::vector<Value> & values);
    Table & like(const string & field, const string & value);
    Table & order(const string & order);
    Table & group(const string & group);
    Table & offset(int offset);
    Table & limit(int limit);

    typedef std::vector<Row> RowSet;
    void one(Row & row);
    void all(RowSet & rows);

    // insert
    void insert(const Row & row);

    // insert batch
    void insert(const RowSet & rows);

    // update
    void update(const Row & row);

    // delete
    void remove();

private:
    string sql();
    void clear();
    void insert_inner(const Row & row);
    string escape_table(const string & table);
    string escape_field(const string & field);

private:
    Database & m_db;
    string m_select;
    string m_table;
    string m_where;
    string m_order;
    string m_group;
    string m_join;
    string m_on;
    int m_offset;
    int m_limit;
};

}}
