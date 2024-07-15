# Crypto++

This is the original source code from [cryptopp](https://github.com/weidai11/cryptopp).

## Changes made to original code from GitHub
- Removed text files
- Removed Visual Studio files
- Add `CRYPTOPP_DISABLE_ASM` and `CRYPTOPP_DISABLE_MIXED_ASM` compiler
  flags to `library.json` for ESP32 etc. to disable assembly usage

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
