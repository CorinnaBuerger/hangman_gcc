#include <iostream>
#include <random>
#include <string>
#include <ctime>

#include "hangman.hh"

void Game::random_word(void)
{
	std::random_device rd;
	const auto seed { rd.entropy() ? rd() : time(nullptr) };
	std::mt19937 gen(seed);
	std::uniform_int_distribution<> dist(0, static_cast<int>(this->words.size()-1));

	size_t random_idx = dist(gen);
	this->word = words[random_idx];
}

void Game::check_character(char guess)
{
	if (this->word_chars.contains(guess)) {
		this->so_far_chars.insert(guess);
		std::cout << "You guessed right.\n\n";
	} else {
		std::cout << "You guessed wrong.\n\n";
		this->wrong_so_far.insert(guess);
		this->hangman_idx += 1;
	}
}

void Game::draw_state(void)
{
	std::string border = "  -----------------------------\n\n";
	std::cout << border << this->hangman[this->hangman_idx] << border;
}

void Game::draw_word(void)
{
	for (size_t i = 0; i < this->word.size(); i++) {
		if (this->so_far_chars.contains(this->word[i])) {
			std::cout << word[i] << ' ';
		} else {
			std::cout << "_ ";
		}
	}
	std::cout << "\n\n\n";
}

void Game::you_won(void)
{
	std::string won_str{ R"(
	  __   __                                _
	  \ \ / /                               | |
	   \ V /___  _   _  __      _____  _ __ | |
	    \ // _ \| | | | \ \ /\ / / _ \| '_ \| |
	    | | (_) | |_| |  \ V  V / (_) | | | |_|
	    \_/\___/ \__,_|   \_/\_/ \___/|_| |_(_)
	  )" };
	std::cout << won_str << "\n\n";
}

void Game::you_lost(void)
{
	std::string lost_str{ R"(
	  __   __            _           _   _ 
	  \ \ / /           | |         | | | |
	   \ V /___  _   _  | | ___  ___| |_| |
	    \ // _ \| | | | | |/ _ \/ __| __| |
	    | | (_) | |_| | | | (_) \__ \ |_|_|
	    \_/\___/ \__,_| |_|\___/|___/\__(_)
                                     
	  )" };
                                     

	std::cout << lost_str << "\n\n" << "The word was \"" << this->word << "\" (lol).\n\n";
}

void Game::play(void)
{
	bool player_won = true;
	while (this->word_chars.size() != this->so_far_chars.size()) {
		char guess;

		this->draw_word();
		std::cout << "Guess one or more characters (wrong so far: " 
			  << this->wrong_so_far << "): ";
		std::cin >> guess;
		this->check_character(guess);
		this->draw_state();

		if (this->hangman_idx == this->hangman.size()-1) {
			player_won = false;
			break;
		}
	}
	this->draw_word();
	if (player_won) this->you_won();
	else			this->you_lost();
}
