#include "model_detection.h"
#include <fstream>

int main(){


	vector <std::string> models = { "accent 1996 - 2001", "accent 2001 - 2012", "accent 2012 - 2016", "Audi A3 Sedan Attraction", "Audi A3 Sportback Ambition", "Audi A3 Sportback Attraction", "BMW 3.20", "Volkwagen Golf", "Fiat Doblo",
		"Fiat Linea 1.3Multijet", "Fiat punto", "Fiat Tipo", "ford fiesta", "Ford Focus", "ford mondeo", "Honda Civic", "Hyundai Getz", "hyundai i30", "Mercedes 200 E", "Mercedes C - 180", "Nissan Qashqai 2009 - 2013", "Nissan Qashqai 2014 - 2016",
		"Opel Corsa", "peugeot 307", "Peugeot 508", "renault FLUENCE", "Seat Leon", "Tofas Sahin", "Toyota Auris 1.4 D - 4D Comfort Extra", "Toyota Corolla", "Volkswagen Jetta", "Volkswagen Passat", "Volkswagen Polo" };


	// Define paths for pretrained svm and vocabulary
	string svm_file_name = "svm_20170305_1";
	string vocabulary_file_name = "vocabulary_20170305_1";

	// Create an instance of ModelDetection
	ModelDetection *md = new ModelDetection(svm_file_name, vocabulary_file_name);

	
	// Set input image here
	string test_path = "C:/Users/raistlin/Documents/Visual Studio 2013/Projects/ModelDetection/App/App/Model/test";

	ofstream myfile;
	myfile.open("log.txt");
	std::vector<cv::String> filenames;
	glob(test_path, filenames);

	for (int i = 0; i < filenames.size(); ++i){
		Mat input_image = imread(filenames[i]);
		md->set_image(input_image);

		cout << "Remaining: " << filenames.size()- i +1 << endl;
		int prediction = md->detect_model();

		myfile << "File: " << filenames[i] << "\t" << "Label: " << models[prediction - 1]<< "\t" <<prediction << endl;

	}
	myfile.close();


	// Since we labeled the models according to their file names (e.g. 1(1), 2(1)...), the order of models matters.
	//vector <std::string> models = { "Toyota Corolla", "VW Polo", "Ford Focus", "VW Passat", "Honda Civic", "Mercedes C-180", "Opel Corsa", "Peugeot 307", "Seat Ibiza", "Tofas Sahin", "Toyota Auris", "Fiat Linea", "Fiat Punto", "Hyundai i30", "Hyundai Accent", "VW Jetta", "Fluence" };
	
	return 0;

}
