#ifndef _HANGMAN_HH_
#define _HANGMAN_HH_

#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>

class Game {
private:
	std::string word {};
	std::unordered_set<char> word_chars {};
	std::unordered_set<char> so_far_chars {};
	std::unordered_set<char> wrong_so_far {};
	size_t hangman_idx = 0;

	std::array<std::string, 35> words { 
		"hello",    "world", 	  "fritz",               "hobbit",  	"corki", 
		"forki",    "coding",     "sleep",               "python",  	"book",
		"haubitze", "hangman",    "programmieren",       "cola", 	"corgi", 
		"porinna",  "poperze",    "stupsnaeschen",       "beepboop",    "schifffahrtskapitaenskabinentuer",
		"syndrome", "subway", 	  "quiz",  		 "fluffy",      "aperol",
		"spritz",   "funny",      "hanebuechen", 	 "quidditch",   "ralf",
		"gollum",   "yuccapalme", "kernspintomographie", "burgverlies", "quarzuhr",
	};

	std::array<std::string, 11> hangman {
		"\n\n\n\n\n\n\n",
		"\n\n\n\n   / \\\n\n\n",
		"    |\n    |\n    |\n    |\n   / \\ \n\n\n",
		"    ______\n    |\n    |\n    |\n    |\n   / \\ \n\n\n",
		"    ______\n    |    |\n    |\n    |\n    |\n   / \\\n\n\n",
		"    ______\n    |    |\n    |    O\n    |\n    |\n   / \\\n\n\n",
		"    ______\n    |    |\n    |    O\n    |    |\n    |\n   / \\\n\n\n",
		"    ______\n    |    |\n    |    O\n    |    |\\\n    |\n   / \\\n\n\n",
		"    ______\n    |    |\n    |    O\n    |   /|\\\n    |\n   / \\\n\n\n",
		"    ______\n    |    |\n    |    O\n    |   /|\\\n    |     \\\n   / \\ \n\n\n", 
		"    ______\n    |    |\n    |    O\n    |   /|\\\n    |   / \\\n   / \\ \n\n\n" 
	};

	void random_word(void);
	void check_character(char guess);
	void draw_state(void);
	void draw_word(void);
	void you_won(void);
	void you_lost(void);

public:
	Game(bool debug_mode = false)
	{
		this->random_word();
		if (debug_mode) std::cerr << "My random word is " << this->word << '\n';
		for (size_t i = 0; i < this->word.size(); i++) {
			this->word_chars.insert(this->word[i]);
		}
	}

	void play(void);
};

template <typename T>
concept out_streamable = requires(T t, std::ostream& os) {
	{ os << t };
};

template <out_streamable T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& set)
{
	auto it { set.begin() };
	if (it == set.end()) { os << "{}"; return os; }

	os << '{' << (*it++);
	while (it != set.end()) {
		os << ", " << (*it);
		++it;
	}
	os << '}';
	return os;
}

#endif /* _HANGMAN_HH_ */
