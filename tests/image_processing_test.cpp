#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include <image_processing.h>

TEST_CASE("test image resize")
{
    ImageProcessing img_proc;

    cv::Mat image = cv::imread("../tests/resource/sample_image.jpeg");

    REQUIRE(!image.empty());

    int desired_width = 200;
    int desired_height = 200;

    cv::Mat resized_image = img_proc.image_resizer(image, desired_width, desired_height);

    REQUIRE(resized_image.cols == desired_width);
    REQUIRE(resized_image.rows == desired_height);
}