#include <iostream>
#include "CInterface.h"

void CInterface::refresh() {
    for (int i = 0; i < 50; ++i) {
        std::cout << std::endl;
    }

}

void CInterface::chooseUser() {
    std::cout << "Choose mode\n"
              << "************\n"
              << "0) Fill quiz\n"
              << "1) Create quiz\n"
              << "************\n";
}

void CInterface::chooseQuestion() {
    std::cout << "Choose question type\n"
              << "************\n"
              << "0) Open text\n"
              << "1) Multiple choice\n"
              << "2) Sequence\n"
              << "3) End the quiz\n"
              << "************\n";
}

void CInterface::wrongInput() {
    std::cout << "Wrong input, try again." << std::endl;
}

void CInterface::createFilename() {
    std::cout << "Please write the name of the file:" << std::endl;
}

void CInterface::error() {
    std::cout << "Something went wrong. Ending the program." << std::endl;
}

void CInterface::loadFilename() {
    std::cout << "Please write the name of the quiz you want to fill." << std::endl;
}

void CInterface::writeQuestion() {
    std::cout << "Please write your question: ";
}

void CInterface::writeOpenText() {
    std::cout << "Please write the correct answer: ";
}

void CInterface::writeMultipleChoice() {
    std::cout << "Please write 3 options, the correct one first: " << std::endl;
}

void CInterface::writeSequence() {
    std::cout << "Please write 3 answers correctly ordered: " << std::endl;

}

void CInterface::wrongFile() {
    std::cout << "File is formatted incorrectly." << std::endl;
}

void CInterface::pageNum(int pageNum, int totalNum) {
    std::cout << "===== Page " << pageNum << "/" << totalNum << " =====" << std::endl;
}

void CInterface::answer(int questionNum) {
    std::cout << "Write answer to question number " << questionNum << ": ";
}

void CInterface::continueTeacher() {
    std::cout << "Would you like to create another test?(y/n)" << std::endl;
}

void CInterface::continueStudent() {
    std::cout << "Would you like to fill another test?(y/n)" << std::endl;
}

void CInterface::finalPoints(int score, int total) {
    std::cout << "Final score: " << score << "/" << total << std::endl;
}

void CInterface::selectType() {
    std::cout << "Choose the question type\n"
              <<  "************\n"
              << "0) Exact word\n"
              << "1) Exact word from set of words\n"
              << "2) The answer has to contain word in the sentence\n"
              << "************\n";
}

void CInterface::writeOpenTextWord() {
    std::cout << "Write the word that the answer should contain: " << std::endl;
}

void CInterface::writeOpenTextSet() {
    std::cout << "Write the number of options(max 30): " << std::endl;
}

void CInterface::wrongAnswer(const std::string &answer) {
    std::cout << "The answer was incorrect." << std::endl << "The correct answer: " << answer << std::endl;
}

void CInterface::rightAnswer() {
    std::cout << "The question was correctly answered." << std::endl;
}

void CInterface::pressKey() {
    std::cout << "Press ENTER to continue..." << std::endl;

}

void CInterface::possibilties(int possibilities) {
    std::cout << "Write " << possibilities << " answers for the question:" << std::endl;
}

void CInterface::outputA() {
    std::cout << "a,";
}

void CInterface::outputB() {
    std::cout << "b,";
}

void CInterface::outputC() {
    std::cout << "c,";
}





