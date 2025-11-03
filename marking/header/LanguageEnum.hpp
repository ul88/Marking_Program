#pragma once

namespace LanguageEnum{
    enum code{
        C=0,
        CPP,
        PYTHON,
        JAVA,
        SIZE
    };

    code getEnum(std::string str){
        if(str == "c" || str == "cpp") return code::CPP;
        else if(str == "py") return code::PYTHON;

        return code::SIZE;
    }

    std::string getString(code c){
        switch(c){
        case C:
            return "c";
        case CPP:
            return "cpp";
        case PYTHON:
            return "py";
        }
        return "None";
    }

} //namespace LanguageEnum