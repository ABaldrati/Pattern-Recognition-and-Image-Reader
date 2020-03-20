#include "ImageReader.h"

int main() {
    std::string inputDir = "../EasyMotion";
    const int numExecPerTest = 5;
    const int maxNumThreads = 12;
    sleep(10);

    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; ++i) {
            std::vector<std::pair<cv::Mat, fs::path>> imagesPar = parallelSyncRead(inputDir, numThreads);
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        sleep(1);
        auto durationSync = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Parallel sync read time with numThread " << numThreads << "   "
                  << float(durationSync / (numExecPerTest * 1000000.))
                  << std::endl;
        sleep(10);
    }

    std::cout << std::endl << std::endl;

    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        boost::basic_thread_pool ThreadPool(numThreads);
        sleep(10);

        auto t3 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; ++i) {
            std::vector<std::pair<boost::future<cv::Mat>, fs::path>> fut_images1 = asyncParallel(inputDir, ThreadPool);
            auto imagesAsync1 = std::vector<cv::Mat>();

            for (auto &fut_image : fut_images1) {
                imagesAsync1.push_back(std::get<0>(fut_image).get());
            }
        }
        auto t4 = std::chrono::high_resolution_clock::now();

        auto durationAsyc = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
        std::cout << "Parallel async read time with numThread " << numThreads << "   "
                  << float(durationAsyc / (numExecPerTest * 1000000.)) << std::endl;
        sleep(10);
    }
    return 0;
}