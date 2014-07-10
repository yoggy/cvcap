#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

// parameters
int image_width;
int image_height;
std::string image_filename;

bool optparse(int argc, char *argv[])
{
	namespace po = boost::program_options;
	po::options_description opt("cvcap options");
	opt.add_options()
		("help,h", "show help")
		("resolution,r", po::value<std::string>()->default_value("640x480"), "resolution")
		("filename,f", po::value<std::string>()->default_value("image.jpg"), "capture image filename");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, opt), vm);

	if (vm.count("help")) {
		std::cerr << opt << std::endl;
		return false;
	}

	image_filename  = vm["filename"].as<std::string>();

	// parse resolution string
	std::string resolution_str = vm["resolution"].as<std::string>();
	std::vector<std::string> res;
	boost::split(res, resolution_str, boost::is_any_of("x"));
	if (res.size() != 2) {
		std::cerr << "error : invalid resolution format string..."  << std::endl;
		std::cerr << opt << std::endl;
		return false;
	}
	image_width  = boost::lexical_cast<int>(res[0]);
	image_height = boost::lexical_cast<int>(res[1]);

	return true;
}

int main(int argc, char *argv[]) 
{
	if (optparse(argc, argv) == false) return 1;

	cv::VideoCapture capture;
	if (capture.open(0) == false) {
		std::cerr << "error : capture.open(0)" << std::endl;
		return 1;
	}

	cv::Mat capture_img;

	// dummy capture (for auto iris...)
	for (int i = 0; i < 30; ++i) {
		capture >> capture_img;
	}

	capture >> capture_img;

	// resize
	cv::Mat resized_img;
	cv::resize(capture_img, resized_img, cv::Size(image_width, image_height));
	if (cv::imwrite(image_filename.c_str(), resized_img) == false) {
		std::cerr << "error : failed to cv::imwrite()...filename=" << image_filename << std::endl;
		return 1;
	}

	std::cerr << "info : image capture completed...filename=" << image_filename << std::endl;

	return 0;
}
