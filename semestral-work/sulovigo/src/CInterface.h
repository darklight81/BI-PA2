#ifndef SEMESTRALKA_CINTERFACE_H
#define SEMESTRALKA_CINTERFACE_H

/**
 * Handles printing out messages to the terminal.
 */
class CInterface {
public:
    /**
     * Refreshes the screen.
     */
    static void refresh();
    /**
     * Prints out menu to choose a user.
     */
    static void chooseUser();
    /**
     * Prints out menu to choose type of a question.
     */
    static void chooseQuestion();

    static void wrongInput();

    static void createFilename();

    static void loadFilename();

    static void error();

    static void writeQuestion();

    static void writeOpenText();

    static void writeMultipleChoice();

    static void writeSequence();

    static void wrongFile();

    /**
     * Prints out the actual CPage the CQuiz is on.
     * @param pageNum - number of the actual CPage.
     * @param totalNum  - the total number of pages.
     */
    static void pageNum(int pageNum, int totalNum);

    static void answer(int questionNum);

    static void continueStudent();

    static void continueTeacher();

    /**
     * Prints out the final score of a filled CQuiz.
     * @param score - number of correctly answered questions
     * @param total - total number of questions
     */
    static void finalPoints(int score, int total);

    static void selectType();

    static void writeOpenTextSet();

    static void writeOpenTextWord();

    static void wrongAnswer(const std::string &answer);

    static void rightAnswer();

    static void pressKey();

    static void possibilties(int possibilities);

    static void outputA();

    static void outputB();

    static void outputC();
};


#endif //SEMESTRALKA_CINTERFACE_H
