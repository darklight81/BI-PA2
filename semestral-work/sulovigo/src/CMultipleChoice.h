#ifndef SEMESTRALKA_CMULTIPLECHOICE_H
#define SEMESTRALKA_CMULTIPLECHOICE_H

#include <vector>
#include "CQuestion.h"

/**
 * Multiple choice question with three possibilities from which only one is correct (that is stored in string answer, while in vector answers the answers are shuffled randomly)
 */
class CMultipleChoice : public CQuestion {
private:
    std::vector<std::string> answers;
    std::string answer;
public:
    /**
     * Constructor which also shuffles the answers in vector answers
     * @param question - string which represents question.
     * @param a - string which represents the correct answer.
     * @param b - string which represents the 2nd possibility.
     * @param c - string which represents the 3rd possibility.
     */
    CMultipleChoice(std::string question, std::string a, std::string b, std::string c);

    /**
     * Prints out the question on the CPage.
     * @param number - number of the question on the actual CPage.
     */
    void showQuestion(int number) const override;

    /**
     * Gets input from cin and checks if it's by comparing it to the string answer
     * @return true if the input answer is equal to the string answer, false if not.
     */
    bool checkAnswer() const override;

    /**
     * Getter to get the correct answer;
     * @return string answer
     */
    std::string getAnswer() const override;

    CQuestion* clone() const override;
};


#endif //SEMESTRALKA_CMULTIPLECHOICE_H
