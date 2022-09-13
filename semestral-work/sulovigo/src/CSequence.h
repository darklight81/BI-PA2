#ifndef SEMESTRALKA_CSEQUENCE_H
#define SEMESTRALKA_CSEQUENCE_H


#include <vector>
#include "CQuestion.h"

/**
 * Sequence question with three possibilities which have to be ordered by a student when answering.
 */
class CSequence : public CQuestion {
private:
    std::vector<std::string> answers;
    std::vector<std::string> shuffledAnswers;
public:
    /**
     * Saves answers (a, b, c) in correct order into answers vector and shuffles it into shuffledAnswers vector.
     * @param question - string which represents question
     * @param a - first string in sequence
     * @param b - second string in sequence
     * @param c - third string in sequence
     */
    CSequence(std::string question, std::string a, std::string b, std::string c);

    /**
     * prints out the question on the CPage.
     * @param number - number of the question on the actual CPage.
     */
    void showQuestion(int number) const override;
    /**
     * Gets input from cin and checks if it's correct.
     * @return true if the input answer is correct, false if wrong.
     */
    bool checkAnswer()const override;
    /*
     * Gets a correct answer and returns it.
     */
    std::string getAnswer()const override;

    CQuestion* clone() const override;
};


#endif //SEMESTRALKA_CSEQUENCE_H
