#pragma once

#include "stdint.h"
#include "string.h"

/**
 * Convert between binary and base64 encoded string.
 * @see https://github.com/dojyorin/arduino_base64
 */
namespace base64
{
    /**
     * Convert binary to base64 encoded string.
     * If input is string, cast to `uint8_t*`.
     * @example
     * ```c++
     * const uint8_t input[] = {0x17, 0x77, 0x3B, 0x11, 0x82, 0xA4, 0xC4, 0xC8};
     * auto inputLength = sizeof(input);
     * char output[base64::encodeLength(inputLength)];
     * base64::encode(input, inputLength, output);
     * ```
     */
    void encode(const uint8_t *input, size_t inputLength, char *output);

    /**
     * Calculate number of output characters.
     * @example
     * ```c++
     * const uint8_t input[] = {0x17, 0x77, 0x3B, 0x11, 0x82, 0xA4, 0xC4, 0xC8};
     * auto inputLength = sizeof(input);
     * char output[base64::encodeLength(inputLength)];
     * base64::encode(input, inputLength, output);
     * ```
     */
    size_t encodeLength(size_t inputLength);

    /**
     * Convert base64 encoded string to binary.
     * If output is string, cast to `char*`.
     * @example
     * ```c++
     * const char input[] = "F3c7EYKkxMgnvO0nB8FWVw==";
     * uint8_t output[base64::decodeLength(input)];
     * base64::decode(input, output);
     * ```
     */
    void decode(const char *input, uint8_t *output);

    /**
     * Calculate number of output bytes.
     * @example
     * ```c++
     * const char input[] = "F3c7EYKkxMgnvO0nB8FWVw==";
     * uint8_t output[base64::decodeLength(input)];
     * base64::decode(input, output);
     * ```
     */
    size_t decodeLength(const char *input);
}