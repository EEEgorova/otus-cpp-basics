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
	if (pattern.empty())
		return false;
	
	GrepResult searchRes;

	size_t startPos = line.find(pattern);
	while (startPos != std::string::npos) {
		result.positions.push_back(startPos);
	    result.words.push_back( ProssesShortPhrase(line, pattern.size(), startPos) );
		
		startPos = line.find(pattern, startPos + 1);
	}
	
	if (result.style == whole_line && !result.words.empty())
		result.whole_line = line;

	return !result.words.empty();
}