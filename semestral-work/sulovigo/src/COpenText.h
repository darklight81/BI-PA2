#ifndef SEMESTRALKA_COPENTEXT_H
#define SEMESTRALKA_COPENTEXT_H


#include <vector>
#include "CQuestion.h"

/**
 * Open text question which has 3 types, 1st - student has to get the exact answer right, 2nd - there are more possible answers, 3rd - the answer has to contain the answer.
 */
class COpenText : public CQuestion {
private:
    int type;
    std::string answer;
    std::vector<std::string> answers;

public:
    /**
     * Constructor for the type 1 and type 3 question.
     * @param question - string which represents question.
     * @param answer - string which represents the answer.
     * @param type - int which represents the type to be stored. (either 0 or 2)
     */
    COpenText(std::string question, std::string answer, int type);

    /**
     * Constructor for the type 2 question
     * @param question - string which represents question.
     * @param answers - vector of all the possible answers.
     */
    COpenText(std::string question, std::vector<std::string> answers);
    /**
     * Gets input from cin and checks if it's correct.
     * @return true if the input answer is correct, false if wrong.
     */
    bool checkAnswer()const override;
    /*
     * Gets a correct answer and returns it.
     */
    std::string getAnswer()const override;

    CQuestion* clone()const override;
};


#endif //SEMESTRALKA_COPENTEXT_H
