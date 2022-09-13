#include <iostream>
#include "COpenText.h"


COpenText::COpenText(std::string question, std::string answer, int type) {
    this->question = question;
    this->answer = answer;
    this->type = type;
}

bool COpenText::checkAnswer()const {
    std::string key;
    std::getline(std::cin, key);

    switch (type) {
        case 0:
            return key == answer;
        case 1:
            for (unsigned i = 0; i < answers.size(); ++i) {
                if (key == answers[i])
                    return true;
            }
            return false;
        case 2:
            if (key.find(answer, 0) == std::string::npos)
                return false;
            return true;
    }
    return false;
}

COpenText::COpenText(std::string question, std::vector<std::string> answers) {
    this->question = question;
    this->answers = answers;
    this->type = 1;
}

std::string COpenText::getAnswer()const {
    std::string returnAnswer = "";
    if (type == 1) {
        for (unsigned i = 0; i < answers.size(); ++i)
            returnAnswer += (answers.at(i) + " ");
        return returnAnswer;
    }
    return answer;
}

CQuestion *COpenText::clone() const {
    return new COpenText(*this);
}


