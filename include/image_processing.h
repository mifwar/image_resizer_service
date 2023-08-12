#pragma once

#include <string>
#include <base64.h>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

class ImageProcessing{
public:
    cv::Mat image_resizer(cv::Mat source, int desired_width, int desired_height);
    cv::Mat encoded_to_mat(std::string encoded_data);
    std::string mat_to_encoded(cv::Mat source);

    Base64Codec codec;
};