#define BOOST_THREAD_VERSION 5
#define BOOST_THREAD_PROVIDES_EXECUTORS
#define BOOST_THREAD_USES_LOG_THREAD_ID
#define BOOST_THREAD_QUEUE_DEPRECATE_OLD
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY

#include <iostream>
#include "Utils.h"
#include "Matrix.h"
#include "PatternRecognition.h"
#include <chrono>
#include <filesystem>

#include <boost/thread/future.hpp>
#include <boost/thread/caller_context.hpp>
#include <boost/thread/executors/basic_thread_pool.hpp>


int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    cv::Mat image = cv::imread("../000.jpeg");
    cv::Mat greyImage;
    cv::cvtColor(image, greyImage, CV_BGR2GRAY);
    Matrix<int> target(greyImage);
    Matrix<int> query(20, 200);


    //target.generateRandomUniformMatrix(255);
    query.generateRandomUniformMatrix(255);

    //print_array(target.getValues(),target.getLength(),"target");

    //print_array(query.getValues(), query.getLength(),"query");

    PatternRecognition<int> pattern(query, target);
    pattern.findPattern();
    // pattern.printPatterns();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    auto point1 = cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate());
    auto point2 = cv::Point(pattern.getCxCoordinate() + query.getNumberOfColumns(),
                            pattern.getCyCoordinate() + query.getNumberOfRows());

    cv::rectangle(image, point1, point2, cv::Scalar(0, 255, 0));
    cv::imshow("color", image);
    cv::waitKey(0);

    std::cout << std::endl << float(duration / 1000000.);

}
