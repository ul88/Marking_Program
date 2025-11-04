#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./header/Input.hpp"
#include "./header/LanguageEnum.hpp"
#include "./header/Output.hpp"
#include "./header/ProblemLog.hpp"

void changeProcess(LanguageEnum::code languageCode){
    switch(languageCode){
    case LanguageEnum::code::C: 
    case LanguageEnum::code::CPP:
        execl("../resource/a.out", "../resource/a.out", NULL);
        break;
    case LanguageEnum::code::PYTHON:
        execl("/usr/bin/python3","python3","../resource/main.py",NULL); // 파이썬
        break;
    }
}

void getPipe(int number, int fd[2]){
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    std::string output_file_path = "../output/output_" + std::to_string(number) + ".txt";
    int output_fd = open(output_file_path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
}

int startFork(int number, std::string content, LanguageEnum::code languageCode){
    int fd[2];
    if(pipe(fd) == -1) {
        std::cout<<"pipe error";
    }
    
    write(fd[1], content.c_str(), content.length());
    close(fd[1]);
    
    int pid = fork();

    if(pid == 0){
        getPipe(number, fd);
        changeProcess(languageCode);
    }else if(pid < 0){
        std::cerr<<"fork fail";
        exit(1);
    }

    return pid;
}

void marking(int problem_id, const std::string& userId, LanguageEnum::code languageCode){
    Database::Output output;
    Database::ProblemLog problemLog;

    output.findProblemId(problem_id);

    for(const Database::Output::Column& col : output.getTable()){
        std::ifstream in("../output/output_" + std::to_string(col.id) + ".txt");
        if(in.is_open()){
            in.seekg(0, std::ios::end);
            int size = in.tellg();
            std::string data("", size);
            in.seekg(0, std::ios::beg);

            in.read(&data[0], size);

            if(col.content != data){
                std::cout<<"now_output: "<< data<<"\n";
                std::cout<<"real output: "<< col.content<<"\n";
                problemLog.insert({0,
                    userId,
                    problem_id,
                    col.id,
                    data,
                    LanguageEnum::getString(languageCode),
                    ""});
                return;   
            }
        }
    }

    std::cout<<"problem id( " << problem_id << " )  correct!" <<std::endl;
    problemLog.insert({0,
        userId,
        problem_id,
        0,
        "",
        LanguageEnum::getString(languageCode),
        ""});
}

int main(int argc, char* argv[])
{
    if(argc <= 3){
        std::cout<<"[1] [2] [3]"<<std::endl;
        std::cout<<"[1] : 실행하고자 하는 언어 확장자"<<std::endl;
        std::cout<<"[2] : 문제 번호"<<std::endl;
        std::cout<<"[3] : 사용자 이름"<<std::endl;
        std::cout<<"e.g., c 1 ul88"<<std::endl;
        exit(1);
    }

    int problem_id;
    LanguageEnum::code languageCode;
    std::string userId;
    Database::Input input;

    if(argc >= 4){
        languageCode = LanguageEnum::getEnum(std::string(argv[1]));
        problem_id = atoi(argv[2]);
        userId = argv[3];
    }

    input.findProblemId(problem_id);

    int pid;

    for(const Database::Input::Column col : input.getTable()){
        pid = startFork(col.id, col.content, languageCode);
        wait(NULL);
    }

    if(pid != 0) marking(problem_id, userId, languageCode);
    
    return 0;
}