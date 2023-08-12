#include <string>
#include <iostream>

#include <json_handler.h>
#include <image_processing.h>

#include <libasyik/service.hpp>
#include <libasyik/http.hpp>

int main(){    
    auto as = asyik::make_service();
    auto server = asyik::make_http_server(as, "127.0.0.1", 8080);

    server->on_http_request("/resize_image", "POST", [](auto req, auto args){
        JsonHandler json;

        auto send_response = [json, &req](int code, std::string message, std::string output_jpeg = ""){
            std::string json_result = json.setup_response(code, message, output_jpeg);
            req->response.body = json_result;
            req->response.result(code);
        };

        if(!json.parse(req->body)){
            send_response(400, "Invalid JSON format");
            return;            
        }

        std::string encoded_data = json.get_encoded_data();
        auto [is_valid_width, desired_width] = json.get_desired_width();
        auto [is_valid_height, desired_height] = json.get_desired_height();

        bool is_valid_size_format = is_valid_width && is_valid_height;
        bool is_valid_size = desired_width > 0 && desired_height > 0;

        if(!is_valid_size_format || !is_valid_size){
            std::string error_message = !is_valid_size_format ?
                "the desired_width and desired_height must be a number" :
                "the desired_width and desired_height must be bigger than 0";

            send_response(400, error_message);
            return;
        }

        ImageProcessing img_proc;
        cv::Mat image = img_proc.encoded_to_mat(encoded_data);

        if(image.cols <= 0 || image.rows <= 0){
            send_response(400, "invalid image");
            return;
        }

        cv::Mat resizedImage = img_proc.image_resizer(image, desired_width, desired_height);
        std::string encoded_resized_image = img_proc.mat_to_encoded(resizedImage);
        
        send_response(200, "success", encoded_resized_image);
    });

    as->run();

    return 0;
}