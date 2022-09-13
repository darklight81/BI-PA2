#include <iostream>
#include "CQuestion.h"

void CQuestion::showQuestion(int number) const {
    std::cout << number << ", question: " << question << std::endl << std::endl;;
}

CQuestion::CQuestion() {
    question = "";

}
