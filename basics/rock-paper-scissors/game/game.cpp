#include <iostream>
#include<string>
#include<ctime>
#include<iomanip>
using namespace std;
//enum for each chooci
enum enchoice { stone = 1, paper = 2, scissors = 3 };
//enum for each one won 
enum enwiner { player = 1, coputer = 2, draw = 3 };

//structure  to storge info about each  round in game
//number of round , chocie of player ,choice of computer ,and winer
struct stround_result {
    short round_number = 1;
    enchoice player_choice;
    enchoice coputer_choice;
    enwiner round_winer;
    string winer_name;
};

//structure to storge info about all round in game
struct stgame_result {
    short game_round = 1;
    short player_wine_times = 0;
    short coputer_wine_times = 0;
    short draw = 0;
    enwiner final_winer;
    string winer_name;
};



//fuction for clean screen after end gami
void cleanscrean() {
    system("cls");
    system("color 0f");
}


enchoice fplayer_choice() {

    short number_choice = 1;
    do {
        cout << "please inter your choic [1]stone [2]paper [3]scissors:"; cin >> number_choice;

    } while (number_choice < 1 || number_choice>3);
    return(enchoice(number_choice));
}

//computer choice by round number functioin
short round_number(short your_from, short your_to) {
    return rand() % (your_to - your_from + 1) + your_from;
}
enchoice fcoputer_choice() {
    return enchoice(round_number(1, 3));
}

//aftare read player choice and player and storege in struct 
//we compieare and returne enum winer
enwiner fround_winer(stround_result your_round_info) {
    if (your_round_info.player_choice == your_round_info.coputer_choice) {
        return enwiner::draw;
    }
    else {
        switch (your_round_info.player_choice) {
        case enchoice::paper:
            if (your_round_info.coputer_choice == enchoice::scissors) {
                return enwiner::coputer;
            }
            break;

        case enchoice::stone:
            if (your_round_info.coputer_choice == paper) {
                return enwiner::coputer;

            }
            break;

        case enchoice::scissors:
            if (your_round_info.coputer_choice == stone) {
                return enwiner::coputer;
            }
            break;

        }
        return enwiner::player;

    }
}
//take enume winer and return name
string fround_winer_name(enwiner your_round_winer) {
    string array_winer[3] = { "player","coputer","draw" };
    return array_winer[your_round_winer - 1];
}

//after read computer and player and determinat winer  we print info
void set_winer_screencolor(enwiner your_round_winer) {
    if (your_round_winer == enwiner::coputer) {
        cout << "\a";
        system("color 4f");
    }
    else if (your_round_winer == enwiner::player) {
        cout << "\a";
        system("color 2f");
    }
    else {
        cout << "\a";
        system("color 6f");
    }
}
string fround_choice_name(enchoice your_choice) {
    string array_choice[3] = { "stone","paper","scissors" };
    return  array_choice[your_choice - 1];
}
void print_round_result(stround_result your_round_info) {
    cout << "________________________round[" << your_round_info.round_number << "]________________________\n";
    cout << "player choice:" << fround_choice_name(your_round_info.player_choice) << endl;
    cout << "computer choice:" << fround_choice_name(your_round_info.coputer_choice) << endl;
    cout << "round winer:" << your_round_info.winer_name << endl;
    cout << "______________________________________________________________________________________";
    cout << "\n\n";
    set_winer_screencolor(your_round_info.round_winer);
}

//after end all round we fill game info and detrmint which one win in gami
enwiner fgame_winer(stgame_result your_game_info) {
    if (your_game_info.player_wine_times > your_game_info.coputer_wine_times) {
        return enwiner::player;
    }
    else if (your_game_info.player_wine_times < your_game_info.coputer_wine_times) {
        return enwiner::coputer;
    }
    else {
        return enwiner::draw;
    }
}
stgame_result fill_game_info(stgame_result your_game_info, short your_number_round) {
    stgame_result game_result;
    game_result.game_round = your_number_round;
    game_result.player_wine_times = your_game_info.player_wine_times;
    game_result.coputer_wine_times = your_game_info.coputer_wine_times;
    game_result.draw = your_game_info.draw;
    game_result.final_winer = fgame_winer(game_result);
    game_result.winer_name = fround_winer_name(game_result.final_winer);

    return game_result;

}

//read number of round and repeat all 
stgame_result start_round(short your_number_round) {
    stgame_result game_info;
    for (short i = 1; i <= your_number_round; i++) {
        cout << "round[" << i << "]begin:\n";
        stround_result round_info;
        round_info.round_number = i;
        round_info.player_choice = fplayer_choice();
        round_info.coputer_choice = fcoputer_choice();
        round_info.round_winer = fround_winer(round_info);
        round_info.winer_name = fround_winer_name(round_info.round_winer);

        if (round_info.round_winer == enwiner::player) {
            game_info.player_wine_times++;
        }
        else if (round_info.round_winer == enwiner::coputer) {
            game_info.coputer_wine_times++;
        }
        else {
            game_info.draw++;
        }

        print_round_result(round_info);

    }
    return fill_game_info(game_info, your_number_round);

}


short round_number() {
    short number = 1;
    do {

        cout << "please inter number of round:"; cin >> number;
    } while (number < 1 || number>10);
    return number;
}

//aftare read number of round and function of start_round worke 
//and retrive structure withe game result we print it 
void print_final_result(stgame_result your_final_result) {
    cout << "\t\t\t__________________________________________________________\n";
    cout << "\t\t\t                +++ G A M E R  O V E R ++++               \n";
    cout << "\t\t\t__________________________________________________________\n";
    cout << "\t\t\t________________________[game result}_____________________\n";
    cout << "\t\t\t" << "game rounds" << ":" << your_final_result.game_round << endl;
    cout << "\t\t\t" << "player1 win times" << ":" << your_final_result.player_wine_times << endl;
    cout << "\t\t\t" << "coputer won times" << ":" << your_final_result.coputer_wine_times << endl;
    cout << "\t\t\t" << "draw times" << ":" << your_final_result.draw << endl;
    cout << "\t\t\t" << "final winer" << ":" << your_final_result.winer_name << endl << endl;


    cout << "\t\t\t\t_______________________________________________________________\n\n";

}

//her we start
void play() {
    char repeat = 'y';
    do {
        cleanscrean();

        stgame_result final_result = start_round(round_number());

        print_final_result(final_result);

        cout << "do your want to play again [y] or[n]:"; cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
}

int main()
{
    srand(time(0));

    play();

}

