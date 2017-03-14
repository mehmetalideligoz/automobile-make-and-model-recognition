#include "model_detection.h"

ModelDetection::ModelDetection(){

}

// TODO: Check invalid files, and other conditions...
ModelDetection::ModelDetection(std::string &svm_file_name, std::string &vocabulary_file_name){
	// Load SVM
	svm = cv::ml::SVM::create();
	svm = cv::ml::SVM::load<cv::ml::SVM>(svm_file_name);

	// Load Dictionary
	cv::FileStorage fs(vocabulary_file_name, cv::FileStorage::READ);
	fs["vocabulary"] >> dictionary;
	
}


/*
	@brief: 

	@returns:
		- prediction::int


*/

int ModelDetection::detect_model(){
	
	// Create surf and matcher
	cv::Ptr<cv::DescriptorMatcher> matcher = new cv::FlannBasedMatcher;
	cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(400);

	// Create bow_descriptor_extractor
	cv::BOWImgDescriptorExtractor bow_descriptor_extractor(surf, matcher);
	bow_descriptor_extractor.setVocabulary(dictionary);

	// Predict input_image class
	surf->detect(input_image, keypoints);
	bow_descriptor_extractor.compute2(input_image, keypoints, bow_descriptor);
	int prediction = svm->predict(bow_descriptor);
	
	
	return prediction;
}


void ModelDetection::set_image(cv::Mat &image){
	input_image = image;
}







