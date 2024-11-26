#ifndef FILE_READER
#define FILE_READER 

#include <string>
#include <vector>
#include <fstream>

class FileReader{
    public: 
        FileReader(std::string file_path); 
        std::vector<double> getNextLine();  
        bool hasNextLine(); 
    
    private: 
        std::ifstream file; 
}; 

#endif