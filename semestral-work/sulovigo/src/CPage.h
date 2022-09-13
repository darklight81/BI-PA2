#ifndef SEMESTRALKA_CPAGE_H
#define SEMESTRALKA_CPAGE_H

#include <vector>
#include "CQuestion.h"
#include "CMultipleChoice.h"
#include "COpenText.h"
#include "CSequence.h"

/**
 * Represents one CPage of the CQuiz on which there are 3 questions stored.
 */
class CPage {
private:
    std::vector<CQuestion*> questions;
public:
    CPage& operator =(CPage p);
    CPage();
    CPage(const CPage &p);
    ~CPage();
    unsigned qNum = 0;
    /**
     * Adds the open text question to the CPage.
     */
    void addQuestion(CQuestion* question);

    /**
     * Shows questions stored in CPage.
     * @return int which says how many questions are on the CPage.
     */
    unsigned showQuestions();

    /**
     * Evaluates the answers to the questions stored on CPage.
     * @return int which represents how many questions where rightly answered
     */
    int getAnswers();
};


#endif //SEMESTRALKA_CPAGE_H
