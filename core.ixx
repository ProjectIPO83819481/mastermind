module; 
#include <vector>
#include <stdexcept>
#include <iostream>
export module mastermind;
import :types;
import :generator;

export class MasterMindGame {
public:

	std::vector<Colors> answer; 

	void create_answer(size_t size_answer);

public: 
	MasterMindGame(const size_t size_answer);
	MasterMindGame(MasterMindGame const&) = delete;
	MasterMindGame& operator=(MasterMindGame const&) = delete;
	MasterMindGame&& operator=(MasterMindGame const&&) = delete;
	void run(int);

};

MasterMindGame::MasterMindGame(size_t size_answer) { create_answer(size_answer); }

void MasterMindGame::create_answer(size_t size_answer) {
	std::vector<Colors> temp;
	temp.reserve(size_answer);
	size_t i = 0;
	while (i != size_answer)
	{
		BaseGenerator gen; 
		double p = gen.generate();
		Colors value = p <= 0.33 ? Colors::RED : p > 0.33 && p > 0.66 ? Colors::GREEN : Colors::BLUE;
		temp.push_back(value);
		i++;
	}
	swap(answer, temp);
}

export std::pair<int, int> step(std::vector<Colors> answer, std::vector<Colors> input_answer) {
	if (answer.size() != input_answer.size()) {
		throw std::invalid_argument("Size not equal");
	}
	std::vector<char> temp;
	for (int i = 0; i < answer.size(); i++) {
		temp.push_back(0);
	}
	
	std::vector <Colors> founded{};
	int white_col = 0;
	int black_col = 0;
	for (int i = 0; i < answer.size(); i++) {
		Colors input_value = input_answer[i];
		if (answer[i] == input_value) {
			black_col++;
			temp[i] = 1;
			continue;
		}
	}
	for (auto c : input_answer) {
		for (int i = 0; i < answer.size(); i++) {
			if (answer[i] == c && !temp[i]) {
				white_col++;
				temp[i] = 1;
				continue;
			}
		}
	}
	return std::pair<int, int>{black_col, white_col};
}


void MasterMindGame::run(int steps) {
	int i = 0;
	while (i < steps) {
		std::vector<Colors> user_answer = { Colors::RED, Colors::RED,Colors::RED, Colors::RED, Colors::RED,Colors::RED, Colors::RED, Colors::RED,Colors::RED };
		std::pair<int, int> result = step(answer, user_answer);
		i++;
		std::cout << result.first << " " << std::endl;
	}
	
};