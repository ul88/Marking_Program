#pragma once
#include "Database.hpp"

namespace Database{

// 해당 class에서 사용할 column 이름 지정 항상 'TableName'Column 형식으로 생성
struct OutputColumn{
    int id;
    int input_id;
    std::string content;
};

// 생성한 Column 구조체를 temaplate type으로 같이 넘김
class Output : public MariaDB<OutputColumn>{
public:
    Output() : MariaDB<OutputColumn>("output") {};
    ~Output() {};

    void findProblemId(int problem_id);
};

void Output::findProblemId(int problem_id){
    sql::SQLString query(
        "SELECT output.id, output.input_id, output.content"
        " FROM output"
        " INNER JOIN input"
        " ON input.id = output.input_id"
        " WHERE input.problem_id =" + std::to_string(problem_id)
    );

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