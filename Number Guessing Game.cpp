#include <iostream>
#include <cstdlib> 
#include <ctime>   
using namespace std;

int main() {
    srand(time(0)); // Seed for random number generation
    int number_to_guess = rand() % 100 + 1; // Random number between 1 and 100
    int user_guess;
    int attempts = 0;

    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I have chosen a number between 1 and 100. Can you guess it?" << endl;

    do {
        cout << "Enter your guess: ";
        cin >> user_guess;
        attempts++;

        if (user_guess > number_to_guess) {
            cout << "Too high! Try again." << endl;
        } else if (user_guess < number_to_guess) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts." << endl;
        }
    } while (user_guess != number_to_guess);

    return 0;
}

