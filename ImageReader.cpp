#include "ImageReader.h"

namespace fs = std::filesystem;

std::vector<std::pair<cv::Mat, fs::path>> sequentialRead(std::string &inputDir, int color) {
    auto images = std::vector<std::pair<cv::Mat, fs::path>>();
    for (const auto &dirEntry : fs::recursive_directory_iterator(inputDir)) {
        cv::Mat image = cv::imread(dirEntry.path().u8string(), color);

        if (!image.data)                              // Check for invalid input
        {
            std::cout << "Could not open or find the image" << std::endl;
        }

        images.push_back(std::make_pair(image, dirEntry.path()));
    }
    return images;
}


std::vector<std::pair<cv::Mat, fs::path>> parallelSyncRead(std::string &inputDir, int numThreads, int color) {
    auto images = std::vector<std::pair<cv::Mat, fs::path>>();
    std::vector<fs::path> image_paths = std::vector<fs::path>();
    for (const auto &dirEntry : fs::recursive_directory_iterator(inputDir)) {
        image_paths.push_back(dirEntry.path());
    }

    if (numThreads < 0) {
#ifdef _OPENMP
        numThreads = omp_get_num_devices();
#endif
    }


#pragma omp parallel for schedule(static) num_threads(numThreads) shared(image_paths, std::cout, images, color) default(none)
    for (int i = 0; i < image_paths.size(); i++) {
        cv::Mat image = cv::imread(image_paths[i].u8string(), color);

        if (!image.data)                              // Check for invalid input
        {
            std::cout << "Could not open or find the image" << std::endl;
        }
#pragma omp critical
        images.push_back(std::make_pair(image, image_paths[i]));
    }

    return images;
}


std::vector<std::pair<boost::future<cv::Mat>, fs::path>>
asyncParallel(std::string &inputDir, boost::basic_thread_pool &ThreadPool, int color) {

    auto fut_images = std::vector<std::pair<boost::future<cv::Mat>, fs::path>>();

    std::vector<std::string> image_paths = std::vector<std::string>();
    for (const auto &dirEntry : fs::recursive_directory_iterator(inputDir)) {
        auto readImage = boost::bind<cv::Mat>([color](std::string image) { return cv::imread(image, color); },
                                              dirEntry.path().u8string());
        fut_images.push_back(std::make_pair(boost::async(ThreadPool, readImage), dirEntry.path()));
    }
    return fut_images;
}