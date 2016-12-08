# automobile-make-and-model-recognition


Questions:

0- About input image:
- What should be the size of images in training/test set?
- Should we use grayscale or rgb input?
- Does preprocessing images provide better results? (histogram equalization, contrast streching, thresholding, blurring) 

1- About feature detection:
- Which one is suitable for real time applications? Surf vs. Sift vs. Orb etc. 
- How to determine the size of hessian matrix?
- Should we fix the feature size? 

2- About matcher:
- Flann vs. BruteForce

3- About Bagofwords:
- What should be the right choice of dictionary size?
- What about 'k' value? 

4- About svm:
- What are the best parameters for svm? (c, iteration, learning rate, kernel type)

5- About C++ and OpenCV:
- OpenCV version differences?
- Which image type to use: CV_8FC1, CV_32S, CV_32FC1 ...
- Reading from and writing to a file, glob() function and FileStorage
- Include files and namespaces 
