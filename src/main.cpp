#include "main.hpp"

std::string f1_path = "res/working.txt";
std::string f2_path = "res/expired.txt";

int main(){
	std::ifstream f1(f1_path);
	std::ifstream f2(f2_path);

	std::stringstream f1_stream;
	std::stringstream f2_stream;
	f1_stream << f1.rdbuf();
	f2_stream << f2.rdbuf();

	std::string f1_str;
	std::string f2_str;
	while (std::getline(f1_stream, f1_str, '\n') &&
		std::getline(f2_stream, f2_str, '\n')) {
		std::string f1LineOut = "";
		std::string f2LineOut = "";
		unsigned long int i = 0;
		for (i = 0; i < f1_str.length() && i < f2_str.length(); i++) {
			if (f1_str[i] == f2_str[i]) {
				f1LineOut += GREEN;
				f2LineOut += GREEN;
			} else {
				f1LineOut += RED;
				f2LineOut += RED;
			}
			f1LineOut += f1_str[i];
			f2LineOut += f2_str[i];
		}
		f1LineOut += RESET;
		f2LineOut += RESET;
		
		// f2_str is eof
		while (i < f1_str.length()) {
			f1LineOut += f1_str[i];
			i++;
		}
		// f1_str is eof
		while (i < f2_str.length()) {
			f2LineOut += f2_str[i];
			i++;
		}

		// print the new lines
		std::cout 	<< f1LineOut << std::endl
				<< f2LineOut << std::endl
				<< std::endl;
	}
	while (std::getline(f1_stream, f1_str, '\n'))
		std::cout << f1_str << std::endl;
	while (std::getline(f2_stream, f2_str, '\n'))
		std::cout << f2_str << std::endl;
}
