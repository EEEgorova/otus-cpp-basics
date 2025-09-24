#include <string>
#include <vector>

enum Style {
	short_phrase,
	whole_line
};

struct GrepResult {
	std::vector<size_t> positions;
	Style style = short_phrase;
	std::vector<std::string> words;
	std::string whole_line;
};

std::vector<int> ShiftCalc(const std::string& pattern) {
	size_t patternSize = pattern.size();
	std::vector<int> suffshift(patternSize + 1, patternSize); // suffix table
	std::vector<int> z(patternSize, 0); // z-function
	
	for (int j = 1, maxZidx = 0, maxZ = 0; j < patternSize; ++j) {
		if (j <= maxZ) 
			z[j] = std::min(maxZ - j + 1, z[j - maxZidx]);
		
		while (j + z[j] < patternSize && pattern[patternSize - 1 - z[j]] == pattern[patternSize - 1 - (j + z[j])]) {
			z[j]++; 
		}
		
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}
	
	for (int j = patternSize - 1; j > 0; j--) {
		suffshift[patternSize - z[j]] = j;
	}
	
	for (int j = 1, r = 0; j <= patternSize - 1; j++) { 
		if (j + z[j] == patternSize) {
			for (; r <= j; r++) {
				if (suffshift[r] == patternSize) suffshift[r] = j;
			}
		}
	}
	return suffshift;
 }

size_t FindNextOccurrence(const std::string& line, const std::string& pattern, size_t curPos, const std::vector<int> & suffshift) {
	size_t patternSize = pattern.size();
	size_t lineSize = line.size();
	for (int i = curPos, j = 0; i <= lineSize - patternSize && j >= 0; i += suffshift[j + 1]) {
		for (j = patternSize - 1; j >= 0 && pattern[j] == line[i + j]; j--);
		if (j < 0) 
			return i;
	}

	return std::string::npos;
}

std::string ProssesShortPhrase(const std::string& line, size_t patternSize, size_t & curPos) {
	size_t pos = curPos;
	while (line[pos] != ' ') {
		if (pos == 0)
			break;
		pos -= 1;
	}

	if (line[pos] == ' ')
		++pos;

	std::string word;
	for (size_t i = pos; i < curPos + patternSize; ++i) {
		word.push_back(line[i]);

	}

	pos = curPos + patternSize;

	if (pos < line.size() - 1) {
		while (line[pos] != ' ') {
			word.push_back(line[pos]);
			if (pos + 1 == line.size())
				break;
			++pos;
		}
	}
	curPos = pos;
	return word;
}

bool ProssesLine(const std::string& line, const std::string& pattern, GrepResult& result) {
	if (pattern.empty() || line.empty())
		return false;
	
	GrepResult searchRes;

	std::vector<int> shift = ShiftCalc(pattern);
	size_t startPos = FindNextOccurrence(line, pattern, 0, shift);
	while (startPos != std::string::npos) {
		result.positions.push_back(startPos);
	    result.words.push_back( ProssesShortPhrase(line, pattern.size(), startPos) );
		
		startPos = FindNextOccurrence(line, pattern, startPos + 1, shift);
	}
	
	if (result.style == whole_line && !result.words.empty())
		result.whole_line = line;

	return !result.words.empty();
}