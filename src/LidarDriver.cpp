#include "../include/LidarDriver.h"
#include <iostream>

LidarDriver::LidarDriver::LidarDriver(double degrees) {
	angular_res = degrees;
	offset = int((180 / angular_res + 1));
	dim = offset * BUFFER_DIM;
	head = 0;
	tail = 0;
	buff = nullptr;
}

void LidarDriver::LidarDriver::new_scan(std::vector<double>& scan) {
	if(buff == nullptr) buff = new double[dim];
	else{
		//If the buffer is full, the oldest element should be deleted
		if((tail + 1) % BUFFER_DIM == head) get_scan(); 

		tail = (tail + 1) % BUFFER_DIM; 
	}
	for (int i = tail * offset; i < (tail + 1) * offset; i++) {
		buff[i] = scan[i - (tail * offset)];
	}
} 

std::vector<double> LidarDriver::LidarDriver::get_scan() {
	if(buff == nullptr) return std::vector<double>{0};
	
	//save old scan
	std::vector<double> r;
	
	for(int i = head * offset; i < (head + 1) * offset; i++) {
		r.push_back(buff[i]);
	}
	
	//delete old scan
	head = (head + 1) % BUFFER_DIM;
	
	return r;
}

void LidarDriver::LidarDriver::clear_buffer() {
	delete[] buff;
	buff = nullptr;
}

double LidarDriver::LidarDriver::get_distance(double degrees) const {
	if(buff==nullptr) return 0;
	
	int index = tail * offset + int(degrees/angular_res);
	
	return buff[index];
}

std::ostream& operator<<(std::ostream& out, const LidarDriver& ld) {
	for (int i = ld.tail * ld.offset; i < (ld.tail + 1) * ld.offset; i++){
		out << ld.buff[i] << " ";
	}
	return out;
}

LidarDriver::LidarDriver::~LidarDriver() {
	clear_buffer();
}