#include <string>
#include <iostream>

#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/gcm.h>
#include <cryptopp/hex.h>

#include <Arduino.h>

/// @brief Encrypt some data using AES-128 in GCM mode (this encrypts the data AND authenticates the data)
std::string encryptGCM(const uint8_t *msg, size_t len, const byte *key, size_t keySize, const byte *iv, size_t ivSize, uint8_t tagSizeInBytes)
{
    using namespace CryptoPP;
    std::string ciphertext;

    GCM<AES>::Encryption e;
    e.SetKeyWithIV(key, keySize, iv, ivSize);

    AuthenticatedEncryptionFilter ef(e, new StringSink(ciphertext), false, tagSizeInBytes);
    ef.ChannelPut(DEFAULT_CHANNEL, msg, len);
    ef.ChannelMessageEnd(DEFAULT_CHANNEL);

    return ciphertext;
}

/// @brief Decrypt some data using AES-128 in GCM mode (this decrypts the data AND authenticates it)
std::string decryptGCM(const uint8_t *msg, size_t len, const byte *key, size_t keySize, const byte *iv, size_t ivSize, uint8_t tagSizeInBytes)
{
    using namespace CryptoPP;
    std::string plaintext;

    CryptoPP::GCM<CryptoPP::AES>::Decryption d;
    d.SetKeyWithIV(key, keySize, iv, ivSize);

    CryptoPP::AuthenticatedDecryptionFilter ef(d, new CryptoPP::StringSink(plaintext), false, tagSizeInBytes);
    ef.ChannelPut(CryptoPP::DEFAULT_CHANNEL, msg, len);
    ef.ChannelMessageEnd(CryptoPP::DEFAULT_CHANNEL);

    return plaintext;
}

// EVERYTHING BELOW HERE IS JUST CONVENIENCE ------------------------------------------------------

/// @brief Just a wrapper wo we can use std::string for message, key and iv and do not have to repeat reinterpret_cast over and over
inline std::string encryptGCM(const std::string &msg, const std::string &key, const std::string &iv, uint8_t tagSizeInBytes)
{
    return encryptGCM(
        reinterpret_cast<const uint8_t *>(msg.data()), msg.size(),
        reinterpret_cast<const uint8_t *>(key.data()), key.size(),
        reinterpret_cast<const uint8_t *>(iv.data()), iv.size(),
        tagSizeInBytes);
}
/// @brief Just a wrapper wo we can use std::string for message, key and iv and do not have to repeat reinterpret_cast over and over
inline std::string decryptGCM(const std::string &msg, const std::string &key, const std::string &iv, uint8_t tagSizeInBytes)
{
    return decryptGCM(
        reinterpret_cast<const uint8_t *>(msg.data()), msg.size(),
        reinterpret_cast<const uint8_t *>(key.data()), key.size(),
        reinterpret_cast<const uint8_t *>(iv.data()), iv.size(),
        tagSizeInBytes);
}

/// @brief SUPER USEFUL FOR DEBUGGING!!! Gets the hexa-decimal string of some binary data
std::string toHex(const std::string &s)
{
    using namespace CryptoPP;
    std::string output;
    HexEncoder encoder(new StringSink(output));
    StringSource(s, true, new Redirector(encoder));
    return output;
}

/// @brief Decodes a hexa-decimal string back to binary data
std::string fromHex(const std::string &hex)
{
    using namespace CryptoPP;
    std::string output;
    HexDecoder decoder(new StringSink(output));
    StringSource(hex, true, new Redirector(decoder));
    return output;
}

void setup()
{
    Serial.begin(115200); // use your baud rate from platformio.ini here !
}

void loop()
{
    std::string message = "Aah, the negotiator!";
    std::string aesKey = fromHex("647A68766468756A646B66756E6C696B6D756E7A6B66756A6E68747265746872"); // 128-bit key
    std::string iv = fromHex("6F697A686167636572616F7A7263676561677263656F697A6E6165677263696E");     // 128-bit iv

    // just in case you did not know: std::cout is re-written to Serial by PlatformIO ;)
    std::cout << "Plaintext is         : " << message << "\n";

    auto ciphertext = encryptGCM(message, aesKey, iv, 16); // 16-byte checksum/tag
    std::cout << "Encrypted+Tag is     : " << toHex(ciphertext) << "\n";

    auto recovered = decryptGCM(ciphertext, aesKey, iv, 16); // 16-byte checksum/tag
    std::cout << "Recovered message is : " << recovered << "\n";
}
