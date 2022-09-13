#ifndef SEMESTRALKA_CQUESTION_H
#define SEMESTRALKA_CQUESTION_H


#include <string>

/**
 * Class of question from which inherits all the questions implemented.
 */
class CQuestion {
protected:
    std::string question;
public:
    virtual ~CQuestion()= default;
    CQuestion();

    /**
     *
     * @param number
     */
    virtual void showQuestion(int number) const;

    /**
     *
     * @return
     */
    virtual bool checkAnswer() const = 0;

    /**
     * Getter of the right answer to the question.
     * @return string which represents answer
     */
    virtual std::string getAnswer() const = 0;
    virtual CQuestion* clone() const = 0;
};


#endif //SEMESTRALKA_CQUESTION_H
