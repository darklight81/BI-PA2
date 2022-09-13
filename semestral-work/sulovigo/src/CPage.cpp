#include <iostream>
#include "CPage.h"
#include "CInterface.h"

unsigned CPage::showQuestions() {
    for (unsigned i = 0; i < qNum; ++i) {
        questions[i]->showQuestion(i+1);
    }
    return qNum;
}

void CPage::addQuestion(CQuestion* question) {
    questions.push_back(question);
    qNum++;
}


int CPage::getAnswers() {
    int points = 0;
    std::string key;
    std::vector<std::string> keys;
    for (unsigned i = 0; i < qNum; ++i) {
        CInterface::answer(i + 1);
        if(questions.at(i)->checkAnswer()){
            points++;
            CInterface::rightAnswer();
        }
        else CInterface::wrongAnswer(questions.at(i)->getAnswer());
    }
    return points;
}
CPage::CPage():questions{}{}

CPage::CPage(const CPage &p) {
    for (auto x : p.questions){
        this->questions.push_back(x->clone());
    }
    this->qNum = p.qNum;
}

CPage::~CPage() {
	for (auto x : questions)
		delete x;
}
CPage &CPage::operator=(CPage p) {
    this->questions.swap(p.questions);
    return *this;
}
