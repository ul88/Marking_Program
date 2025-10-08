#include <iostream>
#include<map>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./header/ProblemInput.hpp"

enum Language_code{
    C=0,
    CPP,
    PYTHON,
    JAVA,
    SIZE
};


void change_process(const std::string& path){
    enum Language_code code = C;
    switch(code){
    case C:
        execl(path.c_str(), path.c_str(), NULL);    
        break;
    case PYTHON:
        execl("/usr/bin/python3","python3",path.c_str(),NULL); // 파이썬
        break;
    }
}

void change_file_descriptor(const std::string& path,int number){
    std::string input_file_path = "input_" + std::to_string(number) + ".txt";
    std::string output_file_path = "output_" + std::to_string(number) + ".txt";
    
    // std::println("in_path: {}\nout_path: {}",input_file_path,output_file_path);
    std::cout<<"in_puth : "<<input_file_path<<std::endl
            <<"out_path : "<<output_file_path<<std::endl; 

    int input_fd = open(input_file_path.c_str(), O_RDONLY);
    int output_fd = open(output_file_path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);

    dup2(input_fd, STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);

    close(input_fd);
    close(output_fd);

    change_process(path);
}

void getPipe(const std::string& path,int number, int fd[2]){
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    std::string output_file_path = "../output/output_" + std::to_string(number) + ".txt";
    int output_fd = open(output_file_path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
    change_process(path);
}

void startFork(const std::string& path, int number, std::string content){
    int fd[2];
    if(pipe(fd) == -1) {
        std::cout<<"pipe error";
    }
    
    write(fd[1], content.c_str(), content.length());
    close(fd[1]);
    int pid = fork();
    if(pid == 0){
        // change_file_descriptor(path,i);
        getPipe(path, number, fd);
    }else if(pid < 0){
        // std::println("fork fail");
        std::cout<<"fork fail";
        exit(1);
    }
}



// void marking(ProblemInput& problemInput){
    
// }

int main(int argc, char* argv[])
{
    if(argc <= 1){
        /*
        std::println("[1] [2]");
        std::println("[1] : 실행하고자 하는 파일 경로");
        std::println("[2] : input 데이터의 개수");
        std::println("e.g, ./test.out 5");
        */
        std::cout<<"[1] [2]"<<std::endl;
        std::cout<<"[1] : 실행하고자 하는 파일 경로"<<std::endl;
        std::cout<<"[2] : 문제 번호"<<std::endl;
        std::cout<<"e.g., ./test.out 1"<<std::endl;
        exit(1);
    }

    std::string path;
    int problem_id;
    
    if(argc >= 2){
        path = argv[1];
    }
    if(argc >= 3){
        problem_id = atoi(argv[2]);
    }

    std::map<std::string, std::string> m;
    m.insert({"table_name", "input"});
    m.insert({"problem_id", "1"});
    Database::ProblemInput d;
    d.findProblemId(m);
    
    for(auto& [key, value] : d.getTable()){
        startFork(path, key, std::string(value));
        wait(NULL);
    }

    // marking();
    
    return 0;
}