#include "CPage.h"
#include <string>
#include <fstream>

#ifndef SEMESTRALKA_QUIZ_H
#define SEMESTRALKA_QUIZ_H
using namespace std;

/**
 * The main class in which all pages with questions are stored and file stream to save the created quizzes.
 */
class CQuiz {
private:
    std::vector<CPage> pages;
    fstream file;

public:
    CQuiz() = default;
    /**
     * Determines if student or teacher is using the programme.
     */
    void init();

    /**
     * Loads the CQuiz from file defined by user.
     */
    void load();

    /**
     * Creates a file with set of questions and answers, ready to be used.
     */
    void createQuestions();

    /**
     * Shows question from pre-loaded CQuiz and let the student answer it.
     */
    void fill();
    /**
     * Cleans the pages and close file stream.
     */
    void clean();
};


#endif //SEMESTRALKA_QUIZ_H
