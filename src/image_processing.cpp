#include <string>
#include <image_processing.h>

cv::Mat ImageProcessing::image_resizer(cv::Mat source, int desired_width, int desired_height){
    cv::Mat resized_image;
    cv::resize(source, resized_image, cv::Size(desired_width, desired_height));

    return resized_image;
}

cv::Mat ImageProcessing::encoded_to_mat(std::string encoded_data){
    std::string decoded_data = codec.decoder(encoded_data);
    std::vector<char> vec_decoded_data(decoded_data.begin(), decoded_data.end());
    cv::Mat image = cv::imdecode(vec_decoded_data, cv::IMREAD_COLOR);

    return image;
}

std::string ImageProcessing::mat_to_encoded(cv::Mat source){
    std::vector<uchar> buffer;
    cv::imencode(".jpeg", source, buffer);
    std::string buffer_str(buffer.begin(), buffer.end());
    std::string encoded_data = codec.encoder(buffer_str);

    return encoded_data;
}