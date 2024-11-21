#include "../include/LidarDriver.h"

LidarDriver::LidarDriver::LidarDriver(double degrees) {
	angular_res=degrees;
	dim = int((180/angular_res + 1))*BUFFER_DIM;
	head = 0;
	tail = 0;
	buff=nullptr;
}

void LidarDriver::LidarDriver::new_scan(std::vector<double>& scan) {
	if(buff==nullptr) buff = new double[dim];
	
	
} 

std::vector<double> LidarDriver::LidarDriver::get_scan() {
	if(buff==nullptr) return std::vector<double>{0};
	
	//save old scan
	std::vector<double> r;
	
	for(int i=head*dim;i<(head+1)*dim;i++) {
		r.push_back(buff[i]);
	}
	
	//delete old scan
	head = (head+1)%BUFFER_DIM;
	
	return r;
}

void LidarDriver::LidarDriver::clear_buffer() {
	delete[] buff;
	buff = nullptr;
}

double LidarDriver::LidarDriver::get_distance(double degrees) const {
	if(buff==nullptr) return 0;
	
	int index = tail*BUFFER_DIM + int(angular_res/degrees);
	
	return buff[index];
}
