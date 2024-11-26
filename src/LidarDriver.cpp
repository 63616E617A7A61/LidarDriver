#include "../include/LidarDriver.h"

// Constructor to initialize the LidarDriver object with the given angular resolution 
LidarDriver::LidarDriver(double degrees) {
	angular_res = degrees;
	offset = int((180 / angular_res + 1)); // Calculate how many points a full scan will contain (180 degrees / angular resolution + 1)
	dim = offset * BUFFER_DIM; // Total size of the buffer (number of scans * points per scan)
	head = 0; // Initialize the head pointer (used to track where the oldest scan is located in the buffer)
	tail = 0; // Initialize the tail pointer (used to track where the latest scan is written in the buffer)
	buff = nullptr;
}

// Method to add a new scan to the buffer
void LidarDriver::new_scan(std::vector<double>& scan) {
	if(buff == nullptr) buff = new double[dim]; // If the buffer hasn't been allocated yet, allocate memory for it
	else{
		// If the buffer is full, remove the oldest scan to make space for the new one
		if((tail + 1) % BUFFER_DIM == head) get_scan(); 

		tail = (tail + 1) % BUFFER_DIM; // Increment the tail pointer (wrap around using modulo to create a circular buffer)
	}
	// Copy the new scan into the buffer
	for (int i = tail * offset; i < (tail + 1) * offset; i++) {
		int scan_index = i - (tail * offset); // Calculate the corresponding index in the scan vector
		if(scan_index < scan.size()){ // Check if the index is valid (within bounds of the scan vector)
			buff[i] = scan[i - (tail * offset)]; // If valid, copy the value from scan to the buffer
		}
		else{
			buff[i] = 0; // If invalid (scan is shorter), set the buffer value to 0
		}
	}
} 

// Method to retrieve the scan data at the head position (the oldest scan in the buffer)
std::vector<double> LidarDriver::get_scan() {
	if(buff == nullptr) return std::vector<double>{0}; // If the buffer is empty, return a vector containing a single 0
	
	std::vector<double> r; // Create a vector to store the retrieved scan data
	
	// Copy the scan data from the buffer (from the head position) to the vector
	for(int i = head * offset; i < (head + 1) * offset; i++) {
		r.push_back(buff[i]);
	}
	
	// Remove the oldest scan by advancing the head pointer (wrap around using modulo)
	head = (head + 1) % BUFFER_DIM;
	
	return r;
}

// Method to clear the buffer (deallocate memory)
void LidarDriver::clear_buffer() {
	delete[] buff;
	buff = nullptr;
}

// Method to retrieve the distance at a specific angle (in degrees) of the last scan 
double LidarDriver::get_distance(double degrees) const {
	if(buff==nullptr) return 0; // If the buffer is empty, return 0 as a default value
	
	int index = tail * offset + int(degrees/angular_res); // Calculate the index of the distance corresponding to the given angle

	if(index > offset) return 0; // if index exceed offset, return 0
	
	return buff[index];
}

// Overload of the stream insertion operator (<<) to print the current scan data
std::ostream& operator<<(std::ostream& out, const LidarDriver& ld) {
	// Loop through the data at the tail position in the buffer and print each value
	for (int i = ld.tail * ld.offset; i < (ld.tail + 1) * ld.offset; i++){ 
		out << ld.buff[i] << " "; 
	}
	return out; // Return the output stream
}

// Destructor to clean up the LidarDriver object
LidarDriver::~LidarDriver() { 
	// Call clear_buffer to deallocate the buffer when the object is destroyed
	clear_buffer();
}
