#include "main.hpp"

// macros
std::vector<std::string> split(std::string s, std::string delimiter, int splits=-1);



std::string f1_path = "res/working.txt";
std::string f2_path = "res/younes.txt";

std::vector<std::string> f_paths;

int main(int argc, char *argv[]) {
	int chunks = 0;
	int chunk_counter = 0;
	if (argc == 1) {
		std::cout << "Usage: linediff [--chunks num] FILE..." << std::endl;
		exit(-1);
	}
	if (!strcmp(argv[1], "--chunks")) {
		if (argc == 2)
		{
			std::cout << "Usage: linediff [--chunks num] FILE..." << std::endl;
			exit(-1);
		}
		chunks = std::atoi(argv[2]);
		if (chunks < 0)
		{
			std::cout << "Chunks must be a positive number" << std::endl;
			exit(-1);
		}
		else if (chunks == 0)
		{
			std::cout << "Chunks must not be 0" << std::endl;
			std::cout << "Usage: linediff [--chunks num] FILE..." << std::endl;
			exit(-1);
		}
	}
	int file_sum = argc - (chunks ? 3 : 1);
	// print info
	//std::vector<std::string> splitted_f1 = split(f1_path, "/");
	//std::vector<std::string> splitted_f2 = split(f2_path, "/");
	//std::cout << "Comparing " << splitted_f1[splitted_f1.size() -1];
	//std::cout << " and " << splitted_f2[splitted_f2.size() -1] << '.';
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << "Main file is " << BOLDWHITE << splitted_f1[splitted_f1.size() -1] << RESET;
	//std::cout << " which means it will be displayed before the second file";
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	
	std::vector<std::ifstream*> f_streams;
	std::vector<std::stringstream*> s_streams;
	std::vector<std::string*> linebufs;
	std::vector<bool> eofs;

	for (int i = (chunks ? 3 : 1); i < argc; i++) {
		std::ifstream* f1 = new std::ifstream(argv[i]);
		f_streams.push_back(f1);

		std::stringstream* s_stream = new std::stringstream;
		(*s_stream) << f1->rdbuf();
		s_streams.push_back(s_stream);
	
		std::string* f1_str = new std::string;
		linebufs.push_back(f1_str);

		eofs.push_back(false);
	}

	int row = 0;
	bool compActive = true;
	unsigned long int linelen_tot = 0;
	while (compActive) {
		// fill outbufs
		std::vector<std::string*> outbufs;
		for (int i = 0; i < file_sum; i++) {
			std::string* s = new std::string;
			outbufs.push_back(s);
		}
		// fetch lines from files
		for (int i = 0; i < file_sum; i++) {
			if (std::getline(*s_streams[i], *linebufs[i], '\n')) {
				// pass, todo fix this
			} else {
				// update eofs
				eofs[i] = true;
			}
		}
		// check so files aren't eof, if they are, quit
		compActive = false;
		for (int j = 0; j < file_sum; j++) {
			if (eofs[j] == false) {
				compActive = true;
				break;
			}
		}
		if (!compActive)
			break;
		row++;
		std::string leftBuf = "";
		for (unsigned long int i = 0; i < 3 - std::to_string(row).length(); i++)			leftBuf += ' ';

		for (std::string* s : outbufs)
			*s += leftBuf + std::to_string(row) + " |";

		linelen_tot = outbufs[0]->length();
		
		long unsigned int line_len = 0;
		for (std::string* l : linebufs) {
			if (line_len < l->length())
				line_len = l->length();
		}

		linelen_tot += line_len;

		// compare
		for (long unsigned int i = 0; i < line_len; i++) {
			// get first char
			bool equal = true;
			char firstChar = 0;
			for (int j = 0; j < file_sum; j++) {
				if (eofs[j] == false) {
					if (i > linebufs[j]->length())
						continue;
					firstChar = (*linebufs[j])[i];
					break;
				}
			}
			if (firstChar == 0)
				break;
			for (int j = 0; j < file_sum; j++) {
				if (eofs[j] == true) // if file is eof
					continue;
				if (i > linebufs[j]->length()) // if row is out
					continue;
				if ((*linebufs[j])[i] != firstChar) { // if diff
					equal = false;
					break;
				}
			}
			
			// assign colors
			for (int j = 0; j < file_sum; j++) {
				if (eofs[j] == true) // if file is eof
					continue;
				if (i > linebufs[j]->length()) // if row is out
					continue;
				if (equal)
					*outbufs[j] += GREEN;
				else
					*outbufs[j] += RED;
				// add chars

				*outbufs[j] += (*linebufs[j])[i];
				// reset for next character
				*outbufs[j] += RESET;
			}
		}

		// print the new lines
		for (std::string* s : outbufs)
			std::cout << *s << std::endl;
		std::cout << std::endl;

		// Draw chunk borders
		if (chunks)
		{
			if (++chunk_counter >= chunks)
			{
				std::cout << BOLDRED;
				std::cout << " " + std::to_string((row / chunks) - 1) + "^ ";
				for (long unsigned int i = 0; i < linelen_tot - std::to_string(row / chunks).length() - std::to_string((row / chunks) - 1).length() - 6; i++)
				{
					std::cout << '#';
				}
				std::cout << " " + std::to_string(row / chunks) + "v ";
				std::cout << RESET << std::endl << std::endl;
				chunk_counter = 0;
			}
		}
	}
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
