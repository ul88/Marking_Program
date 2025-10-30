#pragma once
#include "./Database.hpp"

namespace Database{

struct ProblemLogColumn{
    int id;
    std::string userId;
    int problemId;
    int incorrectInputId;
    std::string createAtTime;
};

class ProblemLog : MariaDB<ProblemLogColumn>{
public:
    ProblemLog() : MariaDB<ProblemLogColumn>("problem_log") {};
    ~ProblemLog() {};
    
    void insertData(ProblemLog::Column column);
};

void ProblemLog::insertData(ProblemLog::Column column){
    sql::SQLString query;
    if(column.incorrectInputId == 0){
        query = "INSERT INTO " + tableName + "(user_id, problem_id) VALUE (\""+column.userId+"\","+std::to_string(column.problemId)+")";
    }else{
        query = "INSERT INTO " + tableName + "(user_id, problem_id, incorrect_input_id) VALUE (\""+column.userId+"\","+std::to_string(column.problemId)+","+std::to_string(column.incorrectInputId)+")";
    }
    
    insert(query);
}

} // namespace Database