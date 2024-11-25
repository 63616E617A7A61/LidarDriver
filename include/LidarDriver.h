#ifndef LIDAR_DRIVER
#define LIDAR_DRIVER

#include <ostream>
#include <vector>

class LidarDriver {
	public:
		LidarDriver(double degrees);

		void new_scan(std::vector<double>& scan);
		std::vector<double> get_scan();
		void clear_buffer();
		double get_distance(double degrees) const;
		friend std::ostream& operator<<(std::ostream& out, const LidarDriver& ld);

		~LidarDriver();
	private:
		double angular_res;
		static const int BUFFER_DIM = 10;
		int dim;
		int tail, head;
		int offset;
		double* buff;

};

#endif
