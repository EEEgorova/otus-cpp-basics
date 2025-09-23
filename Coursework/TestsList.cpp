#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "LineProssesing.h"

TEST(GrepTesting, EmptyLine) {
	std::string line = "";
	std::string pattern = " ";
	
	GrepResult searchRes;
	EXPECT_TRUE( !ProssesLine(line, pattern, searchRes) && searchRes.words.empty());
}

TEST(GrepTesting, Line) {
	std::string line = "In mathematics, the factorial of a non-negative integer b";
	
	std::vector<std::string> pattern(4);
	pattern[0] = "a"; 
	pattern[1] = "In";
	pattern[2] = "b"; 
	pattern[3] = "the fact"; 

	std::vector<GrepResult> res(pattern.size());
	res[0].words = { "mathematics," , "factorial", "a", "non-negative" };
	res[1].words = { "In" };
	res[2].words = { "b" };
	res[3].words = { "the factorial" };

	res[0].positions = { 4, 21, 33, 42 };
	res[1].positions = { 0 };
	res[2].positions = { 56 };
	res[3].positions = { 16 };

	for (size_t i = 0; i < pattern.size(); ++i) {
		GrepResult searchRes;
		bool tmp = ProssesLine(line, pattern[i], searchRes);
		EXPECT_TRUE( tmp && res[i].positions == searchRes.positions && res[i].words == searchRes.words);
	}
}

