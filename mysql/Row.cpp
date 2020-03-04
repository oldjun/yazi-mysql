#include <sstream>
using std::ostringstream;

#include <cstdlib>

#include "Row.h"
using namespace yazi::mysql;

Value::Value()
{

}

Value::Value(int data)
{
    ostringstream os;
    os << data;
    m_data = os.str();
}

Value::Value(double data)
{
    ostringstream os;
    os << data;
    m_data = os.str();
}

Value::Value(const char * data)
{
    m_data = data;
}

Value::Value(const string & data)
{
    m_data = data;
}

Value::Value(const Value & other)
{
    m_data = other.m_data;
}

Value::~Value()
{
    m_data.clear();
}

int Value::asInt() const
{
    return std::atoi(m_data.c_str());
}

double Value::asDouble() const
{
    return std::atof(m_data.c_str());
}

string Value::asString() const
{
    return m_data;
}

Value & Value::operator = (const Value& other)
{
    m_data = other.m_data;
    return *this;
}

Value & Value::operator = (int data)
{
    ostringstream os;
    os << data;
    m_data = os.str();
    return *this;
}

Value & Value::operator = (double data)
{
    ostringstream os;
    os << data;
    m_data = os.str();
    return *this;
}

Value & Value::operator = (const string & data)
{
    m_data = data;
    return *this;
}

Value & Value::operator = (const char * data)
{
    m_data = data;
    return *this;
}

bool Value::operator == (const Value & other)
{
    return (m_data == other.m_data);
}

bool Value::operator == (int data)
{
    Value other = data;
    return (*this == other);
}

bool Value::operator == (double data)
{
    Value other = data;
    return (*this == other);
}

bool Value::operator == (const string & data)
{
    Value other = data;
    return (*this == other);
}

bool Value::operator == (const char * data)
{
    Value other = data;
    return (*this == other);
}

bool Value::operator != (const Value & other)
{
    return !(*this == other);
}

bool Value::operator != (int data)
{
    Value other = data;
    return (*this != other);
}

bool Value::operator != (double data)
{
    Value other = data;
    return (*this != other);
}

bool Value::operator != (const string & data)
{
    Value other = data;
    return (*this != other);
}

bool Value::operator != (const char * data)
{
    Value other = data;
    return (*this != other);
}

Value::operator int()
{
    return std::atoi(m_data.c_str());
}

Value::operator double()
{
    return std::atof(m_data.c_str());
}

Value::operator string ()
{
    return m_data;
}

Value::operator string () const
{
    return m_data;
}

Row::Row()
{
}

Row::~Row()
{
}

Value & Row::operator [] (const char * key)
{
    string name = key;
    return (*this)[name];
}

Value & Row::operator [] (const string & key)
{
    return m_row[key];
}

const Value & Row::operator [] (const char * key) const
{
    const string tmp = key;
    return (*this)[tmp];
}

const Value & Row::operator [] (const string & key) const
{
    std::map<string, Value>::const_iterator it = m_row.find(key);
    if (it != m_row.end())
    {
        return it->second;
    }
    return null();
}

bool Row::empty() const
{
    return m_row.empty();
}

void Row::clear()
{
    m_row.clear();
}

Value const & Row::null()
{
    static const Value null;
    return null;
}
