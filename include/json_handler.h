#pragma once

#include <string>
#include <json/json.h>
#include <iostream>

class JsonHandler{
public:
    bool parse(std::string json_string);
    std::string setup_response(int code, std::string message, std::string output_jpeg = "") const;

    std::string get_encoded_data();
    std::pair<bool, int> get_desired_width();
    std::pair<bool, int> get_desired_height();
    std::pair<bool, int> get_desired_value(std::string key);

private:
    Json::Value value;
};