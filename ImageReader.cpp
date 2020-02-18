#include "ImageReader.h"

namespace fs = std::filesystem;

std::vector<cv::Mat> sequentialRead(std::string &inputDir) {
    auto images = std::vector<cv::Mat>();
    for (const auto &dirEntry : fs::recursive_directory_iterator(inputDir)) {
        cv::Mat image = cv::imread(dirEntry.path().u8string(), 0);

        if (!image.data)                              // Check for invalid input
        {
            std::cout << "Could not open or find the image" << std::endl;
        }

        images.push_back(image);
    }
    return images;
}


std::vector<cv::Mat> parallelSyncRead(std::string &inputDir, int numThreads) {
    auto images = std::vector<cv::Mat>();
    std::vector<std::string> image_paths = std::vector<std::string>();
    for (const auto &dirEntry : fs::recursive_directory_iterator(inputDir)) {
        image_paths.push_back(dirEntry.path().u8string());
    }

    if (numThreads < 0) {
        numThreads = omp_get_num_devices();
    }

#pragma omp parallel for schedule(static) num_threads(numThreads) shared(image_paths, std::cout, images) default(none)
    for (int i = 0; i < image_paths.size(); i++) {
        cv::Mat image = cv::imread(image_paths[i], 0);

        if (!image.data)                              // Check for invalid input
        {
            std::cout << "Could not open or find the image" << std::endl;
        }
#pragma omp critical
        images.push_back(image);
    }

    return images;
}


std::vector<boost::future<cv::Mat>> asyncParallel(std::string &inputDir, int numThreads) {
    if (numThreads < 1) {
        numThreads = std::thread::hardware_concurrency();
    }

    boost::basic_thread_pool ThreadPool(numThreads);

    std::vector<boost::future<cv::Mat>> fut_images = std::vector<boost::future<cv::Mat>>();

    std::vector<std::string> image_paths = std::vector<std::string>();
    for (const auto &dirEntry : fs::recursive_directory_iterator(inputDir)) {
        auto readImage = boost::bind<cv::Mat>([](std::string image) { return cv::imread(image, 0); },
                                              dirEntry.path().u8string());
        fut_images.push_back(boost::async(ThreadPool, readImage));
    }
    return fut_images;
}