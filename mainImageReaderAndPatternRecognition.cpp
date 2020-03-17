#include <iostream>
#include "Utils.h"
#include "Matrix.h"
#include "PatternRecognition.h"
#include <chrono>
#include <filesystem>
#include "ImageReader.h"

int main() {
    //---------------------------------------------------
    std::string inputDir = "../test5k";
    fs::path outputDir = fs::u8path("../output_images");
    const int numExecPerTest = 5;
    const int maxNumThreads = 12 ;
    fs::create_directory(outputDir);
    Matrix<int> query1(10, 10);
    query1.generateRandomUniformMatrix(255);

    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        boost::basic_thread_pool ThreadPool(numThreads);
        sleep(5);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; ++i) {
            std::vector<std::pair<boost::future<cv::Mat>, fs::path>> fut_images_and_paths = asyncParallel(
                    inputDir, ThreadPool, CV_LOAD_IMAGE_COLOR);

            auto futures_task = std::vector<boost::future<void>>();
            for (auto &fut_image_and_path : fut_images_and_paths) {
                futures_task.push_back(
                        std::get<0>(fut_image_and_path).then(ThreadPool, [&query1, &fut_image_and_path](
                                auto fut_image) {
                            auto colorImage = fut_image.get();
                            auto path = std::get<1>(fut_image_and_path);
                            cv::Mat greyImage;
                            cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
                            auto matrix = Matrix<int>(greyImage);
                            PatternRecognition<int> pattern(query1, matrix);
                            pattern.findPattern(1);
                            auto points = std::make_pair<cv::Point, cv::Point>(
                                    cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                                    cv::Point(pattern.getCxCoordinate() + query1.getNumberOfColumns(),
                                              pattern.getCyCoordinate() + query1.getNumberOfRows()));
                            cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                                          cv::Scalar(0, 255, 0), 2);
                            return std::make_pair(colorImage, path);
                        }).then(ThreadPool, [outputDir](auto fut_image_and_path){
                            cv::Mat image;
                            fs::path path;
                            std::tie(image, path) = fut_image_and_path.get();
                            auto file_name_string = path.filename().u8string();
                            auto dirString = outputDir.u8string();
                            cv::imwrite(dirString + "/" + file_name_string, image);
                        }));
            }
            for (auto &fut_task : futures_task) {
                fut_task.wait();
            }
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Parallel async execution with QueryMatrix " << query1.getNumberOfRows() << "X"
                  << query1.getNumberOfColumns() << " with numThread " << numThreads << "   "
                  << float(duration / (numExecPerTest * 1000000.)) << std::endl;

        sleep(10);
    }
    std::cout << std::endl;
    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        auto t3 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; i++) {
            std::vector<std::pair<cv::Mat, fs::path>> images_and_paths = parallelSyncRead(
                    inputDir, numThreads, CV_LOAD_IMAGE_COLOR);
#pragma omp parallel for schedule(static) num_threads(numThreads) shared(outputDir, images_and_paths, query1) default(none)
            for (int i = 0; i < images_and_paths.size(); ++i) {
                auto colorImage = std::get<0>(images_and_paths[i]);
                auto path = std::get<1>(images_and_paths[i]);
                cv::Mat greyImage;
                cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
                auto matrix = Matrix<int>(greyImage);
                PatternRecognition<int> pattern(query1, matrix);
                pattern.findPattern(1);
                auto points = std::make_pair<cv::Point, cv::Point>(
                        cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                        cv::Point(pattern.getCxCoordinate() + query1.getNumberOfColumns(),
                                  pattern.getCyCoordinate() + query1.getNumberOfRows()));
                cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                              cv::Scalar(0, 255, 0), 2);
                auto file_name_string = path.filename().u8string();
                auto dirString = outputDir.u8string();
                cv::imwrite(dirString + "/" + "sync." + file_name_string, colorImage);
            }
        }
        auto t4 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
        std::cout << "Parallel sync execution with QueryMatrix " << query1.getNumberOfRows() << "X"
                  << query1.getNumberOfColumns() << " with numThread " << numThreads << "   "
                  << float(duration / (numExecPerTest * 1000000.)) << std::endl;
        sleep(10);
    }
    std::cout << std::endl << std::endl;
    //------------------------------------------------------------------------------------------------------------------
    Matrix<int> query2(20, 20);
    query2.generateRandomUniformMatrix(255);

    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        boost::basic_thread_pool ThreadPool(numThreads);
        sleep(10);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; ++i) {
            std::vector<std::pair<boost::future<cv::Mat>, fs::path>> fut_images_and_paths = asyncParallel(
                    inputDir, ThreadPool, CV_LOAD_IMAGE_COLOR);

            auto futures_task = std::vector<boost::future<void>>();
            for (auto &fut_image_and_path : fut_images_and_paths) {
                futures_task.push_back(
                        std::get<0>(fut_image_and_path).then(ThreadPool, [&query2, &fut_image_and_path](
                                auto fut_image) {
                            auto colorImage = fut_image.get();
                            auto path = std::get<1>(fut_image_and_path);
                            cv::Mat greyImage;
                            cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
                            auto matrix = Matrix<int>(greyImage);
                            PatternRecognition<int> pattern(query2, matrix);
                            pattern.findPattern(1);
                            auto points = std::make_pair<cv::Point, cv::Point>(
                                    cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                                    cv::Point(pattern.getCxCoordinate() + query2.getNumberOfColumns(),
                                              pattern.getCyCoordinate() + query2.getNumberOfRows()));
                            cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                                          cv::Scalar(0, 255, 0), 2);
                            return std::make_pair(colorImage, path);
                        }).then(ThreadPool, [outputDir](auto fut_image_and_path){
                            cv::Mat image;
                            fs::path path;
                            std::tie(image, path) = fut_image_and_path.get();
                            auto file_name_string = path.filename().u8string();
                            auto dirString = outputDir.u8string();
                            cv::imwrite(dirString + "/" + file_name_string, image);
                        }));
            }
            for (auto &fut_task : futures_task) {
                fut_task.wait();
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Parallel async execution with QueryMatrix " << query2.getNumberOfRows() << "X"
                  << query2.getNumberOfColumns() << " with numThread " << numThreads << "   "
                  << float(duration / (numExecPerTest * 1000000.)) << std::endl;

        sleep(10);
    }
    std::cout << std::endl;
    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        auto t3 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; i++) {
            std::vector<std::pair<cv::Mat, fs::path>> images_and_paths = parallelSyncRead(
                    inputDir, numThreads, CV_LOAD_IMAGE_COLOR);
#pragma omp parallel for schedule(static) num_threads(numThreads) shared(outputDir, images_and_paths, query2) default(none)
            for (int i = 0; i < images_and_paths.size(); ++i) {
                auto colorImage = std::get<0>(images_and_paths[i]);
                auto path = std::get<1>(images_and_paths[i]);
                cv::Mat greyImage;
                cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
                auto matrix = Matrix<int>(greyImage);
                PatternRecognition<int> pattern(query2, matrix);
                pattern.findPattern(1);
                auto points = std::make_pair<cv::Point, cv::Point>(
                        cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                        cv::Point(pattern.getCxCoordinate() + query2.getNumberOfColumns(),
                                  pattern.getCyCoordinate() + query2.getNumberOfRows()));
                cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                              cv::Scalar(0, 255, 0), 2);
                auto file_name_string = path.filename().u8string();
                auto dirString = outputDir.u8string();
                cv::imwrite(dirString + "/" + "sync." + file_name_string, colorImage);
            }
        }
        auto t4 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
        std::cout << "Parallel sync execution with QueryMatrix " << query2.getNumberOfRows() << "X"
                  << query2.getNumberOfColumns() << " with numThread " << numThreads << "   "
                  << float(duration / (numExecPerTest * 1000000.)) << std::endl;
        sleep(10);
    }

    std::cout << std::endl << std::endl;
    //----------------------------------------------------------------------------------------------------------------
    Matrix<int> query3(30, 30);
    query3.generateRandomUniformMatrix(255);

    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        boost::basic_thread_pool ThreadPool(numThreads);
        sleep(1);

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; ++i) {
            std::vector<std::pair<boost::future<cv::Mat>, fs::path>> fut_images_and_paths = asyncParallel(
                    inputDir, ThreadPool, CV_LOAD_IMAGE_COLOR);

            auto futures_task = std::vector<boost::future<void>>();
            for (auto &fut_image_and_path : fut_images_and_paths) {
                futures_task.push_back(
                        std::get<0>(fut_image_and_path).then(ThreadPool, [&query3, &fut_image_and_path](
                                auto fut_image) {
                            auto colorImage = fut_image.get();
                            auto path = std::get<1>(fut_image_and_path);
                            cv::Mat greyImage;
                            cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
                            auto matrix = Matrix<int>(greyImage);
                            PatternRecognition<int> pattern(query3, matrix);
                            pattern.findPattern(1);
                            auto points = std::make_pair<cv::Point, cv::Point>(
                                    cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                                    cv::Point(pattern.getCxCoordinate() + query3.getNumberOfColumns(),
                                              pattern.getCyCoordinate() + query3.getNumberOfRows()));
                            cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                                          cv::Scalar(0, 255, 0), 2);
                            return std::make_pair(colorImage, path);
                        }).then(ThreadPool, [outputDir](auto fut_image_and_path){
                            cv::Mat image;
                            fs::path path;
                            std::tie(image, path) = fut_image_and_path.get();
                            auto file_name_string = path.filename().u8string();
                            auto dirString = outputDir.u8string();
                            cv::imwrite(dirString + "/" + file_name_string, image);
                        }));
            }
            for (auto &fut_task : futures_task) {
                fut_task.wait();
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Parallel async execution with QueryMatrix " << query3.getNumberOfRows() << "X"
                  << query3.getNumberOfColumns() << " with numThread " << numThreads << "   "
                  << float(duration / (numExecPerTest * 1000000.)) << std::endl;

        sleep(10);
    }

    std::cout << std::endl << std::endl;

    for (int numThreads = 1; numThreads < maxNumThreads; ++numThreads) {
        auto t3 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numExecPerTest; i++) {
            std::vector<std::pair<cv::Mat, fs::path>> images_and_paths = parallelSyncRead(
                    inputDir, numThreads, CV_LOAD_IMAGE_COLOR);
#pragma omp parallel for schedule(static) num_threads(numThreads) shared(outputDir, images_and_paths, query3) default(none)
            for (int i = 0; i < images_and_paths.size(); ++i) {
                auto colorImage = std::get<0>(images_and_paths[i]);
                auto path = std::get<1>(images_and_paths[i]);
                cv::Mat greyImage;
                cv::cvtColor(colorImage, greyImage, CV_BGR2GRAY);
                auto matrix = Matrix<int>(greyImage);
                PatternRecognition<int> pattern(query3, matrix);
                pattern.findPattern(1);
                auto points = std::make_pair<cv::Point, cv::Point>(
                        cv::Point(pattern.getCxCoordinate(), pattern.getCyCoordinate()),
                        cv::Point(pattern.getCxCoordinate() + query3.getNumberOfColumns(),
                                  pattern.getCyCoordinate() + query3.getNumberOfRows()));
                cv::rectangle(colorImage, std::get<0>(points), std::get<1>(points),
                              cv::Scalar(0, 255, 0), 2);
                auto file_name_string = path.filename().u8string();
                auto dirString = outputDir.u8string();
                cv::imwrite(dirString + "/" + "sync." + file_name_string, colorImage);
            }
        }
        auto t4 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
        std::cout << "Parallel sync execution with QueryMatrix " << query3.getNumberOfRows() << "X"
                  << query3.getNumberOfColumns() << " with numThread " << numThreads << "   "
                  << float(duration / (numExecPerTest * 1000000.)) << std::endl;
        sleep(10);
    }
}


