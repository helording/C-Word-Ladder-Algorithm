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
ladders for the query words. Additionally final algorithm, to achieve desired performance, would
need to have optimisations to avoid repeated searching, occuring when multiple paths to destination
word intersected at eariler points/words. In these scenarios the algorithms would need to avoid
investigating the same future words after an intersection of two paths. With this in mind interest
was taken in ensuring algorithmic correctness in general and correct output in complex scenarios
with multiple paths where issues are likely to occur.

To ensure the algorithm could be tested accurately, specific lexicons were made for each use-case
that can be found in the "testicons" folder in the test folder. Tests using the english lexicon are
also used to test known word ladders that are confirmed via the assignement spec. Loosely, the
purpose of these tests rather than to be relied upon for implementation correctioness, are simply
included for completeness and to test the algorithm against a larger lexicon.
*/

TEST_CASE("Basic Tests") {
	SECTION("Empty") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/Empty.txt");
		auto const ladders = word_ladder::generate("a", "z", english_lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Failure Zero Hops") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/MultipleHopsFailure.txt");
		auto const ladders = word_ladder::generate("aaa", "zzz", english_lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Failure After Hops") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/ZeroHopsFailure.txt");
		auto const ladders = word_ladder::generate("aa", "zz", english_lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Successfully Finds Basic Path") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/OnePathSuccess.txt");
		auto const ladders = word_ladder::generate("aaa", "zzz", english_lexicon);

		CHECK(std::size(ladders) == 1);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"aaa", "aaz", "azz", "zzz"})
		      == 1);
	}

	SECTION("No Loops Created, No Repeats, No Oversteps, Full-Path Returned") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/NoLoops.txt");
		auto const ladders = word_ladder::generate("aaaaa", "bbbaa", english_lexicon);

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

TEST_CASE("Complex / Multiple Path Scenarios") {
	SECTION("Basic Mutliple Paths Test (2 Paths)") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/"
		                                                       "BasicMultiplePathsSuccess.txt");
		auto const ladders = word_ladder::generate("aaa", "acb", english_lexicon);

		CHECK(std::size(ladders) == 2);
		CHECK(std::is_sorted(ladders.begin(), ladders.end()));

		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"aaa", "aab", "acb"})
		      == 1);
		CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"aaa", "aca", "acb"})
		      == 1);
	}

	SECTION("Intersection Before Destination") {
		auto const english_lexicon = word_ladder::read_lexicon("testicons/"
		                                                       "MultiplesPathsWithDoubleUps.txt");
		auto const ladders = word_ladder::generate("aaaaaa", "zzaaaz", english_lexicon);

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
		auto const english_lexicon = word_ladder::read_lexicon("testicons/BasicEmbeddedDubUps.txt");
		auto const ladders = word_ladder::generate("aaaaaa", "zaaazz", english_lexicon);

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
		auto const english_lexicon = word_ladder::read_lexicon("testicons/ComplexCollidingPaths.txt");
		auto const ladders = word_ladder::generate("GOAL", "QUIZ", english_lexicon);

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
