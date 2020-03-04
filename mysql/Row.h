#pragma once
#include <string>
using namespace std;

#include <map>
#include <vector>

namespace yazi {
namespace mysql {

class Value
{
public:
    Value();
    Value(int data);
    Value(double data);
    Value(const char * data);
    Value(const string & data);
    Value(const Value & other);
    ~Value();

    int asInt() const;
    double asDouble() const;
    string asString() const;

    Value & operator = (const Value & other);
    Value & operator = (int data);
    Value & operator = (double data);
    Value & operator = (const string & data);
    Value & operator = (const char * data);

    bool operator == (const Value & other);
    bool operator == (int data);
    bool operator == (double data);
    bool operator == (const string & data);
    bool operator == (const char * data);

    bool operator != (const Value & other);
    bool operator != (int data);
    bool operator != (double data);
    bool operator != (const string & data);
    bool operator != (const char * data);

    operator int();
    operator double();
    operator string();
    operator string() const;

private:
    string m_data;
};

class Row
{
public:
    Row();
    ~Row();

    // Access an object value by name, create a null member if it does not exist.
    Value & operator [] (const char * key);
    // Access an object value by name, returns null if there is no member with that name.
    const Value & operator [] (const char * key) const;

    // Access an object value by name, create a null member if it does not exist.
    Value & operator [] (const string & key);
    // Access an object value by name, returns null if there is no member with that name.
    const Value & operator [] (const string & key) const;

    bool empty() const;
    void clear();

    // static
    static Value const & null();

    
    typedef std::map<string, Value>::iterator iterator;
    typedef std::map<string, Value>::const_iterator const_iterator;

    iterator begin()
    {
        return m_row.begin();
    }

    iterator end()
    {
        return m_row.end();
    }

    const_iterator begin() const
    {
        return m_row.begin();
    }

    const_iterator end() const
    {
        return m_row.end();
    }

private:
    std::map<string, Value> m_row;
};

typedef std::vector<Row> RowSet;

}}
