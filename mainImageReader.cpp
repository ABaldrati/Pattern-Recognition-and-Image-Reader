#include "ImageReader.h"

int main() {
    int numThreads = 4;
    boost::basic_thread_pool ThreadPool(numThreads);

    std::string inputDir = "../input_images";
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<cv::Mat, fs::path>> imagesSeq = sequentialRead(inputDir);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<cv::Mat, fs::path>> imagesPar = parallelSyncRead(inputDir, numThreads);
    auto t4 = std::chrono::high_resolution_clock::now();

    auto t5 = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<boost::future<cv::Mat>,fs::path>> fut_images1 = asyncParallel(inputDir, ThreadPool);
    auto imagesAsync1 = std::vector<cv::Mat>();

    for (auto &fut_image : fut_images1) {
        imagesAsync1.push_back(std::get<0>(fut_image).get());
    }
    auto t6 = std::chrono::high_resolution_clock::now();


    auto durationSeq = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto durationSync = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    auto durationAsyc = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();


    std::cout << "Sequential read time: " << float(durationSeq / 1000000.) << std::endl;
    std::cout << "Parallel sync read time: " << float(durationSync / 1000000.) << std::endl;
    std::cout << "Parallel async2 read time: " << float(durationAsyc / 1000000.) << std::endl;


    return 0;
}