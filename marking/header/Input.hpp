#pragma once
#include "Database.hpp"

namespace Database{
    
struct InputColumn{
    int id;
    int problem_id;
    std::string content;
};

class Input : public MariaDB<InputColumn>{
public:
    Input() : MariaDB<InputColumn>("input") 
    {
        
    };
    ~Input() {};

    void findProblemId(int problem_id);
};

void Input::findProblemId(int problem_id){
    sql::SQLString query("select * from " + tableName +
                        " where problem_id=" + std::to_string(problem_id));

    Database::ResultSetPtr res = find(query);
    
    if(res == nullptr) return;

    while(res->next()){
        table.push_back(
            {
                res->getInt(1),
                res->getInt(2),
                std::string(res->getString(3))
            }
        );
    }
}

}//namespace Database