#include <iostream>
#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./header/ProblemInput.hpp"
#include "./header/LanguageEnum.hpp"

void changeProcess(LanguageEnum::code languageCode){
    switch(languageCode){
    case LanguageEnum::code::C: 
    case LanguageEnum::code::CPP:
        execl("/home/hanul/coding/marking_program/resource/a.out", "/home/hanul/coding/marking_program/resource/a.out", NULL);
        break;
    case LanguageEnum::code::PYTHON:
        execl("/usr/bin/python3","python3","/home/hanul/coding/marking_program/resource/main.py",NULL); // 파이썬
        break;
    }
}

// void change_file_descriptor(const std::string& path,int number){
//     std::string input_file_path = "input_" + std::to_string(number) + ".txt";
//     std::string output_file_path = "output_" + std::to_string(number) + ".txt";
    
//     // std::println("in_path: {}\nout_path: {}",input_file_path,output_file_path);
//     std::cout<<"in_puth : "<<input_file_path<<std::endl
//             <<"out_path : "<<output_file_path<<std::endl; 

//     int input_fd = open(input_file_path.c_str(), O_RDONLY);
//     int output_fd = open(output_file_path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);

//     dup2(input_fd, STDIN_FILENO);
//     dup2(output_fd, STDOUT_FILENO);

//     close(input_fd);
//     close(output_fd);

//     change_process(path);
// }

void getPipe(int number, int fd[2]){
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    std::string output_file_path = "../output/output_" + std::to_string(number) + ".txt";
    int output_fd = open(output_file_path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
}

void startFork(int number, std::string content, LanguageEnum::code languageCode){
    int fd[2];
    if(pipe(fd) == -1) {
        std::cout<<"pipe error";
    }
    
    write(fd[1], content.c_str(), content.length());
    close(fd[1]);
    
    int pid = fork();

    if(pid == 0){
        // change_file_descriptor(path,i);
        getPipe(number, fd);
        changeProcess(languageCode);
    }else if(pid < 0){
        std::cerr<<"fork fail";
        exit(1);
    }
}



// void marking(ProblemInput& problemInput){
    
// }

int main(int argc, char* argv[])
{
    if(argc <= 1){
        std::cout<<"[1] [2]"<<std::endl;
        std::cout<<"[1] : 실행하고자 하는 언어 확장자"<<std::endl;
        std::cout<<"[2] : 문제 번호"<<std::endl;
        std::cout<<"e.g., c 1"<<std::endl;
        exit(1);
    }

    std::string problem_id;
    LanguageEnum::code languageCode;

    if(argc >= 2){
        languageCode = LanguageEnum::getEnum(std::string(argv[1]));
    }
    if(argc >= 3){
        problem_id = argv[2];
    }

    std::map<std::string, std::string> m;
    m.insert({"table_name", "input"});
    m.insert({"problem_id", problem_id});
    Database::ProblemInput d;
    d.findProblemId(m);
    
    for(auto& [key, value] : d.getTable()){
        startFork(key, std::string(value), languageCode);
        wait(NULL);
    }

    // marking();
    
    return 0;
}