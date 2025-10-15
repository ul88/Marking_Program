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

} //namespace LanguageEnum