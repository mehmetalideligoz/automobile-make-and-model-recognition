#include "model_detection.h"

ModelDetection::ModelDetection(){

}

// TODO: Check invalid files, and other conditions...
ModelDetection::ModelDetection(string &svm_file_name, string &vocabulary_file_name){
	// Load SVM
	svm = SVM::create();
	svm = SVM::load<SVM>(svm_file_name);

	// Load Dictionary
	FileStorage fs(vocabulary_file_name, FileStorage::READ);
	fs["vocabulary"] >> dictionary;
	
}


/*
	@brief:

	@returns:
		- prediction::int


*/

int ModelDetection::detect_model(){
	
	// Create surf and matcher
	Ptr<DescriptorMatcher> matcher = new FlannBasedMatcher;
	Ptr<SURF> surf = SURF::create(400);

	// Create bow_descriptor_extractor
	BOWImgDescriptorExtractor bow_descriptor_extractor(surf, matcher);
	bow_descriptor_extractor.setVocabulary(dictionary);

	// Predict input_image class
	surf->detect(input_image, keypoints);
	bow_descriptor_extractor.compute2(input_image, keypoints, bow_descriptor);
	int prediction = svm->predict(bow_descriptor);
	
	
	return prediction;
}


void ModelDetection::set_image(Mat &image){
	input_image = image;
}







