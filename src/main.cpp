#include "../include/LidarDriver.h"
#include <iostream>

double dRand(double min, double max){
    double r = (double)rand() / RAND_MAX;
    return min + r * (max - min);
}

void printVect(std::vector<double> o){
	for(double i : o){
		std::cout << i << " ";
	}
	std::cout << "\n---------------------------\n";
}

std::vector<double> generateScan(int n){
	std::vector<double> r;
	for (int i = 0; i < n; i++){
		r.push_back(dRand(0, 100));
	}
	return r;
}

int main() {
	LidarDriver ld(0.5);
	int nDati = 361;

	std::vector<double> a;

	for (int i = 0; i < 11; i++) {
		a = generateScan(nDati);
		std::cout << i << ":\n";
		printVect(a); 
		ld.new_scan(a);
	}

	printVect(ld.get_scan());

	std::cout << ld << "\n";

	std::cout << ld.get_distance(5) << "\n";

	return 0;
}