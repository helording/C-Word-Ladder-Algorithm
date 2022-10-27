#include <comp6771/word_ladder.hpp>
#include <iterator>

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

template <typename T>
void print_collection(const T& collection){

    auto it = collection.begin();

    std::cout << " Collection [";
    while(it != collection.end()){
        std::cout << " " << *it ;
        ++it;
    }
    std::cout << "]" << std::endl;
}


namespace word_ladder {

	// Helper lambda
	// Finds if a two words are a "step"
	[[nodiscard]] auto generate(std::string const& from,
	                            std::string const& to,
	                            std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		(void)from;
		(void)to;
		(void)lexicon;

		// Creating new lexicon with words of the same length as query words
		auto words = std::unordered_set<std::string>{};
		std::copy_if(lexicon.begin(),
		             lexicon.end(),
		             std::inserter(words, words.begin()),
		             [&from](std::string s) { return (s.length() == from.length()); });

		// Variables for algorithm

		auto alp = std::vector<char> {'a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n','o','p',
		'q','r','s','t','u','v','w','x','y','z'};

		std::unordered_set<std::string> words_checked {};
		std::vector<std::string> words_to_check {};
		std::vector<std::string> layer_words {from};
		std::vector<std::vector<std::string>> ladders {};


		std::queue<std::vector<std::string>> q {};
		q.push(std::vector<std::string> {from});


		size_t layer = 0;
		while (!q.empty()) {
			auto lad = q.front();
			q.pop();

			if (layer != lad.size()) {
				words_checked.insert(layer_words.begin(), layer_words.end());
				layer_words.clear();
				++layer;
			}

			if (lad.back() == to) {
				ladders.push_back(lad);
				while (!q.empty()) {
					auto l = q.front();
					q.pop();
					if (l.back() == to) ladders.push_back(l);
				}

				std::sort(ladders.begin(),
		          ladders.end(),
		          [](std::vector<std::string> x, std::vector<std::string> y) { return x < y; });


				return ladders;
			}

			std::for_each(alp.begin(), alp.end(), [&](auto& c) {
				auto from_copy = lad.back();;
				std::for_each(from_copy.begin(), from_copy.end(), [&](auto& fc){
					char tmp = fc;
					fc = c;
					if (words_checked.find(from_copy) == words_checked.end()) {
						words_to_check.push_back(from_copy);
					}
					fc = tmp;
				});
			});


			std::for_each(words_to_check.begin(), words_to_check.end(), [&](auto& s){
				if (words.find(s) != words.end()) {
					auto lad_copy = lad;
					lad_copy.push_back(s);
					q.push(lad_copy);
				} else {
					words_checked.insert(s);
				}
			});

			layer_words.insert(layer_words.end(), words_to_check.begin(), words_to_check.end());
			words_to_check.clear();

		};

		return ladders;
	}

} // namespace word_ladder
