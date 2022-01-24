#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#pragma comment(lib, "winmm.lib")
#include <windows.h>
using namespace std;

bool run;

void list_score() {
    ifstream in;
    in.open("profile.txt");
    while (!in.eof()) {
        string line1;
        getline(in, line1);

        if (in.fail()) {
            break;
        }
        cout << line1 << endl;
    }
}

int countLines(vector<string> words) {
    return words.size();
}


string getWord() {
    ifstream words_file;
    try {
        words_file.open("words.txt");
    }
    catch (...) {
        cout << "Error" << endl;
        run = false;
    }
    string line;
    vector<string> words;

    while (getline(words_file, line)) {
        words.push_back(line);
    }
    srand(time(NULL));
    int number_of_words = countLines(words);
    string word = words.at(rand() % number_of_words);
    return word;
}


string runAI() {
    return (getWord());
}

string updateWord(string word, vector<int> characterLocations, char to_update) {
    char dummy;
    vector<char> word_vec(word.length(), dummy);

    for (int i = 0; i < word.length(); i++) {
        vector<int>::iterator found = find(characterLocations.begin(), characterLocations.end(), i);
        if (found != characterLocations.end()) {
            word_vec[i] = to_update;
            characterLocations.erase(found);
        }
        else {
            word_vec[i] = word[i];
        }
    }


    string result(word_vec.begin(), word_vec.end());
    return result;
}


vector<int> findLocation(string sample, char findIt)
{
    vector<int> characterLocations;
    for (int i = 0; i < sample.size(); i++)
        if (sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

void toLower(string& word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void draw_head(int) {

    cout << " ____________    " << endl;
    cout << "|    (0__0)      " << endl;
    cout << "|                " << endl;
    cout << "|                " << endl;
    cout << "|                " << endl;
    cout << "|                " << endl;
    cout << "|                " << endl;
    cout << "|__              " << endl;
    cout << " " << endl;
}
void draw_body(int) {
    cout << " ____________   " << endl;
    cout << "|    (0__0)     " << endl;
    cout << "|      ||       " << endl;
    cout << "|      ||       " << endl;
    cout << "|      ||       " << endl;
    cout << "|      ||       " << endl;
    cout << "|               " << endl;
    cout << "|__             " << endl;
    cout << " " << endl;
}
void draw_larm(int) {
    cout << " ____________   " << endl;
    cout << "|    (0__0)     " << endl;
    cout << "|      ||       " << endl;
    cout << "|     /||       " << endl;
    cout << "|    / ||       " << endl;
    cout << "|      ||       " << endl;
    cout << "|               " << endl;
    cout << "|__             " << endl;
    cout << " " << endl;

}
void draw_rarm(int) {
    cout << " ____________   " << endl;
    cout << "|    (0__0)     " << endl;
    cout << "|      ||       " << endl;
    cout << "|     /||\\      " << endl;
    cout << "|    / || \\     " << endl;
    cout << "|      ||       " << endl;
    cout << "|               " << endl;
    cout << "|__             " << endl;
    cout << " " << endl;
}
void draw_lleg(int) {
    cout << " ____________   " << endl;
    cout << "|    (0__0)     " << endl;
    cout << "|      ||       " << endl;
    cout << "|     /||\\      " << endl;
    cout << "|    / || \\     " << endl;
    cout << "|      ||       " << endl;
    cout << "|     /         " << endl;
    cout << "|__  /          " << endl;
    cout << " " << endl;
}
void draw_rleg(int) {
    cout << " ____________   " << endl;
    cout << "|    (0__0)     " << endl;
    cout << "|      ||       " << endl;
    cout << "|     /||\\      " << endl;
    cout << "|    / || \\     " << endl;
    cout << "|      ||       " << endl;
    cout << "|     /  \\      " << endl;
    cout << "|__  /    \\     " << endl;
    cout << " " << endl;
}
void latest_status(int num_tries) {


    switch (num_tries) {
    case 5:
        draw_head(5);
        break;

    case 4:
        draw_body(4);
        break;

    case 3:
        draw_larm(3);
        break;

    case 2:
        draw_rarm(2);
        break;

    case 1:
        draw_lleg(1);
        break;

    case 0:
        draw_rleg(0);

    }

}

bool has_only_alpha(string word) { 
    char c;
    for (int i = 0; i < word.length(); i++) {
        c = word.at(i);

        if (!((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z'))) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "======= Welcome to the Hangman =======" << endl;
    int point = 0;

    run = true;
    string name;

    while (run) {
        string startGame;
        cout << "Press 1 for play with your friend" << endl;
        cout << "Press 2 for play for play against the computer" << endl;
        cout << "Press 3 for list of other users score" << endl;
        cout << "Type 'quit' to end the game." << endl;
        cin >> startGame;
        string hidden_word = "";
        string input;

        if (startGame == "1") {
            bool isValidWord = false;

            cout << "******** PLAYER 1'S TURN ********" << endl;
            while (isValidWord == false) {

                cout << "Enter a word: ";
                cin >> input;
                isValidWord = has_only_alpha(input);
                if (isValidWord) {
                    for (int i = 0; i < 70; i++) {
                        cout << "\n" << endl;
                    }
                    break;
                }
                cout << "You can only enter letters." << endl;
                cout << " " << endl;
            }

            for (int j = 0; j < input.length(); j++) {
                hidden_word += "_";
            }

            toLower(input);
            cout << "******** PLAYER 2'S TURN ********" << endl;
            cout << " " << endl;
            bool game_over = false;
            int num_tries = 6; 
            cout << "The word that your friend entered was " << input.length() << " letters long." << endl;
            cout << " " << endl;

            cout << "Updated Word: " << hidden_word << endl;
            cout << " " << endl;

            while ((num_tries > 0) && (game_over == false)) {
                char letter;
                cout << "Number of tries left: " << num_tries << endl;
                cout << " " << endl;
                cout << "If you would like to guess the word, press 1." << endl;
                cout << " " << endl;
                cout << "Enter a letter you think is in the word: ";
                cin >> letter;
                cout << " " << endl;
                stringstream stream;
                string str;
                stream << letter;
                stream >> str;
                toLower(str);
                size_t found = input.find(letter);
                if (letter == '1') {
                    string guess;
                    cout << "What is your guess?" << endl;
                    cin >> guess;
                    cout << " " << endl;
                    if (input == guess) {
                        cout << "You guessed the word right!" << endl;
                        PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//win.wav"), NULL, SND_FILENAME);
                        cout << " " << endl;

                        break;
                    }
                    else {
                        PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//wrong-l.wav"), NULL, SND_FILENAME);
                        num_tries--;
                    }
                }
                if (found != string::npos) {
                    cout << "That letter is in the word!" << endl;
                    cout << " " << endl;
                    vector<int> characterLocations = findLocation(input, letter);
                    hidden_word = updateWord(hidden_word, characterLocations, letter);
                    if (hidden_word == input) {
                        break;
                    }
                    PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//right-l.wav"), NULL, SND_FILENAME);
                    cout << "Updated Word: " << hidden_word << endl;
                    cout << " " << endl;

                }
                else {
                    cout << "That letter is not in the word." << endl;
                    cout << " " << endl;
                    PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//wrong-l.wav"), NULL, SND_FILENAME);
                    num_tries--;
                }

                latest_status(num_tries);
            }
            if (num_tries != 0) {
                cout << "Player 2 wins!" << endl;
                PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//win.wav"), NULL, SND_FILENAME);
                cout << " " << endl;
            }
            else {
                cout << "Player 1 wins!" << endl;
                cout << " " << endl;
                PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//lose.wav"), NULL, SND_FILENAME);
                cout << "The word you entered was: " << input << endl;
                cout << " " << endl;
            }

            if (startGame == "2") {
                cout << "Player name: ";
                cin >> name;

                input = runAI();
                for (int j = 0; j < input.length(); j++) {
                    hidden_word += "_";
                }
                bool game_over = false;

                int num_tries = 6;
                while ((num_tries > 0) && (game_over == false)) { 
                    char letter;
                    cout << "If you would like to guess the word, press 1." << endl;
                    cout << " " << endl;
                    cout << "Number of tries left: " << num_tries << endl;
                    cout << " " << endl;
                    cout << "Enter a letter you think is in the word: ";
                    cin >> letter;
                    if (letter == '1')
                    {
                        string guess;
                        cout << "What is your guess?" << endl;
                        cin >> guess;
                        if (input == guess) { 
                            cout << "You guessed the word right!" << endl;
                            PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//right-l.wav"), NULL, SND_FILENAME);
                            cout << " " << endl;
                            point = point + 10;
                            break;
                        }
                    }
                    else {
                        size_t found = input.find(letter);
                        
                        if (found != string::npos) {
                            cout << "That letter is in the word!" << endl;
                            cout << " " << endl;
                            vector<int> characterLocations = findLocation(input, letter);
                            point = point + 1;
                            cout << "Your point is:" << point << endl;
                            cout << " " << endl;
                            PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//right-l.wav"), NULL, SND_FILENAME); 

                            hidden_word = updateWord(hidden_word, characterLocations, letter);
                            if (hidden_word == input) {
                                break;
                            }
                            cout << "Updated Word: " << hidden_word << endl;
                            cout << " " << endl;
                        }
                        else { 
                            cout << "That letter is not in the word." << endl;
                            cout << " " << endl;
                            PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//wrong-l.wav"), NULL, SND_FILENAME);
                            num_tries = num_tries - 1;
                            latest_status(num_tries);
                        }
                    }
                }
                if (num_tries != 0) {
                    cout << "You win!" << endl;
                    cout << " " << endl;
                    point = point + 10;
                    cout << "Your point is :" << point << endl;
                    cout << " " << endl;
                    PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//win"), NULL, SND_FILENAME);
                }
                else {
                    cout << "You lose" << endl;
                    cout << " " << endl;
                    cout << "Your score is: " << point << endl;
                    cout << " " << endl;
                    PlaySound(TEXT("C://Users//Aybike//Desktop//hangman//sounds//lose.wav"), NULL, SND_FILENAME);
                }
                cout << "The word the computer gave was: " << input << endl; //Print the desired word
                cout << " " << endl;

            }
            if (startGame == "3") {
                list_score();
            }

            else if (startGame == "quit") {
                run = false;
            }
            else {
                cout << "Please input only 1 or 2 or 'quit'." << endl;
            }
        }

        int space = 30;
        int set_w;
        int name_length = name.length();

        set_w = space - name_length;
        if (name_length > 30) {
            space = space + 40;
        }

        ofstream Profile;
        Profile.open("profile.txt", ios::app);
        Profile << endl << name << setw(set_w) << point;
        ifstream Open("profile.txt");
        while (!(Open.eof())) {
            Open >> name >> point;
        }

        return 0;
    }
}
