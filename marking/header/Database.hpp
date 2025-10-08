#include<mariadb/conncpp.hpp>
#include<memory>
#include<map>

namespace Database{
    
using ResultSetPtr = std::unique_ptr<sql::ResultSet>;
class MariaDB{
public:
    MariaDB();
    ~MariaDB();
    
    ResultSetPtr find(const sql::SQLString& query);
private:
    std::unique_ptr<sql::Connection> conn;
    std::unique_ptr<sql::Statement> stmnt;
};

MariaDB::MariaDB() :
    conn(
        sql::DriverManager::getConnection(
                sql::SQLString("jdbc:mariadb://127.0.0.1:3306/test"), 
                sql::SQLString("root"),
                sql::SQLString("1234")
            )
    ),
    stmnt(conn->createStatement())
{

}

MariaDB::~MariaDB(){
    conn->close();
}

ResultSetPtr MariaDB::find(const sql::SQLString& query){
    try {
        return ResultSetPtr(stmnt->executeQuery(query));
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    }
    return nullptr;
}

} //namespace Database