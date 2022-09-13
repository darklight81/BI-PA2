#include <iostream>
#include <algorithm>
#include <random>
#include "CMultipleChoice.h"
#include "CInterface.h"


CMultipleChoice::CMultipleChoice(std::string question, std::string a, std::string b, std::string c) {
    this->question = question;
    answers.push_back(a);
    answers.push_back(b);
    answers.push_back(c);
    answer = a;
    //shuffles the answers;
    std::shuffle(answers.begin(), answers.end(), std::mt19937(std::random_device()()));

}

// Prints out the question with all possibilities
void CMultipleChoice::showQuestion(int number) const {
    std::cout << number << ", Multiple choice question: " << question << std::endl;
    std::cout << "   a) " << answers[0] << std::endl;
    std::cout << "   b) " << answers[1] << std::endl;
    std::cout << "   c) " << answers[2] << std::endl << std::endl;
}

bool CMultipleChoice::checkAnswer() const {
    int key;
    while (true) {
        key = std::getchar();
        if (key == '\n') // means the getchar above has eaten the newline from previous question
            key = std::getchar();
        getchar(); // for newline
        if (key == 'a' || key == 'b' || key == 'c')
            break;
        else
            CInterface::wrongInput();
    }
    switch (key) {
        case 'a':
            return answers[0] == answer;
        case 'b':
            return answers[1] == answer;
        case 'c':
            return answers[2] == answer;
        default:
            return false;
    }
}

std::string CMultipleChoice::getAnswer() const {
    return answer;
}
CQuestion *CMultipleChoice::clone() const {
    return new CMultipleChoice(*this);
}