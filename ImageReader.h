#ifndef PATTERN_RECOGNITION_IMAGEREADER_H
#define PATTERN_RECOGNITION_IMAGEREADER_H

#define BOOST_THREAD_VERSION 5
#define BOOST_THREAD_PROVIDES_EXECUTORS
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <opencv2/core/core.hpp>
#include <opencv2/viz/vizcore.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cv.hpp>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <future>
#include "omp.h"
#include <boost/thread/future.hpp>
#include <boost/thread/executors/basic_thread_pool.hpp>
namespace fs = std::filesystem;

std::vector<std::pair<cv::Mat, fs::path>> sequentialRead(std::string &inputDir, int color = CV_LOAD_IMAGE_GRAYSCALE);


std::vector<std::pair<cv::Mat, fs::path>>
parallelSyncRead(std::string &inputDir,  int numThreads = -1 ,int color = CV_LOAD_IMAGE_GRAYSCALE);


std::vector<std::pair<boost::future<cv::Mat>, fs::path>>
asyncParallel(std::string &inputDir,boost::basic_thread_pool &ThreadPool , int color = CV_LOAD_IMAGE_GRAYSCALE);

#endif //PATTERN_RECOGNITION_IMAGEREADER_H
