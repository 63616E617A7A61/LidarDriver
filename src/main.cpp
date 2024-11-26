#include "../include/LidarDriver.h"
#include "../include/FileReader.h"
#include <iostream>
#include <cmath>
#include <cstdlib> 

// Function to generate a random number between min and max, rounded to two decimal places
double randomNum(double min, double max){
    double r = (double)rand() / RAND_MAX;
	double result = min + r * (max - min); 
	result = std::round(result * 100.0) / 100.0;
    return result;
}

// Function to generate a scan of 'n' random distances between 0 and 100
std::vector<double> generateScan(int n){
	std::vector<double> r;
	for (int i = 0; i < n; i++){
		r.push_back(randomNum(0, 100));
	}
	return r;
}

// Function to read scans from a file and pass them to the lidarDriver
void getScanFile(LidarDriver& lidarDriver, std::string file_path){
	FileReader fileReader(file_path); 
	std::vector<double> scan; 
	// Continue reading as long as there are more lines in the file
	while(fileReader.hasNextLine()){ 
		scan = fileReader.getNextLine(); 
		lidarDriver.new_scan(scan); 
	}
}

// Function to print the content of a vector
void printVect(std::vector<double> o){
	for(double i : o){
		std::cout << i << " ";
	}
}

int main() {
	LidarDriver lidarDriver(2); 
	int n = 91; 

	getScanFile(lidarDriver, "scan_file.txt"); 
	std::cout << "Scan da file caricati" << "\n\n\n"; 

	do{
		std::cout << "\n\n--------------------------------------------------------------" << std::endl; 
		std::cout << "AZIONI DISPONIBILI (digita numero corrispondente)" << std::endl; 
		std::cout << "1. Genera nuovo scan (e carica nel buffer)" << std::endl; 
		std::cout << "2. Leggi scan meno recente presente nel buffer" << std::endl; 
		std::cout << "3. Leggi la distanza misurata a un angolo specifico dello scan più recente" << std::endl; 
		std::cout << "4. Svuota buffer" << std::endl; 
		std::cout << "5. Termina programma" << std::endl; 
		std::cout << "--------------------------------------------------------------\n\n" << std::endl; 

		int scelta; 
		std::cout << "Inserisci azione: "; 
		std::cin >> scelta;

		switch (scelta)
		{
		case 1: {
			std::vector<double> scan = generateScan(n); 
			lidarDriver.new_scan(scan); 
			std::cout << "Scan aggiunto" << std::endl; 
			break;
		}

		case 2: 
			printVect(lidarDriver.get_scan()); 
			break;

		case 3: 
			std::cout << "Inserisci l'angolo di cui vuoi leggere la distanza misurata: "; 
			double degree;
			std::cin >> degree; 
			std::cout << lidarDriver.get_distance(degree) << std::endl; 
			break;

		case 4: 
			lidarDriver.clear_buffer(); 
			std::cout << "Buffer svuotato"; 
			break;
		
		case 5:
			std::cout << "Programma terminato." << std::endl;
			exit(0); 
			break;

		default:
			std::cout << "Opzione non valida. Terminazione del programma." << std::endl;
			exit(0); 
			break; 
			
	}
	} while(true); 

	return 0;
}