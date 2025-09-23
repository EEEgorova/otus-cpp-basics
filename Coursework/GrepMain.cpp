#include <iostream>
#include <fstream>

#include "LineProssesing.h"

int main(int argc, const char* argv[]) {

	std::cout << "1 - short phrase, 2 - whole line " << std::endl;
	int code;
	std::cin >> code;

	Style style = code == 1 ? short_phrase : whole_line;

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
		
		if (ProssesLine(line, argv[2], res)) {
			if (style == short_phrase) {
				for (const auto& word : res.words) {
					std::cout << word << " ";
				}
				std::cout << std::endl;
			}
			else {
				std::cout << res.whole_line << std::endl;
			}
		}
		else {
			std::cout << "No words found" << std::endl;
		}
	}
}


//отладочная информация, будет удалена перед сдачей
/* 
int main() {

	int argc = 3;
	const char* argv[] = { "GrepMain.cpp", "testFile.txt", "the pro"};

	NOmain(argc, argv);

}*/