//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <comp6771/word_ladder.hpp>

#include <string>
#include <vector>

#include <catch2/catch.hpp>

/*
The motivation behind the following tests was to incrementally test more complex scenarios of the
word ladder program. Tests spanned both the algorithm providing the correct output and also the
program avoiding problems that could arise.

Tests using the english lexicon are used to test known word ladders that are confirmed via the
assignment spec. Loosely, the purpose of these tests rather than to be relied upon for
implementation correctioness, are simply included for completeness and to test the algorithm against
a larger lexicon.
*/

TEST_CASE("Testing Known Results From English Lexicon") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");

	SECTION("awake -> sleep") {
		auto const ladders = word_ladder::generate("awake", "sleep", english_lexicon);

		CHECK(std::size(ladders) == 2);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"awake",
		                                          "aware",
		                                          "sware",
		                                          "share",
		                                          "sharn",
		                                          "shawn",
		                                          "shewn",
		                                          "sheen",
		                                          "sheep",
		                                          "sleep"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"awake",
		                                          "aware",
		                                          "sware",
		                                          "share",
		                                          "shire",
		                                          "shirr",
		                                          "shier",
		                                          "sheer",
		                                          "sheep",
		                                          "sleep"})
		      == 1);
	}

	SECTION("work -> play") {
		auto const ladders = word_ladder::generate("work", "play", english_lexicon);

		CHECK(std::size(ladders) == 12);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "fork", "form", "foam", "flam", "flay", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "pork", "perk", "peak", "pean", "plan", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "pork", "perk", "peak", "peat", "plat", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "pork", "perk", "pert", "peat", "plat", "play"})
		   == 1);

		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "pork", "porn", "pirn", "pian", "plan", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "pork", "port", "pert", "peat", "plat", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "word", "wood", "pood", "plod", "ploy", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "worm", "form", "foam", "flam", "flay", "play"})
		   == 1);

		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "worn", "porn", "pirn", "pian", "plan", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "wort", "bort", "boat", "blat", "plat", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "wort", "port", "pert", "peat", "plat", "play"})
		   == 1);
		CHECK(
		   std::count(ladders.begin(),
		              ladders.end(),
		              std::vector<std::string>{"work", "wort", "wert", "pert", "peat", "plat", "play"})
		   == 1);
	}
}
