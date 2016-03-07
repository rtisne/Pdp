#ifndef BINARIZATION_H
#define BINARIZATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

enum NiblackVersion 
{
	NIBLACK=0,
    SAUVOLA,
    WOLFJOLION,
};

#define uget(x,y)    at<unsigned char>(y,x)
#define uset(x,y,v)  at<unsigned char>(y,x)=v;
#define fget(x,y)    at<float>(y,x)
#define fset(x,y,v)  at<float>(y,x)=v;

void binarize(cv::Mat &src, cv::Mat &dst, int method=CV_THRESH_OTSU, int thresholdType=17, int blockSize=11);
void preProcess(cv::Mat &src, cv::Mat &dst, int erosion=12);
void postProcess(cv::Mat &src, cv::Mat &dst, double v=0.9, int win=7);
void shrinkFilter(cv::Mat &src, cv::Mat &dst, double v=0.9, int win=5);
void swellFilter(cv::Mat &src, cv::Mat &dst, int win=16);
void connectivityFilter(cv::Mat &src, cv::Mat &dst);
double calcLocalStats (cv::Mat &im, cv::Mat &map_m, cv::Mat &map_s, int winx, int winy);
void NiblackSauvolaWolfJolion (cv::Mat im, cv::Mat output, NiblackVersion version, double dR=128, int winx=40, int winy=40, double k=0.34);
void applyErosion(cv::Mat &src, cv::Mat &dst, int erosion_type=2, int erosion_size=2);
void applyDilation(cv::Mat &src, cv::Mat &dst, int dilation_type=2, int dilation_size=2);
#endif // BINARIZATION_H
