#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

cv::Mat BinarizedImage(const cv::Mat &src)
{
  cv::Mat img_threshold_out;
    //Passage en niveau de gris
  cv::Mat mat_gray;
  if (src.channels() == 3) 
    cv::cvtColor(src, mat_gray, cv::COLOR_BGR2GRAY);
  else 
    mat_gray = src;

  //we get 0 where there is black, 255 where there is white.

  cv::threshold(mat_gray, img_threshold_out, 0, 255, cv::THRESH_OTSU);
  
  return img_threshold_out;
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    cv::Mat imageBin;
    imageBin = BinarizedImage(image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.                  // Show our image inside it.
    imshow( "Display window", imageBin);  
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
