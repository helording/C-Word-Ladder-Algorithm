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

This group of tests aim to test the most basic scenarios and algormithic correctness. For example
empty file test, testing failure scenarios and testing path navigation etc.

To ensure the algorithm could be tested accurately, specific lexicons were made for each use-case
that can be found in the "testicons" folder in the test folder (tests accessed through word
ladder folder due to CMake).
*/

TEST_CASE("Basic Tests") {
	SECTION("Empty") {
		auto const lexicon = word_ladder::read_lexicon("Empty.txt");
		auto const ladders = word_ladder::generate("a", "z", lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Failure Zero Hops") {
		auto const lexicon = word_ladder::read_lexicon("MultipleHopsFailure.txt");
		auto const ladders = word_ladder::generate("aaa", "zzz", lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Failure After Hops") {
		auto const lexicon = word_ladder::read_lexicon("ZeroHopsFailure.txt");
		auto const ladders = word_ladder::generate("aa", "zz", lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Successfully Finds Basic Path") {
		auto const lexicon = word_ladder::read_lexicon("OnePathSuccess.txt");
		auto const ladders = word_ladder::generate("aaa", "zzz", lexicon);

		CHECK(std::size(ladders) == 1);

		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"aaa", "aaz", "azz", "zzz"})
		      == 1);
	}

	SECTION("Path of Single Letter Words, Avoid Incorrect Destinations") {
		auto const lexicon = word_ladder::read_lexicon("SingleLetterWordsPath.txt");
		auto const ladders = word_ladder::generate("a", "b", lexicon);

		CHECK(std::size(ladders) == 1);

		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"a", "b"}) == 1);
		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"a", "c"}) != 1);
		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"a", "d"}) != 1);
		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"a", "e"}) != 1);
		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"a", "f"}) != 1);
	}

	SECTION("No Loops Created, No Repeats, No Oversteps, Full-Path Returned, Path of Longer Word "
	        "Length") {
		auto const lexicon = word_ladder::read_lexicon("NoLoops.txt");
		auto const ladders = word_ladder::generate("aaaaa", "bbbaa", lexicon);

		CHECK(std::size(ladders) == 1);

		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"aaaaa", "baaaa", "bbaaa", "bbbaa"})
		      == 1);

		SECTION("Don't Relook At Words, No Loops") {
			CHECK(std::count(ladders.begin(),
			                 ladders.end(),
			                 std::vector<std::string>{"aaaaa", "gaaaa", "baaaa", "bbaaa", "bbbaa"})
			      != 1);
			CHECK(std::count(
			         ladders.begin(),
			         ladders.end(),
			         std::vector<std::string>{"aaaaa", "baaaa", "gaaaa", "baaaa", "bbaaa", "bbbaa"})
			      != 1);
		}

		SECTION("No Oversteps") {
			CHECK(std::count(ladders.begin(),
			                 ladders.end(),
			                 std::vector<std::string>{"aaaaa", "bbaaa", "bbbaa"})
			      != 1);
			CHECK(std::count(ladders.begin(),
			                 ladders.end(),
			                 std::vector<std::string>{"aaaaa", "baaaa", "bbbaa"})
			      != 1);
		}

		SECTION("Partial Paths Not Returned") {
			CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"aaaaa", "bbbaa"})
			      != 1);
			CHECK(std::count(ladders.begin(),
			                 ladders.end(),
			                 std::vector<std::string>{"baaaa", "bbaaa", "bbbaa"})
			      != 1);
			CHECK(std::count(ladders.begin(),
			                 ladders.end(),
			                 std::vector<std::string>{"aaaaa", "baaaa", "bbaaa"})
			      != 1);
			CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"baaaa", "bbaaa"})
			      != 1);
		}
	}
}