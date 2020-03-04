#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "System.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "Database.h"
#include "Table.h"
#include "Row.h"
using namespace yazi::mysql;

int main()
{
    // system init
    Singleton<System>::instance()->init();

    Database db;
    if (db.connect("127.0.0.1", 0, "root", "6zrU5fmDm06BNdJM", "test"))
    {
        std::cout << "ok......" << std::endl;
    }

    Table table(db);

    // select one record
    Row row;
    table.from("user").where("id", 1).one(row);
    if (row.empty())
    {
        std::cout << "query result is empty" << std::endl;
    }
    else
    {
        string name = row["name"];
        int age = row["age"];
        std::cout << "name=" << name << " age=" << age << std::endl;
    }

    std::vector<Value> values;
    values.push_back(1);
    values.push_back(3);

    // select all record
    RowSet rows;
    table.select("id,name,age,time").from("user").where(">=", "age", 30).order("id asc").all(rows);
    for (RowSet::iterator it = rows.begin(); it != rows.end(); it++)
    {
        int id = (*it)["id"];
        string name = (*it)["name"];
        int age = (*it)["age"];
        string time = (*it)["time"];
        std::cout << "id=" << id << ", name=" << name << ", age=" << age << ", time=" << time << std::endl;
    }

    rows.clear();

    table.from("fans as f").join("user as u", "f.uid=u.id").where("u.id", 1).all(rows);
    for (RowSet::iterator it = rows.begin(); it != rows.end(); it++)
    {
        int uid = (*it)["uid"];
        int fid = (*it)["fid"];
        std::cout << "uid=" << uid << ", fid=" << fid << std::endl;
    }

    // insert
    {
        Row row;
        row["name"] = "ping";
        row["age"] = 30;
        table.from("user").insert(row);
    }

    /*
    rows.clear();

    row.clear();
    row["name"] = "ping";
    row["age"] = 30;
    rows.push_back(row);

    row["name"] = "jack";
    row["age"] = 32;
    rows.push_back(row);

    row["name"] = "lucy";
    row["age"] = 24;
    rows.push_back(row);
    
    row["name"] = "lily";
    row["age"] = 22;
    rows.push_back(row);

    // batch insert
    table.from("user").insert(rows);
    */

    // update
    row.clear();
    row["age"] = 30;
    row["name"] = "ping";
    table.from("user").where("id", 1).update(row);

    // delete
    table.from("user").where("id", 1).remove();

    db.close();
    return 0;
}
