#include <catch2/catch_all.hpp>
#include <base64.h>

TEST_CASE("Base64 encode and decode consistency")
{
    Base64Codec codec;

    std::string original_data = "Hello there!";
    std::string encoded_data = codec.encoder(original_data);
    std::string decoded_data = codec.decoder(encoded_data);
    
    REQUIRE(original_data == decoded_data);
}
