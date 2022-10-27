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
		std::unordered_set<std::string> layer_words_found {from};
		std::vector<std::vector<std::string>> ladders {};

		std::vector<std::vector<std::string>> intersections {};


		std::queue<std::vector<std::string>> q {};
		q.push(std::vector<std::string> {from});


		size_t layer = 0;
		while (!q.empty()) {
			auto lad = q.front();
			q.pop();

			if (layer != lad.size()) {
				words_checked.insert(layer_words.begin(), layer_words.end());
				layer_words.clear();
				layer_words_found.clear();
				++layer;
			}

			if (lad.back() == to) {
				return rebuild_ladders(lad, intersections);
			}

			std::for_each(alp.begin(), alp.end(), [&](auto& c) {
				auto from_copy = lad.back();;
				std::for_each(from_copy.begin(), from_copy.end(), [&](auto& fc){
					char tmp = fc;
					fc = c;
					if (layer_words_found.find(from_copy) != words_checked.end()) {
						auto lad_copy = lad;
						lad_copy.push_back(from_copy);
						intersections.push_back(lad_copy);
					} else if (words_checked.find(from_copy) == words_checked.end()) {
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
					layer_words_found.insert(s);
				} else {
					words_checked.insert(s);
				}
			});

			layer_words.insert(layer_words.end(), words_to_check.begin(), words_to_check.end());
			words_to_check.clear();

		};

		return ladders;
	}

	// Rebuild paths that intersected the ladder found
	auto rebuild_ladders(std::vector<std::string>& ladder,
	                     std::vector<std::vector<std::string>>& intersections)
	   -> std::vector<std::vector<std::string>> {
		auto word_ladders = std::vector<std::vector<std::string>>{};
		auto ladders_to_check = std::queue<std::vector<std::string>>{};

		word_ladders.push_back(ladder);
		ladders_to_check.push(ladder);

		/* Check if there are any intersections between a word_ladder and prefixes in
		intersecting_paths list. If there is, reconstruct word_ladder, adding it to queue to
		also be checked*/
		while (!ladders_to_check.empty()) {
			auto next_result = ladders_to_check.front();
			ladders_to_check.pop();
			for (auto& intersection : intersections) {
				auto found = std::find(next_result.begin(), next_result.end(), intersection.back());
				if (found != next_result.end()) {
					auto new_result = std::vector<std::string>{intersection};
					new_result.insert(new_result.end(), ++found, next_result.end());

					if (std::find(word_ladders.begin(), word_ladders.end(), new_result)
					    == word_ladders.end()) {
						word_ladders.push_back(new_result);
						ladders_to_check.push(new_result);
					}
				}
			};
		}

		std::sort(word_ladders.begin(),
		          word_ladders.end(),
		          [](std::vector<std::string> x, std::vector<std::string> y) { return x < y; });

		return word_ladders;
	}

} // namespace word_ladder