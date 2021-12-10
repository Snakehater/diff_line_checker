#include "main.hpp"

// macros
std::vector<std::string> split(std::string s, std::string delimiter, int splits=-1);



std::string f1_path = "res/working.txt";
std::string f2_path = "res/expired.txt";

int main(){
	// print info
	std::vector<std::string> splitted_f1 = split(f1_path, "/");
	std::vector<std::string> splitted_f2 = split(f2_path, "/");
	std::cout << "Comparing " << splitted_f1[splitted_f1.size() -1];
	std::cout << " and " << splitted_f2[splitted_f2.size() -1] << '.';
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Main file is " << BOLDWHITE << splitted_f1[splitted_f1.size() -1] << RESET;
	std::cout << " which means it will be displayed before the second file";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	std::ifstream f1(f1_path);
	std::ifstream f2(f2_path);

	std::stringstream f1_stream;
	std::stringstream f2_stream;
	f1_stream << f1.rdbuf();
	f2_stream << f2.rdbuf();

	std::string f1_str;
	std::string f2_str;

	int row = 0;
	while (std::getline(f1_stream, f1_str, '\n') &&
		std::getline(f2_stream, f2_str, '\n')) {
		row++;
		std::string leftBuf = "";
		for (unsigned long int i = 0; i < 3 - std::to_string(row).length(); i++)
			leftBuf += ' ';
		std::string f1LineOut = leftBuf + std::to_string(row) + " |";
		std::string f2LineOut = leftBuf + std::to_string(row) + " |";
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



std::vector<std::string> split(std::string s, std::string delimiter, int splits){
	std::vector<std::string> output;
	
	size_t pos = 0;	
	int i = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos && i != splits) {
		token = s.substr(0, pos);
		output.push_back(token);
		s.erase(0, pos + delimiter.length());
		i++;
	}
	// add the rest of the string to last element
	output.push_back(s);
	return output;
}
