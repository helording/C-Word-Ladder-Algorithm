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

The most complex scenarios that the algorithm can encourter occur when there are multiple word
ladders for the query words. Additionally the final algorithm, to achieve desired performance, would
need to have optimisations to avoid repeated searching, occuring when multiple paths to destination
word intersected at eariler points/words.

In these scenarios the algorithms would need to avoid investigating the same future words after an
intersection of two paths. With this in mind, interest was taken in ensuring algorithmic correctness
in general and in these complex scenarios with multiple paths where issues are likely to occur.

To ensure the algorithm could be tested accurately, specific lexicons were made for each use-case
that can be found in the "testicons" folder in the test folder (tests accessed through word
ladder folder due to CMake).
*/

TEST_CASE("Complex / Multiple Path Scenarios") {
	SECTION("Basic Mutliple Paths Test (2 Paths)") {
		auto const lexicon = word_ladder::read_lexicon("BasicMultiplePathsSuccess.txt");
		auto const ladders = word_ladder::generate("aaa", "acb", lexicon);

		CHECK(std::size(ladders) == 2);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"aaa", "aab", "acb"})
		      == 1);
		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"aaa", "aca", "acb"})
		      == 1);
	}

	SECTION("Intersection Before Destination") {
		auto const lexicon = word_ladder::read_lexicon("MultiplesPathsWithDoubleUps.txt");
		auto const ladders = word_ladder::generate("aaaaaa", "zzaaaz", lexicon);

		CHECK(std::size(ladders) == 3);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "aacaaa", "zacaaa", "zacaaz", "zaaaaz", "zzaaaz"})
		      == 1);
		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "aaadaa", "zaadaa", "zaadaz", "zaaaaz", "zzaaaz"})
		      == 1);
		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "aaaaea", "zaaaea", "zaaaez", "zaaaaz", "zzaaaz"})
		      == 1);
	}

	SECTION("Two Groups of Paths Reaching Destination Word") {
		auto const lexicon = word_ladder::read_lexicon("BasicEmbeddedDubUps.txt");
		auto const ladders = word_ladder::generate("aaaaaa", "zaaazz", lexicon);

		CHECK(std::size(ladders) == 4);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "abaaaa", "zbaaaa", "zbaaaz", "zaaaaz", "zaaazz"})
		      == 1);
		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "acaaaa", "zcaaaa", "zcaaaz", "zaaaaz", "zaaazz"})
		      == 1);
		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "aazaaa", "aazaaz", "zazaaz", "zaaaaz", "zaaazz"})
		      == 1);
		CHECK(std::count(
		         ladders.begin(),
		         ladders.end(),
		         std::vector<std::string>{"aaaaaa", "aazaaa", "aazaaz", "zazaaz", "zazazz", "zaaazz"})
		      == 1);
	}

	SECTION("Multiple Intersections Along Path") {
		auto const lexicon = word_ladder::read_lexicon("ComplexCollidingPaths.txt");
		auto const ladders = word_ladder::generate("GOAL", "QUIZ", lexicon);

		CHECK(std::size(ladders) == 8);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAD",
		                                          "GOLD",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "VELE",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "RAIN",
		                                          "RAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAD",
		                                          "GOLD",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "VELE",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "RAIN",
		                                          "RAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAD",
		                                          "GOLD",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "MELL",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "LAIN",
		                                          "LAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAD",
		                                          "GOLD",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "MELL",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "LAIN",
		                                          "LAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);

		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAF",
		                                          "GOLF",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "VELE",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "RAIN",
		                                          "RAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAF",
		                                          "GOLF",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "VELE",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "RAIN",
		                                          "RAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAF",
		                                          "GOLF",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "MELL",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "LAIN",
		                                          "LAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"GOAL",
		                                          "GOAF",
		                                          "GOLF",
		                                          "GOLE",
		                                          "MOLE",
		                                          "MELE",
		                                          "MELL",
		                                          "VELL",
		                                          "VEIL",
		                                          "VEIN",
		                                          "VAIN",
		                                          "LAIN",
		                                          "LAID",
		                                          "SAID",
		                                          "SLID",
		                                          "SLIT",
		                                          "SUIT",
		                                          "QUIT",
		                                          "QUIZ"})
		      == 1);
	}
}