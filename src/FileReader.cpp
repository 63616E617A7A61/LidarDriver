#include "../include/FileReader.h"
#include <sstream>

// Constructor that takes the file path as an argument and opens the file
FileReader::FileReader(std::string file_path){
    file.open(file_path); 
}

// Method to read the next line from the file and return the values as a vector of doubles
std::vector<double> FileReader::getNextLine(){
	std::vector<double> scan; // Vector to store the numbers in the line
	std::string line; // String to hold the current line

    // If the file is not open, return an empty vector (all the lines has already been read)
	if(!file.is_open()){
		return scan; 
	}

    // Try to read a line from the file
	if(std::getline(file, line)){
		std::istringstream stream(line); // Create an input string stream from the line
        double value;

        // Read each value from the stream and add it to the vector
        while (stream >> value) {
            scan.push_back(value);
        }
	}
	else{
		file.close(); // If the line cannot be read, close the file (the file has ended)
	}

	return scan; 
}

// Method to check if there is another line to read from the file
bool FileReader::hasNextLine() {
    return file.peek() != EOF;  // (EOF is end of file)
}

