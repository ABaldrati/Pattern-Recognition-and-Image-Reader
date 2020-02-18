#ifndef PATTERN_RECOGNITION_IMAGEREADER_H
#define PATTERN_RECOGNITION_IMAGEREADER_H

#define BOOST_THREAD_VERSION 5
#define BOOST_THREAD_PROVIDES_EXECUTORS
#define BOOST_THREAD_USES_LOG_THREAD_ID
#define BOOST_THREAD_QUEUE_DEPRECATE_OLD
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY

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
#include <boost/thread/caller_context.hpp>               // for BOOST_CONTEXTOF, caller_context_t, operator<<
#include <boost/thread/executors/basic_thread_pool.hpp>  // for basic_thread_pool
#include <boost/thread/executors/executor.hpp>           // for executor
#include <boost/thread/executors/executor_adaptor.hpp>   // for executor_adaptor

namespace fs = std::filesystem;

std::vector<cv::Mat> sequentialRead(std::string &inputDir);


std::vector<cv::Mat> parallelSyncRead(std::string &inputDir, int numThreads = -1);


std::vector<boost::future<cv::Mat>> asyncParallel(std::string &inputDir, int numThreads = -1);

#endif //PATTERN_RECOGNITION_IMAGEREADER_H
