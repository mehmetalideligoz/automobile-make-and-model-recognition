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

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
using namespace cv::ml;

class ModelDetection{

public:
	ModelDetection();
	ModelDetection(string &svm_file_name, string &vocabulary_file_name);
	void set_image(Mat &image);
	int detect_model();


private:
	Mat dictionary;
	Mat input_image;
	Ptr<SVM> svm;
	vector<KeyPoint> keypoints;
	Mat bow_descriptor;
};