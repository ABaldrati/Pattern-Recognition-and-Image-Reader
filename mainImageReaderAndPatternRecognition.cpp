#include <iostream>
#include "Utils.h"
#include "Matrix.h"
#include "PatternRecognition.h"
#include <chrono>
#include <filesystem>
#include "ImageReader.h"

int main() {
    std::string inputDir = "../input_images1";
    fs::path outputDir = fs::u8path("../output_images");
    fs::create_directory(outputDir);

    int numThreads = 4;
    boost::basic_thread_pool ThreadPool(numThreads);

    std::vector<std::pair<boost::future<cv::Mat>, fs::path>> fut_images_and_paths = asyncParallel(inputDir,ThreadPool,  CV_LOAD_IMAGE_COLOR);
    Matrix<int> query(75, 75);
    query.generateRandomUniformMatrix(255);

    auto futures_task = std::vector<boost::future<void>>();
    for (auto &fut_image_and_path : fut_images_and_paths) {
        futures_task.push_back(std::get<0>(fut_image_and_path).then(ThreadPool,[&query, &fut_image_and_path, outputDir](auto fut_image) {
            auto colorImage = fut_image.get();
            auto path = std::get<1>(fut_image_and_path);
            cv::Mat greyImage;
            cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
            auto matrix = Matrix<int>(greyImage);
            PatternRecognition<int> pattern(query, matrix);
            pattern.findPattern(1);
            auto points = std::make_pair<cv::Point, cv::Point>(
                    cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                    cv::Point(pattern.getCxCoordinate() + query.getNumberOfColumns(),
                              pattern.getCyCoordinate() + query.getNumberOfRows()));
            cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                          cv::Scalar(0, 255, 0), 2);
            auto file_name_string = path.filename().u8string();
            auto dirString = outputDir.u8string();
            cv::imwrite(dirString + "/" + file_name_string, colorImage);
            std::cout << dirString + "/" + file_name_string << std::endl;
        }));
    }
    for (auto &fut_task : futures_task){
        fut_task.wait();
    }
}
