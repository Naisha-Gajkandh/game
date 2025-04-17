#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Base class
class User {
protected:
    string name;

public:
    User(string n) : name(n) {}
    string getName() const { return name; }
};

// Derived class
class Player : public User {
    int score;

public:
    Player(string n) : User(n), score(0) {}

    void addScore(int s) { score += s; }

    int getScore() const { return score; }

    void saveScore() {
        ofstream file("leaderboard.txt", ios::app);
        if (file)
            file << name << " " << score << "\n";
    }

    void showScore() const {
        cout << "\nTotal Score: " << score << "\n";
    }

    friend void displayPlayerData(const Player& p);
};

// Friend function
void displayPlayerData(const Player& p) {
    cout << "\n[Friend Function] Player Name: " << p.name << ", Score: " << p.score << "\n";
}


class Game {
    static int pseudoRandomIndex(int seed, int mod) {
        return (seed * 17 + 13) % mod;
    }

public:
    static void quickMath(Player& p) {
        static int counter = 1;
        int a, b;
        string operation;
        int correctAnswer;

        switch (counter % 4) {
            case 0:
                a = 10 * counter;
                b = 5;
                operation = "/";
                correctAnswer = a / b;
                break;
            case 1:
                a = 15 + counter;
                b = 20;
                operation = "+";
                correctAnswer = a + b;
                break;
            case 2:
                a = 30 - counter;
                b = 10;
                operation = "-";
                correctAnswer = a - b;
                break;
            case 3:
                a = 5 * counter;
                b = 3;
                operation = "*";
                correctAnswer = a * b;
                break;
        }

        cout << "\nQuick Math: What is " << a << " " << operation << " " << b << "?\n";
        int ans;
        cin >> ans;

        if (ans == correctAnswer) {
            cout << "Correct!\n";
            p.addScore(10);
        } else {
            cout << "Incorrect.\n";
        }

        counter++;
    }

    static void shuffleString(string& str, int seed) {
        int n = str.size();
        for (int i = 0; i < n - 1; ++i) {
            int j = pseudoRandomIndex(seed + i, n - i) + i;
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }
    }

    static void wordScramble(Player& p) {
        static int seed = 1;
        vector<string> words = {"apple", "banana", "grape", "orange", "watermelon"};
        int index = pseudoRandomIndex(seed, words.size());
        string word = words[index];
        string scrambledWord = word;

        shuffleString(scrambledWord, seed);

        string guess;
        cout << "\nWord Scramble: Unscramble the word: " << scrambledWord << "\n";
        cout << "Your guess: ";
        cin >> guess;

        if (guess == word) {
            cout << "Correct! You guessed the word!\n";
            p.addScore(10);
        } else {
            cout << "Incorrect. The correct word was: " << word << "\n";
        }

        seed++;
    }

    static void showLeaderboard() {
        ifstream file("leaderboard.txt");
        if (!file) {
            cout << "No scores yet.\n";
            return;
        }

        string name;
        int score;
        cout << "\nLeaderboard:\n";
        while (file >> name >> score) {
            cout << name << " Score: " << score << "\n";
        }
    }
};

int main() {
    string name;
    cout << "Welcome to MindMaze!\nEnter your name: ";
    getline(cin, name);
    Player player(name);

    int choice;
    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Quick Math Game\n";
        cout << "2. Word Scramble Game\n";
        cout << "3. Show Score\n";
        cout << "4. Leaderboard\n";
        cout << "5. Friend Display Player Info\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: Game::quickMath(player); break;
            case 2: Game::wordScramble(player); break;
            case 3: player.showScore(); break;
            case 4: Game::showLeaderboard(); break;
            case 5: displayPlayerData(player); break;
            case 0:
                cout << "Saving your score...\n";
                player.saveScore();
                break;
            default: cout << "Invalid option.\n";
        }

    } while (choice != 0);

    cout << "Thanks for playing, " << player.getName() << "!\n";
    return 0;
}
