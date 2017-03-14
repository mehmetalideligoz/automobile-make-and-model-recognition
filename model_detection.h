#include "opencv2/xfeatures2d.hpp"
#include "opencv2/ml/ml.hpp"
#include <vector>

class ModelDetection{

public:
	ModelDetection();
	ModelDetection(std::string &svm_file_name, std::string &vocabulary_file_name);
	void set_image(cv::Mat &image);
	int detect_model();


private:
	cv::Mat dictionary;
	cv::Mat input_image;
	cv::Ptr<cv::ml::SVM> svm;
	std::vector<cv::KeyPoint> keypoints;
	cv::Mat bow_descriptor;
};
