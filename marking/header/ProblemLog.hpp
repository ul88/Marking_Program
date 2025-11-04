#pragma once
#include "./Database.hpp"

namespace Database{

struct ProblemLogColumn{
    int id;
    std::string userId;
    int problemId;
    int incorrectOutputId;
    std::string incorrectOutputContent;
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
    PreparedStatementPtr stmnt = getInsertStmnt("INSERT INTO " + tableName + "(user_id, problem_id, incorrect_output_id, incorrect_output_content, ext) VALUES (?, ?, ?, ?, ?)");

    try{
        stmnt->setString(1, column.userId);
        stmnt->setInt(2, column.problemId);
        if(column.incorrectOutputId != 0){
            stmnt->setInt(3, column.incorrectOutputId);
            stmnt->setString(4, column.incorrectOutputContent);
        }else{
            stmnt->setNull(3, sql::DataType::SQLNULL);
            stmnt->setNull(4, sql::DataType::SQLNULL);
        }
        stmnt->setString(5, column.ext);
        stmnt->executeUpdate();
    }catch(sql::SQLException &e){
        std::cerr << "Error adding contact to database: " << e.what() << std::endl;
    }   
}

} // namespace Database
