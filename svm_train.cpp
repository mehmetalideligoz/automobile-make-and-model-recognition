//#define NB_IMAGES 20
//#define NB_CLASSES 17
//
//#include <opencv2/imgproc.hpp>
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/xfeatures2d.hpp"
//#include "opencv2/core/core.hpp"
//#include "opencv2/ml/ml.hpp"
//#include <chrono>
//#include <vector>
//#include <stdio.h>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//using namespace cv::xfeatures2d;
//using namespace cv::ml;
//
//
//const std::string trainPath = "C:/Users/raistlin/Documents/Visual Studio 2013/Projects/ModelDetection/App/App/train_resized/";
//
//bool writeVocabulary(const string& filename, const Mat& vocabulary);
//char ch[150];
////--------Using SURF as feature extractor and FlannBased for assigning a new point to the nearest one in the dictionary
//Ptr<DescriptorMatcher> matcher(new FlannBasedMatcher);
//Ptr<SURF> surf = SURF::create(400); // hessian: 400
////Ptr<DescriptorExtractor> extractor;
//
////---dictionary size=number of cluster's centroids
//int dictionarySize = 3000;
//TermCriteria tc(CV_TERMCRIT_ITER, 10, 0.001);
//int retries = 1;
//int flags = KMEANS_PP_CENTERS;
//BOWKMeansTrainer bowTrainer(dictionarySize, tc, retries, flags);
//BOWImgDescriptorExtractor bowDE(surf, matcher);
//
//
//int main()
//{
//
//	FileStorage fs("vocabulary_400_3000_resized", FileStorage::READ);
//
//	int i, j;
//	Mat img2;
//
//	Mat dictionary;
//	fs["vocabulary"] >> dictionary;
//
//	cout << "Read vocabulary..." << endl;
//	bowDE.setVocabulary(dictionary);
//	cout << "extracting histograms in the form of BOW for each image " << endl;
//	vector<int> label_vector;
//	Mat trainingData(0, dictionarySize, CV_32FC1);
//	int k = 0;
//	vector<KeyPoint> keypoint1;
//	Mat bowDescriptor1;
//
//	//extracting histogram in the form of bow for each image
//	for (j = 1; j <= NB_CLASSES; j++){
//		std::cout << "class " << j << std::endl;
//		for (i = 1; i <= NB_IMAGES; i++){ // number of images per class
//			sprintf(ch, "%s%d%s%d%s", trainPath.c_str(), j, "(", i, ").png");
//			const char* imageName = ch;
//			img2 = imread(imageName);
//
//			if (img2.empty()){
//				sprintf(ch, "%s%d%s%d%s", trainPath.c_str(), j, "(", i, ").jpg");
//				imageName = ch;
//				img2 = imread(imageName);
//				cout << ch;
//				if (img2.empty()){
//					cout << "GG!" << endl;
//					return -1;
//				}
//
//			}
//			cout << ch;
//			//resize(img2,img2, Size(256,128));
//			surf->detect(img2, keypoint1);
//			bowDE.compute2(img2, keypoint1, bowDescriptor1);
//
//			cout << "rows " << bowDescriptor1.rows << "cols " << bowDescriptor1.cols << endl;
//
//			trainingData.push_back(bowDescriptor1);
//
//			label_vector.push_back((int)j);
//		}
//	}
//	//cout << "rows training dat" << trainingData.rows << "cols" << trainingData.cols << endl;
//
//	int label_array[340]; // 220
//	for (int i = 0; i < label_vector.size(); ++i){
//
//		label_array[i] = label_vector[i];
//
//		cout << i << " ";
//	}
//
//	Mat labels(340, 1, CV_32S, label_array); // 32S
//
//	//Setting up SVM parameters
//	Ptr<SVM> svm = SVM::create();
//	svm->setType(SVM::C_SVC);
//	svm->setKernel(SVM::SIGMOID);
//	//svm->setGamma(0.1);
//	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
//	
//	Ptr<TrainData> trainData = ml::TrainData::create(trainingData, ROW_SAMPLE, labels);
//	
//	printf("%s\n", "Training SVM classifier");
//
//	svm->trainAuto(trainData);
//	//bool res = svm->train(trainingData, ROW_SAMPLE, labels);
//	
//	svm->save("new_svm_sigmoid");
//
//}