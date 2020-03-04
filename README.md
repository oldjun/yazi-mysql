# yazi-mysql
a c++ interface to mysql

|Author|junping|
|---|---|
|E-mail|oldjun@sina.com|
|Wechat|chenjunping1024|

## Open a connection to mysql server
```c++
#include <iostream>
#include <string>
using namespace std;

#include "Database.h"
using namespace yazi::mysql;

int main()
{
    // open a connection
    Database db;
    if (db.connect("127.0.0.1", 0, "username", "password", "dbname"))
    {
        std::cout << "ok......" << std::endl;
    }
    
    // select/insert/update/delete ...
    
    // close the connection
    db.close();
    
    return 0;
}
```
## The user & fans table
```sql
create table `user`
(
    `id` int unsigned not null auto_increment,
    `name` varchar(16) not null default '',
    `age` int unsigned not null default 0,
    `time` timestamp not null default current_timestamp,
    primary key (`id`),
    key `idx_name` (`name`),
    key `idx_time` (`time`)
) ENGINE=InnoaDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

create table `fans`
(
    `id` int unsigned not null auto_increment,
    `uid` int unsigned not null default 0,
    `fid` int unsigned not null default 0,
    `time` timestamp not null default current_timestamp,
    primary key (`id`),
    key `idx_uid` (`uid`),
    key `idx_time` (`time`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
```

## Perform Query：select one record from table
```c++
#include "Database.h"
#include "Table.h"
#include "Row.h"
using namespace yazi::mysql;

int main()
{
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
}
```
## Perform Query：select some record from table
```c++

int main()
{
    Table table(db);

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
}
```
## Perform Query：join table
```c++

int main()
{
    Table table(db);

    // join table
    RowSet rows;
    table.from("fans as f").join("user as u", "f.uid=u.id").where("u.id", 1).all(rows);
    for (RowSet::iterator it = rows.begin(); it != rows.end(); it++)
    {
        int uid = (*it)["uid"];
        int fid = (*it)["fid"];
        std::cout << "uid=" << uid << ", fid=" << fid << std::endl;
    }
}
```
## Perform Insert
```c++
int main()
{
    Table table(db);

    // prepare data
    Row row;
    row["name"] = "ping";
    row["age"] = 30;
    
    // insert
    table.from("user").insert(row);
}
```

## Perform Insert: batch insert
```c++
int main()
{
    Table table(db);

    // prepare data
    Row row;
    RowSet rows;
    
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
}
```

## Perform Update
```c++
int main()
{
    Table table(db);

    // prepare data
    Row row;
    row["age"] = 30;
    row["name"] = "ping";
    table.from("user").where("id", 1).update(row);
}
```

## Perform Delete
```c++
int main()
{
    Table table(db);

    table.from("user").where("id", 1).remove();
}
```
## Compile & Run the project
download the source code, cd into the yazi-mysql project working directory, run command make && ./main 
```bash
cd ./yazi-mysql
make
./main
```
> Note: you should install mysql client before compiling this project. In centos 7, the mysql include path is /usr/include/mysql, the mysql library path is /usr/lib64/mysql, for more details see the Makefile, if your machine's include path or library path is different, please adjust it by modifying the Makefile.
