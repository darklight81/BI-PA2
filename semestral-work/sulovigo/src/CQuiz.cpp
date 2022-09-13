#include <iostream>
#include "CQuiz.h"
#include "CInterface.h"

void CQuiz::fill() {
    cin.ignore();

    int points = 0, totalPoints = 0;

    for (unsigned i = 0; i < pages.size(); ++i) {
        totalPoints += pages.at(i).showQuestions();
        CInterface::pageNum(i + 1, pages.size());
        points += pages.at(i).getAnswers();
        CInterface::pressKey();
        getchar();
        CInterface::refresh();
    }

    CInterface::finalPoints(points, totalPoints);
}

void CQuiz::load() {
    CInterface::loadFilename();

    string fileName;
    std::cin >> fileName;
    CInterface::refresh();
    file.open(fileName, ios::in);
    if (!file.is_open()) {
        CInterface::error();
        return;
    }
    //LOADS QUESTIONS FROM FILE INTO PAGE CLASS
    string question, answer, a, b, c, type, options;
    CQuestion* q;
    int typeInt, optionsInt;
    int cnt = 0;
    int pageIndex = 0;
    while (getline(file, question)) {
        if (cnt % 3 == 0) {
            pages.push_back(CPage());
            if (cnt != 0)
                pageIndex++;
        }

        if (question == "0") {
            getline(file, question);
            getline(file, type);
            try {
                typeInt = std::stoi(type);
            }
            catch (...) {
                CInterface::wrongFile();
                break;
            }
            if (typeInt == 0) {
                getline(file, answer);
                q = new COpenText(question, answer, typeInt);
            } else if (typeInt == 1) {
                std::vector<std::string> answers;

                getline(file, options);
                try {
                    optionsInt = std::stoi(options);
                }
                catch (...) {
                    CInterface::wrongFile();
                    break;
                }
                if (optionsInt <= 0) {
                    CInterface::wrongFile();
                    break;
                }
                for (int i = 0; i < optionsInt; ++i) {
                    getline(file, answer);
                    answers.push_back(answer);
                }
                q = new COpenText(question, answers);
            } else if (typeInt == 2) {
                getline(file, answer);
                q = new COpenText(question, answer, typeInt);
            } else {
                CInterface::wrongFile();
                break;
            }

        } else if (question == "1") {
            getline(file, question);
            getline(file, a);
            getline(file, b);
            getline(file, c);
            q = new CMultipleChoice(question, a, b, c);
        } else if (question == "2") {
            getline(file, question);
            getline(file, a);
            getline(file, b);
            getline(file, c);
            q = new CSequence(question, a, b, c);
        } else {
            CInterface::wrongFile();
            break;
        }
        pages.at(pageIndex).addQuestion(q);
        cnt++;
    }
    file.close();
}

void CQuiz::init() {
    int input, cont;
    CInterface::refresh();
    CInterface::chooseUser();

    input = getchar();
    CInterface::refresh();

    // STUDENT'S MODE
    if (input == '0') {
        while (true) {
            clean();
            load();
            fill();

            CInterface::continueStudent();
            //Decides if the student wants to fill another CQuiz or no.
            while (true) {
                cont = getchar();
                if (cont == 'n' || cont == 'y')
                    break;
                else if ( cont == '\n')
                    continue;
                else
                    CInterface::wrongInput();
            }

            if (cont == 'n')
                break;
        }
    }
        // TEACHER'S MODE
    else if (input == '1') {
        while (true) {
            createQuestions();
            CInterface::continueTeacher();
            //Decides if the teacher wants to create another CQuiz or not.
            while (true) {
                cont = getchar();
                if (cont == 'n' || cont == 'y')
                    break;
                else if (cont == '\n')
                    continue;
                else
                    CInterface::wrongInput();
            }
            if (cont == 'n')
                break;
        }
    } else {
        CInterface::refresh();
        CInterface::wrongInput();
    }
}

void CQuiz::createQuestions() {
    CInterface::refresh();
    CInterface::createFilename();

    cin.ignore();
    string fileName;
    getline(cin, fileName);

    file.open(fileName, ios::out);

    if (!file.is_open()) {
        CInterface::error();
        return;
    }
    //START OF CREATING QUESTIONS
    bool flag = true;
    string input;
    int input2;

    string question, answer;

    CInterface::refresh();

    //Repeats the creation of question until user stop it.
    while (flag) {
        CInterface::chooseQuestion();

        getline(cin, input);

        if (input.size() > 1)
            input2 = -1;
        else
            input2 = input[0];

        switch (input2) {
            //creates an open text question
            case '0':
                file << '0' << endl;

                CInterface::selectType();

                while (true) {
                    getline(cin, input);
                    if (input.size() > 1)
                        input2 = -1;
                    else
                        input2 = input[0];
                    if (input2 == '0' || input2 == '1' || input2 == '2')
                        break;
                    else
                        CInterface::wrongInput();
                }

                CInterface::writeQuestion();
                getline(cin, question);
                file << question << endl;
                //Sleect the type of the open text question
                switch (input2) {
                    case '0':
                        file << '0' << endl;
                        CInterface::writeOpenText();
                        getline(cin, answer);
                        file << answer << endl;
                        break;
                    case '1':
                        file << '1' << endl;
                        int possibilities;
                        CInterface::writeOpenTextSet();
                        while(true) {
                            if ( !(cin >> possibilities) || possibilities > 30 || possibilities <= 0)
                            {
                                cin.clear();
                                cin.ignore();
                                CInterface::wrongInput();
                            }
                            else{
                                cin.ignore();
                                break;
                            }
                        }
                        file << possibilities << endl;
                        CInterface::possibilties(possibilities);
                        for (int i = 0; i < possibilities; ++i) {
                            getline(cin, answer);
                            file << answer << endl;
                        }
                        break;
                    case '2':
                        file << '2' << endl;
                        CInterface::writeOpenTextWord();
                        getline(cin, answer);
                        file << answer << endl;
                        break;
                }
                CInterface::refresh();
                break;

                // Multiple choice
            case '1':
                file << '1' << endl;

                CInterface::writeQuestion();
                getline(cin, question);
                file << question << endl;

                CInterface::writeMultipleChoice();
                CInterface::outputA();
                getline(cin, answer);
                file << answer << endl;
                CInterface::outputB();
                getline(cin, answer);
                file << answer << endl;
                CInterface::outputC();
                getline(cin, answer);
                file << answer << endl;
                CInterface::refresh();
                break;

                // Sequence question
            case '2':
                file << '2' << endl;

                CInterface::writeQuestion();
                getline(cin, question);
                file << question << endl;

                CInterface::writeSequence();
                CInterface::outputA();
                getline(cin, answer);
                file << answer << endl;
                CInterface::outputB();
                getline(cin, answer);
                file << answer << endl;
                CInterface::outputC();
                getline(cin, answer);
                file << answer << endl;
                CInterface::refresh();
                break;

                // End
            case '3':
                flag = false;
                break;
                // Wrong input
            default:
                CInterface::refresh();
                CInterface::wrongInput();
                break;
        }
    }
    file.close();

}

void CQuiz::clean() {
    pages.clear();
    file.close();
}


