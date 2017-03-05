#include "kmeans_train.h"

/*
 SURF TUTORIAL: http://docs.opencv.org/trunk/df/dd2/tutorial_py_surf_intro.html


*/
KMeansTrainer::KMeansTrainer(){


}

/*
 LOG file for bow kmeans training
*/
void KMeansTrainer::kmeanstrain_log(bool enabled){
	
	//if (enabled){
	//	surf->getDefaultName();
	//	modelpath;

	//}




}

bool KMeansTrainer::writeVocabulary(const string& filename, const Mat& vocabulary){
	cout << "Saving vocabulary..." << endl;
	FileStorage fs(filename, FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "vocabulary" << vocabulary;
		return true;
	}
	return false;
}

/*
Steps:
	1. Compute descriptors for a given image and its keypoints set.
	2. Find the nearest visual words from the vocabulary for each keypoint descriptor.
	3. Compute the bag-of-words image descriptor as is a normalized histogram of vocabulary words encountered in the image. The i-th bin of the histogram is a frequency of i-th word of the vocabulary in the given image.


*/
bool KMeansTrainer::train(std::string &modelpath){
	//std::string modelpath = "C:/Users/raistlin/Documents/Visual Studio 2013/Projects/ModelDetection/App/App/train_resized/";
	std::vector<cv::String> filenames;
	glob(modelpath, filenames);


	Ptr<DescriptorMatcher> matcher(new FlannBasedMatcher);

	// TODO: hessianThreshold = 400, adjust this value by image's contrast
	surf = SURF::create(400);
	// 128-dim instead of 64-dim features
	surf->setExtended(true);

	// TODO: # of cluster centers
	dictionary_size = 3000;

	// CV_TERMCRIT_EPS: Terminate until convergence
	TermCriteria tc(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 0.001);
	


	// KMEANS_PP_CENTERS Use kmeans++ center initialization by Arthur and Vassilvitskii
	BOWKMeansTrainer bow_trainer(dictionary_size, tc, 1, KMEANS_PP_CENTERS);
	BOWImgDescriptorExtractor bow_descriptor_extractor(surf, matcher);

	for (int i = 0; i < filenames.size(); ++i){

		Mat img;
		img = imread(filenames[i]);

		// SURF detects keypoints and computes descriptors
		vector<KeyPoint> keypoints;
		Mat features;

		// TODO: detectAndCompute vs. detect + bowDE.compute2()
		surf->detectAndCompute(img, noArray(), keypoints, features);
		//surf->detect(img, noArray(), keypoints);
		//bowDE.compute2(img, keypoint, bowDescriptor);
		bow_trainer.add(features);

	}

	Mat dictionary = bow_trainer.cluster();

	long current_date = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	writeVocabulary("vocabulary_" + std::to_string(current_date), dictionary);

	return true;
}
