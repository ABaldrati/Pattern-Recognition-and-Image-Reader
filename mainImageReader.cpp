#include "ImageReader.h"

int main() {
    std::string inputDir = "../input_images";
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<cv::Mat> imagesSeq = sequentialRead(inputDir);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    std::vector<cv::Mat> imagesPar = parallelSyncRead(inputDir, 4);
    auto t4 = std::chrono::high_resolution_clock::now();

    auto t5 = std::chrono::high_resolution_clock::now();
    std::vector<boost::future<cv::Mat>> fut_images = asyncParallel(inputDir, 4);
    auto imagesAsync = std::vector<cv::Mat>();
    while (!fut_images.empty()) {
        auto image = boost::wait_for_any(fut_images.begin(), fut_images.end());
        imagesAsync.push_back((*image).get());
        fut_images.erase(image);
    }

    for (auto &fut_image : fut_images) {
        imagesAsync.push_back(fut_image.get());
    }
    auto t6 = std::chrono::high_resolution_clock::now();


    auto t7 = std::chrono::high_resolution_clock::now();
    std::vector<boost::future<cv::Mat>> fut_images1 = asyncParallel(inputDir, 4);
    auto imagesAsync1 = std::vector<cv::Mat>();

    for (auto &fut_image : fut_images1) {
        imagesAsync1.push_back(fut_image.get());
    }
    auto t8 = std::chrono::high_resolution_clock::now();


    auto durationSeq = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto durationSync = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    auto durationAsyc1 = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();
    auto durationAsyc2 = std::chrono::duration_cast<std::chrono::microseconds>(t8 - t7).count();


    std::cout << "Sequential read time: " << float(durationSeq / 1000000.) << std::endl;
    std::cout << "Parallel sync read time: " << float(durationSync / 1000000.) << std::endl;
    std::cout << "Parallel async1 read time: " << float(durationAsyc1 / 1000000.) << std::endl;
    std::cout << "Parallel async2 read time: " << float(durationAsyc2 / 1000000.) << std::endl;


    return 0;
}