#pragma once
#include<mariadb/conncpp.hpp>
#include<memory>
#include<vector>
#include<stdexcept>

namespace Database{
    
using ResultSetPtr = std::unique_ptr<sql::ResultSet>;

template <typename T>
class MariaDB{
public:
    using Column = T;
    MariaDB(const char* tableName);
    ~MariaDB();
    
    ResultSetPtr find(const sql::SQLString& query);
    const std::vector<Column>& getTable() const {return table;}

protected:
    std::string tableName;
    std::vector<Column> table;

private:
    std::unique_ptr<sql::Connection> conn;
    std::unique_ptr<sql::Statement> stmnt;
};

template <typename T>
MariaDB<T>::MariaDB(const char* tableName) :
    conn(
        sql::DriverManager::getConnection(
                sql::SQLString("jdbc:mariadb://127.0.0.1:3306/test"), 
                sql::SQLString("root"),
                sql::SQLString("1234")
            )
    ),
    stmnt(conn->createStatement()),
    tableName(tableName)
{
}

template <typename T>
MariaDB<T>::~MariaDB(){
    conn->close();
}

template <typename T>
ResultSetPtr MariaDB<T>::find(const sql::SQLString& query){
    try {
        table.clear();
        return ResultSetPtr(stmnt->executeQuery(query));
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return nullptr;
}

} //namespace Database