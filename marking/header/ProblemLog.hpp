#pragma once
#include "./Database.hpp"

namespace Database{

struct ProblemLogColumn{
    int id;
    std::string userId;
    int problemId;
    int incorrectInputId;
    std::string ext;
    std::string createAtTime;
};

class ProblemLog : MariaDB<ProblemLogColumn>{
public:
    ProblemLog() : MariaDB<ProblemLogColumn>("problem_log") {};
    ~ProblemLog() {};
    
    void insert(ProblemLog::Column column);
};

void ProblemLog::insert(ProblemLog::Column column){
    PreparedStatementPtr stmnt = getInsertStmnt("INSERT INTO " + tableName + "(user_id, problem_id, incorrect_input_id, ext) VALUES (?, ?, ?)");

    try{
        stmnt->setString(1, column.userId);
        stmnt->setInt(2, column.problemId);
        if(column.incorrectInputId != 0){
            stmnt->setInt(3, column.incorrectInputId);
        }else{
            stmnt->setNull(3, sql::DataType::INTEGER);
        }
        stmnt->setString(4, column.ext);
        stmnt->executeUpdate();
    }catch(sql::SQLException &e){
        std::cerr << "Error adding contact to database: " << e.what() << std::endl;
    }   
}

} // namespace Database
