#include <json_handler.h>

bool JsonHandler::parse(std::string json_string){
    Json::Reader reader;
    return reader.parse(json_string, value);
}

std::string JsonHandler::setup_response(int code, std::string message, std::string output_jpeg) const{
    Json::Value res;
    res["code"] = code;
    res["message"] = message;

    if(output_jpeg.length() > 0)
        res["output_jpeg"] = output_jpeg;

    return res.toStyledString();
}

std::string JsonHandler::get_encoded_data() {
    return value["input_jpeg"].asString();
}

std::pair<bool, int> JsonHandler::get_desired_value(std::string key) {
    auto result = value[key];
    bool isNumber = result.isNumeric();

    return {isNumber, isNumber ? result.asInt() : 0};
}

std::pair<bool, int> JsonHandler::get_desired_width() {
    return get_desired_value("desired_width");
}

std::pair<bool, int> JsonHandler::get_desired_height() {
    return get_desired_value("desired_height");
}