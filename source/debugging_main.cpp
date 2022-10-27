#include "comp6771/word_ladder.hpp"

//#include <ranges>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

template<typename T>
void print_vectors(std::vector<T> vec) {
	while (!vec.empty()) {
		T v = vec.back();
		std::cout << "vector of items : [";
		std::copy(std::begin(v), std::end(v), std::ostream_iterator<std::string>(std::cout, " "));
		std::cout << "]";
		vec.pop_back();
	}
}

auto main() -> int {
	auto const english_lexicon = word_ladder::read_lexicon("/tmp_amd/adams/export/adams/3/z5164744/Desktop/COMP6771/ass1/test/word_ladder/english.txt");
	auto const ladders = ::word_ladder::generate("fly", "sky", english_lexicon);

	print_vectors(ladders);
	std::cout << ladders.size() << std::endl;
	;
}
