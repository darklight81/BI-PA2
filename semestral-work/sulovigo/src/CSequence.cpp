#include <iostream>
#include <algorithm>
#include <random>
#include "CSequence.h"
#include "CInterface.h"

CSequence::CSequence(std::string question, std::string a, std::string b, std::string c) {
    this->question = question;
    answers.push_back(a);
    answers.push_back(b);
    answers.push_back(c);
    //shuffle to set a,b and c randomly
    shuffledAnswers = answers;
    std::shuffle(shuffledAnswers.begin(), shuffledAnswers.end(), std::mt19937(std::random_device()()));
}

void CSequence::showQuestion(int number) const{
    std::cout << number << ", sequence question: " << question << std::endl;
    std::cout << "   a) " << shuffledAnswers[0] << std::endl;
    std::cout << "   b) " << shuffledAnswers[1] << std::endl;
    std::cout << "   c) " << shuffledAnswers[2] << std::endl << std::endl;
}

bool CSequence::checkAnswer() const{
    std::vector<int> keys;
    int key;
    for (int j = 0; j < 3; ++j) {

        key = getchar();
        if (key == '\n')
            key = getchar();
        getchar();

        if (key != 'a' && key != 'b' && key != 'c') {
            CInterface::wrongInput();
            --j;
        } else
            keys.push_back(key);
    }
    std::vector<std::string> input;

    for (int i = 0; i < 3; ++i) {
        if (keys[i] == 'a')
            input.push_back(shuffledAnswers[0]);
        else if (keys[i] == 'b')
            input.push_back(shuffledAnswers[1]);
        else if (keys[i] == 'c')
            input.push_back(shuffledAnswers[2]);
        else
            return false;
    }
    return input == answers;

}

std::string CSequence::getAnswer() const{
    return answers[0] + " " + answers[1] + " " + answers[2];
}

CQuestion *CSequence::clone() const {
    return new CSequence(*this);
}

