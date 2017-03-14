#include <opencv2/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include <chrono>
#include <vector>
#include <stdio.h>
#include <iostream>

class KMeansTrainer{

public:
	KMeansTrainer(std::string &train_path, int dictionary_size, int hessian_threshold);
	bool train(std::string &modelpath);
	void set_train_path(std::string &train_path);

private:
	Ptr<cv::xfeatures2d::SURF> surf;
	std::string train_path;
	int dictionary_size;
	int hessian_threshold;
	int num_of_features = 0;
	long current_date;
	cv::Mat dictionary;


	bool writeVocabulary(const std::string& filename, const cv::Mat& vocabulary);
	void kmeanstrain_log(bool enabled);

};
