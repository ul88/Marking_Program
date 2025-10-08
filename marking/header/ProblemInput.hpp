#include "Database.hpp"

namespace Database{

class ProblemInput : private Database::MariaDB{
public:
    ProblemInput() {};
    ~ProblemInput() {};

    void findProblemId(std::map<std::string, std::string> columns);

    const std::map<int, sql::SQLString>& getTable() const {return table;}
private:
    std::map<int, sql::SQLString> table;
};

void ProblemInput::findProblemId(std::map<std::string, std::string> columns){
    sql::SQLString query("select * from " + columns["table_name"] +
                        " where problem_id=" + columns["problem_id"]);

    Database::ResultSetPtr res = find(query);
    
    if(res == nullptr) return;

    while(res->next()){
        std::cout<<res->getInt(1)<<" "<<res->getString(3)<<std::endl;
        table[res->getInt(1)] = res->getString(3);
    }
}

}//namespace Database