#pragma once

#include <string>

class Base64Codec{
public:
    std::string remove_comma(std::string encoded_data);
    std::string decoder(std::string encoded_data);
    std::string encoder(std::string decoded_data);
    
private:
    const int BITS_IN_BYTE = 8;
    const int BASE64_BITS_PER_CHAR = 6;
    std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
};