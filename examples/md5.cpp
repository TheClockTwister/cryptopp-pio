// This enables weak ciphers and hashes (like MD5)
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <string>
#include <iostream>

#include <cryptopp/filters.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>

#include <Arduino.h>

/// @brief Calculates the binary digest of the input data
/// @return digest (as binary, not hex!)
std::string md5Binary(const std::string &data)
{
    std::string digest;
    CryptoPP::Weak::MD5 hash;
    CryptoPP::StringSource(data, true, new CryptoPP::HashFilter(hash, new CryptoPP::StringSink(digest)));
    return digest;
}

/// @brief SUPER USEFUL FOR DEBUGGING!!! Gets the hexa-decimal string of some binary data
std::string toHex(const std::string &s)
{
    std::string output;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(output));
    CryptoPP::StringSource(s, true, new CryptoPP::Redirector(encoder));
    return output;
}

/// @brief Calculate the hex-digest of the input
/// @return hexa-decimal digest
inline std::string md5Hex(const std::string &data) { return toHex(md5Binary(data)); }

void setup()
{
    Serial.begin(115200); // use your baud rate from platformio.ini here !
}

void loop()
{
    std::string message = "Hello there...";
    auto hexDigest = md5Hex(message);

    // just in case you did not know: std::cout is re-written to Serial by PlatformIO ;)
    std::cout << "Message hash is: " << hexDigest << "\n";

    delay(1000);
}
