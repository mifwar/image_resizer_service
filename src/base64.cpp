#include <base64.h>

std::string Base64Codec::remove_comma(std::string encoded_data){
    int pos = encoded_data.find(',');
    return pos != std::string::npos ? encoded_data.substr(pos + 1) : encoded_data;
}

std::string Base64Codec::decoder(std::string encoded_data){
    int length_of_bits = 0;
    int accumulated_bits = 0;
    std::string decoded_data;

    std::string clean_encoded_data = remove_comma(encoded_data);

    for(unsigned char c : clean_encoded_data){
        int pos = base64_chars.find(c);

        if(pos == std::string::npos)
            continue;

        accumulated_bits = accumulated_bits << BASE64_BITS_PER_CHAR | pos;
        length_of_bits += 6;

        if(length_of_bits >= BITS_IN_BYTE){
            int remaining_bits = length_of_bits - BITS_IN_BYTE;
            int bits_to_save = accumulated_bits >> remaining_bits;
            decoded_data += static_cast<unsigned char>(bits_to_save);

            int shifter = (1 << remaining_bits) - 1;
            accumulated_bits &= shifter;

            length_of_bits -= BITS_IN_BYTE;
        }
    }

    return decoded_data;
}

std::string Base64Codec::encoder(std::string decoded_data){
    int length_of_bits = 0;
    int accumulated_bits = 0;
    std::string encoded_data;

    for(unsigned char c : decoded_data){
        accumulated_bits = accumulated_bits << BITS_IN_BYTE | c;
        length_of_bits += BITS_IN_BYTE;

        while(length_of_bits >= BASE64_BITS_PER_CHAR){
            int remaining_bits = length_of_bits - BASE64_BITS_PER_CHAR;
            int index = (accumulated_bits >> remaining_bits);
            encoded_data += base64_chars[index];

            int shifter = (1 << remaining_bits) - 1;
            accumulated_bits &= shifter;

            length_of_bits -= BASE64_BITS_PER_CHAR;
        }
    }

    if(length_of_bits > 0){
        int remaining_bits = BASE64_BITS_PER_CHAR - length_of_bits;
        int index = (accumulated_bits << remaining_bits);
        encoded_data += base64_chars[index];

        while(encoded_data.size() % 4 != 0) {
            encoded_data += '=';
        }
    }

    return encoded_data;
}