# [Crypto++](https://github.com/weidai11/cryptopp) for [PlatformIO](https://docs.platformio.org/en/latest)

**The only cryptography library you need is [cryptopp](https://github.com/weidai11/cryptopp) created by Wei Dai! No matter the operating system or platform :)**

This is the original source code from [cryptopp](https://github.com/weidai11/cryptopp)
packaged in a format usable by the PlatformIO packet manager, so it can be used for
development on embedded devices (like ESP8266, ESP32, Arduino Uno, STM32 etc.)

# Usage

## Getting Started

1. Install this library in your PlatformIO project using the CLI or in the `platformio.ini`:
  ```bash
  pio pkg install -p "theclocktwister/crypto++@^8.9.1"
  ```
2. Un-flag the `-fno-rtti` flag and add the `-ftti` compiler flag to prevent problems with `dynamic_cast` and `typeid`, since these
   might have been disabled by the `-fno-rtti` flag.
3. Write a simple hello world program:
  ```c++
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
  ```

## Digging Deeper
Crypto++ has a really good [wiki](https://www.cryptopp.com/wiki/Main_Page), covering almost all classes and functions and
providing useful snippets to get involved right away.

You can find everything you need there, I'm sure ;)


## Common Problems

### Linker error with `dynamic_cast` and `typeid`
- This is likely to be caused by the cryptopp library depending on `dynamic_cast` and `typeid` at runtime.
- Maybe you have the `-fno-rtti` compiler flag enabled (maybe by default).
- Be sure to un-flag `-fno-rtti`
- If that is not enough, add the `-ftti` flag explicitly



# Meta Information

## Changes made to original code from GitHub
- Removed text files
- Removed Visual Studio files
- Add `CRYPTOPP_DISABLE_ASM` and `CRYPTOPP_DISABLE_MIXED_ASM` compiler
  flags to `library.json` for ESP32 etc. to disable assembly usage
- Add `-frtti` compiler flag to avoid build problems later on

## Versioning Schema
- Versioning is done in semantic format `MAJOR`.`MINOR`.`PATCH`
- `MAJOR`.`MINOR` corresponds to the version of cryptopp that is ported
- `PATCH` is used to update this package without using a new cryptopp version

## License
Taken from [cryptopp.com](https://www.cryptopp.com/):

> Crypto++ Library is copyrighted as a compilation and (as of version 5.6.2) licensed under the Boost Software License 1.0, while the individual files in the compilation are all public domain.

See original license at https://github.com/weidai11/cryptopp?tab=License-1-ov-file.

## Credits

Credits for the implementation and collection to Wei Dai, Joan Daemen, Leonard Janke,
Steve Reid, Phil Karn, Andrew M. Kuchling, Colin Plumb, Seal Woods, Chris Morgan,
Paulo Baretto, Richard De Moliner, Matthew Skala, Kevin Springle, Ronny Van Keer,
Aumasson, Neves, Wilcox-O'Hearn and Winnerlein, Aaram Yun, Han Lulu, Markku-Juhani O. Saarinen,
Daniel J. Bernstein, Jack Lloyd and Andrew Moon.
