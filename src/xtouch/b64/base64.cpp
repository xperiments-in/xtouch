#include "./arduino_base64.hpp"

namespace
{
    constexpr char CODE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    uint8_t indexOf(char search)
    {
        for (uint8_t i = 0; i < 64; i++)
        {
            if (::CODE[i] == search)
            {
                return i;
            }
        }

        return 0xFF;
    }

    void to6x4(uint8_t *input, uint8_t *output)
    {
        output[0] = (input[0] & 0xFC) >> 2;
        output[1] = ((input[0] & 0x03) << 4) + ((input[1] & 0xF0) >> 4);
        output[2] = ((input[1] & 0x0F) << 2) + ((input[2] & 0xC0) >> 6);
        output[3] = input[2] & 0x3F;
    }

    void to8x3(uint8_t *input, uint8_t *output)
    {
        output[0] = (input[0] << 2) + ((input[1] & 0x30) >> 4);
        output[1] = ((input[1] & 0x0F) << 4) + ((input[2] & 0x3C) >> 2);
        output[2] = ((input[2] & 0x03) << 6) + input[3];
    }
}

void base64::encode(const uint8_t *input, size_t inputLength, char *output)
{
    uint8_t position = 0;
    uint8_t bit8x3[3] = {};
    uint8_t bit6x4[4] = {};

    while (inputLength--)
    {
        bit8x3[position++] = *input++;

        if (position == 3)
        {
            ::to6x4(bit8x3, bit6x4);

            for (const auto &v : bit6x4)
            {
                *output++ = ::CODE[v];
            }

            position = 0;
        }
    }

    if (position)
    {
        for (uint8_t i = position; i < 3; i++)
        {
            bit8x3[i] = 0x00;
        }

        ::to6x4(bit8x3, bit6x4);

        for (uint8_t i = 0; i < position + 1; i++)
        {
            *output++ = ::CODE[bit6x4[i]];
        }

        while (position++ < 3)
        {
            *output++ = '=';
        }
    }

    *output = '\0';
}

size_t base64::encodeLength(size_t inputLength)
{
    return (inputLength + 2 - ((inputLength + 2) % 3)) / 3 * 4 + 1;
}

void base64::decode(const char *input, uint8_t *output)
{
    auto inputLength = strlen(input);
    uint8_t position = 0;
    uint8_t bit8x3[3] = {};
    uint8_t bit6x4[4] = {};

    while (inputLength--)
    {
        if (*input == '=')
        {
            break;
        }

        bit6x4[position++] = ::indexOf(*input++);

        if (position == 4)
        {
            ::to8x3(bit6x4, bit8x3);

            for (const auto &v : bit8x3)
            {
                *output++ = v;
            }

            position = 0;
        }
    }

    if (position)
    {
        for (uint8_t i = position; i < 4; i++)
        {
            bit6x4[i] = 0x00;
        }

        ::to8x3(bit6x4, bit8x3);

        for (uint8_t i = 0; i < position - 1; i++)
        {
            *output++ = bit8x3[i];
        }
    }
}

size_t base64::decodeLength(const char *input)
{
    auto inputLength = strlen(input);
    uint8_t equal = 0;

    input += inputLength - 1;

    while (*input-- == '=')
    {
        equal++;
    }

    return 6 * inputLength / 8 - equal;
}