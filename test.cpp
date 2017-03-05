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
//#include "opencv2/face/predict_collector.hpp"
//
//
//
//
//using namespace cv;
//using namespace std;
//using namespace cv::xfeatures2d;
//using namespace cv::ml;
//
//
//const std::string trainPath = "C:/Users/raistlin/Documents/Visual Studio 2013/Projects/ModelDetection/App/App/images/";
//const std::string testPath = "C:/Users/raistlin/Documents/Visual Studio 2013/Projects/ModelDetection/App/App/test_resized/";
//
//
//char ch[150];
//Ptr<DescriptorMatcher> matcher(new FlannBasedMatcher);
//Ptr<SURF> surf = SURF::create(400); // hessian: 400
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
//int main(){
//	printf("%s\n", "Loading SVM classifier");
//	Ptr<SVM> svm = SVM::create();
//	svm = SVM::load<SVM>("new_svm_rbf");
//	FileStorage fs("vocabulary_400_3000_resized", FileStorage::READ);
//	Mat dictionary;
//	fs["vocabulary"] >> dictionary;
//	bowDE.setVocabulary(dictionary);
//	cout << "Processing evaluation data..." << endl;
//
//
//	Mat groundTruth(0, 1, CV_32FC1);
//	Mat evalData(0, dictionarySize, CV_32FC1);
//	int k = 0;
//	vector<KeyPoint> keypoint2;
//	Mat bowDescriptor2;
//
//	// TEST
//	Mat results(0, 1, CV_32S);
//	std::string test_path = "C:/Users/raistlin/Documents/Visual Studio 2013/Projects/ModelDetection/App/App/test_resized/";
//	std::vector<cv::String> test_files;
//	glob(test_path, test_files);
//
//	vector <std::string> models = { "Toyota Corolla", "VW Polo", "Ford Focus", "VW Passat", "Honda Civic", "Mercedes C-180", "Opel Corsa", "Peugeot 307", "Seat Ibiza", "Tofas Sahin", "Toyota Auris", "Fiat Linea", "Fiat Punto", "Hyundai i30", "Hyundai Accent", "VW Jetta", "Fluence" };
//	for (int j = 1; j <= NB_CLASSES; j++)
//		for (int i = 1; i <= 5; i++){ // 5 test images per class
//			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//			sprintf(ch, "%s%d%s%d%s", testPath.c_str(), j, "(", i, ").png");
//			const char* imageName = ch;
//			Mat img2 = imread(imageName);
//
//			if (img2.empty()){
//				sprintf(ch, "%s%d%s%d%s", testPath.c_str(), j, "(", i, ").jpg");
//				imageName = ch;
//				img2 = imread(imageName);
//				if (img2.empty()){
//					cout << "GG!" << endl;
//				}
//
//			}
//
//			cout << "Image size: " << img2.size().width << "x" << img2.size().height << endl;	
//			surf->detect(img2, keypoint2);
//			bowDE.compute2(img2, keypoint2, bowDescriptor2);
//
//			//imshow("test", img2);
//			if (bowDescriptor2.size().height < 1){
//				cout << "Empty bow descriptor!" << endl;
//				system("pause");
//				continue;
//
//			}
//			evalData.push_back(bowDescriptor2);
//			groundTruth.push_back((float)j); //float j
//			//float prediction = svm->predict(bowDescriptor2);
//
//			vector<Mat> results_prediction;
//
//			int prediction = svm->predict(bowDescriptor2, results_prediction, 1);
//
//			if (!results_prediction.empty()){
//				imshow("asd", results_prediction[0]);
//				waitKey(0);
//			}
//
//			putText(img2, "Prediction: " + models[prediction - 1], cv::Point(0, img2.size().height - 30), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 3, 8);
//			imshow("Model Prediction", img2);
//
//			cout << "---------------------" << endl;
//			cout << "True Label: " << models[j - 1] << endl;
//			cout << ", Prediction :  " << models[prediction - 1] << endl;
//	
//			//cout << ", Confidence : " << confidence << endl;
//			results.push_back(prediction);
//			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//			long timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
//			std::cout << "TIME ELAPSED: " << timeElapsed << std::endl;
//			waitKey(1000);
//		}
//
//
//
//	//calculate the number of unmatched classes
//	double errorRate = (double)countNonZero(groundTruth - results) / evalData.rows;
//	cout << "Error rate is: " << errorRate;
//	system("pause");
//	return 0;
//
//}