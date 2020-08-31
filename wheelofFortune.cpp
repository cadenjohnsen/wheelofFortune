/********************
 * Program: assignment4.cpp
 * Author: Caden Johnsen
 * Date: 2/19/17
 * Description: A program to play Wheel of fortune.
 * Input: Numbers, strings, and character guesses
 * Output: Money, winner screen, and fun
 ********************/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

void begin_game(int &players, int &rounds) {
	/********************
	 * Function: begin_game
	 * Description: First function that asks user questions
	 * Parameters: players and rounds address
	 * Pre-Conditions: None
	 * Post-Conditions: Players and rounds
	 * Return: Player number and round number
	 ********************/
begin:
	cout << "How many players?" << endl;
	cin >> players;
	if (players > 3) {
		cout << "Invalid number of players." << endl;
		goto begin;
	}
	cout << "How many rounds to win?" << endl;
	cin >> rounds;
}

void letter_to_underscore(string word, string &under) {
	/********************
	 * Function: letter_to_underscore
	 * Description: Converts user input to underscores
	 * Parameters: word and under address
	 * Pre-Conditions: None
	 * Post-Conditions: under
	 * Return: under
	 ********************/
        for(char c = 'A'; c <= 'z'; ++c) { //all characters in alphabet capital and lowercase
		replace(word.begin(), word.end(), c, '-');
	}
	under = word;
	system("clear");
	cout << under << endl;
}

void get_word(string &word, string &under){
	/********************
	 * Function: get_word
	 * Description: Has user input word to guess
	 * Parameters: word address
	 * Pre-Conditions: None
	 * Post-Conditions: word
	 * Return: word
	 ********************/
	cout << "Enter a phrase." << endl;
        cin.ignore(); //clears cin
        getline(cin, word); // allows white space
        letter_to_underscore(word, under); //calls next function
}

void round_bank(int count_wheel, int player_turn, int &bank1, int &bank2, int &bank3) {
	/********************
	 * Function: round_bank
	 * Description: Adds up money for winner of round
	 * Parameters: count_wheel, player_turn, bank1, bank2, bank3
	 * Pre-Conditions: None
	 * Post-Conditions: bank1, bank2, bank3
	 * Return: banks 1,2 and 3
	 ********************/
        switch(player_turn){ //checks player who won for bank
		case 1:
			bank1 = count_wheel + bank1;
			break;
		case 2:
			bank2 = count_wheel + bank2;
			break;
		case 3:
			bank3 = count_wheel + bank3;
			break;
	}
}

void end_game(int player_turn, int game_bank1, int game_bank2, int game_bank3) {
	/********************
	 * Function: end_game
	 * Description: Ends the game
	 * Parameters: winning player and bank earnings
	 * Pre-Conditions: None
	 * Post-Conditions: None
	 * Return: None
	 ********************/
        if (game_bank1 > game_bank2 && game_bank1 > game_bank3) //checks who has most money at end of game
		cout << "Player one wins!" << endl;
	if (game_bank2 > game_bank1 && game_bank2 > game_bank3)
		cout << "Player two wins!" << endl;
	if (game_bank3 > game_bank2 && game_bank3 > game_bank1)
		cout << "Player three wins!" << endl;
        //print out total money for all players
	cout << "Player 1 has $" << game_bank1 << endl;
	cout << "Player 2 has $" << game_bank2 << endl;
	cout << "Player 3 has $" << game_bank3 << endl;
}

bool game_bank(int &bank1, int &bank2, int &bank3, int &game_bank1, int &game_bank2, int &game_bank3, int &winner, int &round_num, int rounds, int player_turn) {
	/********************
	 * Function: game_bank
	 * Description: Adds up winnings from each round
	 * Parameters: banks 1, 2 and 3, player_turn, game_bank 1, 2, 3
	 * Pre-Conditions: None
	 * Post-Conditions: Total money
	 * Return: round earnings and game earnings
	 ********************/
  if (winner == 1) { //winner variable to determine round winner
		game_bank1 = game_bank1 + bank1;
	}
	if (winner == 2) {
		game_bank2 = game_bank2 + bank2;
	}
	if (winner == 3) {
		game_bank3 = game_bank3 + bank3;
	}
	cout << "Player 1 has $" << game_bank1 << endl;
	cout << "Player 2 has $" << game_bank2 << endl;
	cout << "Player 3 has $" << game_bank3 << endl;
	round_num++;
        if (round_num >= rounds) { //checks to see if out of rounds
		end_game(player_turn, game_bank1, game_bank2, game_bank3);
		return true;
	}
	else {
		return false;
	}
}

void guess_letter(string word, string &under, int wheel_value, int &player_turn, int &bank1, int &bank2, int &bank3){
	/********************
	 * Function: guess_letter
	 * Description: Has user input letter to guess
	 * Parameters: word, under address, wheel_value, player_turn, banks 1, 2, 3
	 * Pre-Conditions: None
	 * Post-Conditions: banks, under, player_turn
	 * Return: banks
	 ********************/
	char c;
	int count = 0;
	string s;

	cout << "Enter a consonant." << endl;
	cin >> c;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                cout << "Cannot enter vowel." << endl;
                player_turn = player_turn + 1;
        }
        else {
		for (int i = 0; i < word.size(); i++) {
			if (toupper(word[i]) ==  toupper(c))
			{
				++ count;
				under[i] = c;
			}
		}
		int count_wheel = count * wheel_value;
		cout << "There are " << count << ' ' << c << "'s!" << endl;
		cout << "you earned $" << count_wheel << "." << endl;
		cout << under << endl;
		round_bank(count_wheel, player_turn, bank1, bank2, bank3);
		if (count  == 0) {
			player_turn = player_turn + 1;
		}
	}
}

int wheel_spin(int &player_turn, int &bank1, int &bank2, int &bank3, string word, string under) {
	/********************
	 * Function: wheel_spin
	 * Description: Spins the wheel
	 * Parameters: None
	 * Pre-Conditions: None
	 * Post-Conditions: Dollar amount
	 * Return: Wheel spin
	 ********************/
	int spin;

	srand(time(NULL));
        spin = rand() % 22; //picks a number between 0 and 21
        cout << "The wheel landed on " << spin << "." << endl;
        if (spin == 0) {
		cout << "You went bankrupt!" << endl;
                if (player_turn == 1) { //finds bank of player and deletes it
			bank1 = 0;
		}
		if (player_turn == 2) {
			bank2 = 0;
		}
		if (player_turn == 3) {
			bank3 = 0;
		}
		player_turn = player_turn + 1;
		return spin;
	}
        if (spin == 21) { //if spin is 21 then turn is given to next player
		cout <<"You skipped your turn." << endl;
		player_turn = player_turn + 1;
		return spin;
	}
	else {
		return spin;
	}
}

void guess_correct(int player_turn, int bank1, int bank2, int bank3, int &winner) {
	/********************
	 * Function: guess_correct
	 * Description: If the player guesses the word they get the money for that round
	 * Parameters: player_turn, banks 1, 2, 3, winner
	 * Pre-Conditions: None
	 * Post-Conditions: winner
	 * Return: winner of round
	 ********************/
        switch(player_turn){ //finds which player guessed correctly
		case 1:
			cout << "Correct! Player " << player_turn << " wins $" << bank1 << endl;
			break;
		case 2:
			cout << "Correct! Player " << player_turn << " wins $" << bank2 << endl;
			break;
		case 3:
			cout << "Correct! Player " << player_turn << " wins $" << bank3 << endl;
			break;
	}
	winner = player_turn;
}

bool guess_word(string word, string under, int &player_turn, int bank1, int bank2, int bank3, int &winner, int players) {
	/********************
	 * Function: guess_word
	 * Description: Allows the user to input a guess for the word
	 * Parameters: word, under, player_turn, banks 1, 2, 3, winner, players
	 * Pre-Conditions: None
	 * Post-Conditions: player_turn, winner
	 * Return: player_turn and winner
	 ********************/
	string guess;
	cout << under << endl;
	cout << "Guess the phrase?" << endl;
        cin.ignore(); //deletes previous cin
        getline(cin, guess); //allows white space
        if (guess == word) { //if the guess is the original word
		guess_correct(player_turn, bank1, bank2, bank3, winner);
		return true;
	}
	else {
		cout << "Incorrect." << endl;
		player_turn = player_turn + 1;
		if (player_turn > players)
			player_turn = 1;
		return false;
	}
	cout << under << endl;
}

void vowel(string word, string &under, int wheel_value, int &player_turn, int &bank1, int &bank2, int &bank3) {
	/********************
	 * Function: vowel
	 * Description: If the player guesses a vowel they lose $10 and guess a vowel
	 * Parameters: player_turn, word, under, banks 1, 2, 3, wheel_value
	 * Pre-Conditions: None
	 * Post-Conditions: None
	 * Return: String with vowel in it
	 ********************/
	char c;
	int count = 0;
        int count_wheel = count * wheel_value;
	cout << "Enter a vowel." << endl;
        cin.ignore();
        cin >> c;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
	for (int i = 0; i < word.size(); i++) {
		if (toupper(word[i]) ==  toupper(c))
		{
			++ count;
			under[i] = c;
		}
	}
	cout << "There are " << count << ' ' << c << "'s!" << endl;
	cout << under << endl;
	round_bank(count_wheel, player_turn, bank1, bank2, bank3);
        }
        else {
            cout << "Cannot enter consonant." << endl;
            player_turn = player_turn + 1;
        }
}

void vowel_start(string word, string &under, int wheel_value, int &player_turn, int &bank1, int &bank2, int &bank3, int &vowel_counter){
    //checks if player has $10
    if (player_turn == 1 && bank1 > 10 && vowel_counter == 0) {
        bank1 = bank1 - 10;
        vowel_counter = 1;
        vowel(word, under, wheel_value, player_turn, bank1, bank2, bank3);
    }
    if (player_turn == 2 && bank2 > 10 && vowel_counter == 0) {
        bank2 = bank2 - 10;
        vowel_counter = 1;
        vowel(word, under, wheel_value, player_turn, bank1, bank2, bank3);
    }
    if (player_turn == 3 && bank3 > 10 && vowel_counter == 0) {
        bank3 = bank3 - 10;
        vowel_counter = 1;
        vowel(word, under, wheel_value, player_turn, bank1, bank2, bank3);
    }
    else {
        cout << "You do not have enough money to buy a vowel or you already bought one." << endl;
    }
}

int main() {
	/********************
	 * Function: main
	 * Description: Initializes variables and calls function
	 * Parameters: None
	 * Pre-Conditions: None
	 * Post-Conditions: None
	 * Return: 0
	 ********************/
	int players = 0;
	int rounds = 0;
	string word;
	string under;
	int i = 0;
	int wheel_value = 0;
	int player_turn = 1;
	int bank1 = 0;
	int bank2 = 0;
	int bank3 = 0;
	int game_bank1 = 0;
	int game_bank2 = 0;
	int game_bank3 = 0;
	int winner = 0;
	int round_num = 0;
        int vowel_counter = 0;

	cout << "WHEEL OF FORTUNE" << endl;
	begin_game(players, rounds);
start: //repeats outside of round
	get_word(word, under);
loop: //repeats inside round
	cout << "Player " << player_turn << ": Would you like to 1) buy a vowel 2) spin the wheel or 3) guess the message?" << endl;
	cin >> i;
        if (i == 1) { //vowel function
                        vowel_start(word, under, wheel_value, player_turn, bank1, bank2, bank3, vowel_counter);
                goto loop;
	}
        if (i == 2) { //spins wheel and asks for letter guess
                int wheel_value = wheel_spin(player_turn, bank1, bank2, bank3, word, under);
                if (wheel_value != 0 && wheel_value != 21)
			guess_letter(word, under, wheel_value, player_turn, bank1, bank2, bank3);
		if (player_turn > players)
			player_turn = 1;
		goto loop;
	}
        if (i == 3) { //allows for guess word
		if (guess_word(word, under, player_turn, bank1, bank2, bank3, winner, players) == false)
			goto loop;
		if (game_bank(bank1, bank2, bank3, game_bank1, game_bank2, game_bank3, winner, round_num, rounds, player_turn) == true) {
			return 0;
		}
		goto start;
	}
        return 0;
}
