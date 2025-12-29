#include <iostream>
#include <ctime>
using namespace std;
enum enquestionlevel { easy = 1, mid = 2, hard = 3, mix = 4 };
enum enoperationtype { add = 1, sub = 2, mult = 3, divi = 4, mixop = 5 };

struct stquestion {

    int number1 = 0;
    int number2 = 0;
    enquestionlevel question_level;
    enoperationtype operation_type;
    int correct_answer = 0;
    int user_answer = 0;
    bool answer_is = false;
};

struct stquize {
    int number_question;
    stquestion question_lest[100];
    enquestionlevel question_level;
    enoperationtype operation_type;
    int number_right_answer = 0;
    int number_wrong_answer = 0;
    bool is_pass = false;
};

void resetscreen() {
    system("cls");
    system("color 0f");
}



int read_number_question() {
    int number;
    do {
        cout << "pleas inter number question:"; cin >> number;
    } while (number < 0 || number>10); \
        return number;
}
enquestionlevel read_question_level() {
    int number;
    do {
        cout << "pleser inter level of question [1]easey [2]mid [3]hard [4]mix: "; cin >> number;
    } while (number < 0 || number>4);
    return enquestionlevel(number);
}
enoperationtype read_operation_type() {
    int number;
    do {
        cout << "pleser inter level of question [1]add [2]sub [3]malti [4]divi [5]mix: "; cin >> number;
    } while (number < 0 || number>5);
    return enoperationtype(number);
}


int random_number(int your_from, int your_to) {
    return rand() % (your_to - your_from + 1) + your_from;
}
int simplycalculat(int your_number1, int your_number2, enoperationtype your_operation_type) {
    switch (your_operation_type) {
    case enoperationtype::add:
        return your_number1 + your_number2;
        break;
    case enoperationtype::sub:
        return your_number1 - your_number2;
        break;
    case enoperationtype::mult:
        return your_number1 * your_number2;
        break;
    case enoperationtype::divi:
        return your_number1 / your_number2;
        break;

    }
}
stquestion generat_question(enquestionlevel your_question_level, enoperationtype your_operation_type) {
    stquestion question;
    if (your_question_level == enquestionlevel::mix) {
        your_question_level = enquestionlevel(random_number(1, 3));
    }
    if (your_operation_type == enoperationtype::mixop) {
        your_operation_type = enoperationtype(random_number(1, 4));
    }
    question.operation_type = your_operation_type;
    switch (your_question_level) {
    case enquestionlevel::easy:
        question.number1 = random_number(1, 10);
        question.number2 = random_number(1, 10);
        question.correct_answer = simplycalculat(question.number1, question.number2, your_operation_type);
        question.question_level = your_question_level;
        return question;

    case enquestionlevel::mid:
        question.number1 = random_number(20, 50);
        question.number2 = random_number(20, 50);
        question.correct_answer = simplycalculat(question.number1, question.number2, your_operation_type);
        question.question_level = your_question_level;
        return question;

    case enquestionlevel::hard:
        question.number1 = random_number(50, 100);
        question.number2 = random_number(50, 100);
        question.correct_answer = simplycalculat(question.number1, question.number2, your_operation_type);
        question.question_level = your_question_level;
        return question;

    }
    return question;

}
void generat_quize_question(stquize& your_quize) {
    for (int i = 0; i < your_quize.number_question; i++) {
        your_quize.question_lest[i] = generat_question(your_quize.question_level, your_quize.operation_type);

    }

}


char operation_char(enoperationtype your_operation) {
    char array_operation[4] = { '+','-','*','/' };
    return array_operation[your_operation - 1];

}
void print_question(stquize your_quize, int number_question) {
    cout << endl << "question[" << number_question + 1 << "\\" << your_quize.number_question << "]\n";
    cout << your_quize.question_lest[number_question].number1 << endl;
    cout << your_quize.question_lest[number_question].number2 << "  " << operation_char(your_quize.question_lest[number_question].operation_type);
    cout << "______________________________\n";
}

int read_answer() {
    int number;
    cin >> number;
    return number;
}

bool check_answer(int user_answer, int correct_answer) {
    if (user_answer == correct_answer) {
        return true;
    }
    else {
        return false;
    }
}

void set_winer_screencolor(stquestion your_question) {
    if (your_question.answer_is) {
        cout << "\a";
        system("color 2f");
    }

    else {
        cout << "\a";
        system("color 4f");
    }
}
void print_question_result(stquestion your_question) {
    if (your_question.answer_is) {
        cout << endl << "your anser is correc:)-\n\n\n";
    }
    else {
        cout << "your answer is not correct:-)" << endl;
        cout << "the correct answer is :" << your_question.correct_answer << endl << endl;
    }
    set_winer_screencolor(your_question);
}

void aske_check_answer(stquize& your_quize) {
    for (int i = 0; i < your_quize.number_question; i++) {
        print_question(your_quize, i);
        your_quize.question_lest[i].user_answer = read_answer();
        your_quize.question_lest[i].answer_is = check_answer(your_quize.question_lest[i].user_answer, your_quize.question_lest[i].correct_answer);


        if (your_quize.question_lest[i].answer_is) {
            your_quize.number_right_answer++;
        }
        else {
            your_quize.number_wrong_answer++;
        }

        print_question_result(your_quize.question_lest[i]);

    }
}



string pass_fail(int your_number_correc, int your_number_wrong) {
    if (your_number_correc >= your_number_wrong) {
        return "pass\n";
    }
    else {
        return "fail\n";
    }
}
string convert_question_level(enquestionlevel your_question_level) {
    switch (your_question_level) {
    case enquestionlevel::easy:
        return "easy\n";
        break;
    case enquestionlevel::mid:
        return "middel\n";
        break;
    case enquestionlevel::hard:
        return "hard\n";
        break;
    default:
        return "mix\n";
        break;
    }
}
string convert_operation_type(enoperationtype your_opertion_type) {
    switch (your_opertion_type) {
    case enoperationtype::add:
        return "add\n";
        break;
    case enoperationtype::sub:
        return "sub\n";
        break;
    case enoperationtype::mult:
        return "mult\n";
        break;
    default:
        return "mix\n";
        break;
    }
}
void print_final_result(stquize& your_quize) {
    cout << "________________________________________________\n";
    cout << "   final results is " << pass_fail(your_quize.number_right_answer, your_quize.number_wrong_answer);
    cout << "________________________________________________\n";
    cout << "number of question:" << your_quize.number_question << endl;
    cout << "question level:" << convert_question_level(your_quize.question_level);
    cout << "operation type:" << convert_operation_type(your_quize.operation_type);
    cout << "number of right answer:" << your_quize.number_right_answer << endl;
    cout << "number of wrong aswer :" << your_quize.number_wrong_answer << endl;
    cout << "__________________________________________________\n";
}



void playmatchgame() {
    stquize quize;
    quize.number_question = read_number_question();
    quize.question_level = read_question_level();
    quize.operation_type = read_operation_type();


    //
    generat_quize_question(quize);

    aske_check_answer(quize);

    print_final_result(quize);

}

void startgame() {
    char repeat = 'y';
    do {
        resetscreen();
        playmatchgame();

        cout << "do you want to play again:"; cin >> repeat;

    } while (repeat == 'y' || repeat == 'Y');
}
int main()
{

    srand(time(0));

    startgame();

}

