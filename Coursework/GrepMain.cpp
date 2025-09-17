#include <iostream>
#include <fstream>
#include <string>


struct GrepResult {
	size_t position;
	int style; // 1-one word; 2-line
	std::string words;

};

void ProssesLine(const std::string & line, const std::string & pattern, GrepResult & result) {
	auto startPos = line.find(pattern);
	if ( startPos != std::string::npos) {
		result.position = startPos;
		
		if (result.style == 1) {
			
			size_t pos = startPos;
			while (pos > 0 && line[pos] != ' ') {
				pos -= 1;
			}
			
			for (size_t i = pos; i < startPos + pattern.size(); ++i) {
				result.words.push_back(line[i]);

			}
			pos = startPos + pattern.size();
			while (pos > line.size() && line[pos] != ' ') {
				result.words.push_back(line[pos]);
				++pos;
			}
			
		}
		else{
			result.words = line;
		}
	}
	else {
		result.position = -1;
	}
	return;
}

int main(int argc, const char* argv[]) {

	
	std::cout << "1 - short phrase, 2 - whole line " << std::endl;
	int style = 0;
	std::cin >> style;

	std::ifstream input;          
	input.open(argv[1]);
	if (!input.is_open())
	{
		std::cout << "no file" << std::endl; 
		return 1;
	}
	
	std::string line;
	while (std::getline(input, line))
	{
		
		GrepResult res;
		res.style = style;
		ProssesLine(line, argv[2], res);
		if (res.position != -1) {
			std::cout << res.words << std::endl;
			
		}
	}

	input.close();
}


//отладочная информация, будет удалена перед сдачей
/* 
int main() {

	int argc = 3;
	const char* argv[] = { "GrepMain.cpp", "testFile.txt", "the pro"};

	NOmain(argc, argv);

}*/