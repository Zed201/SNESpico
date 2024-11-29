#pragma once

#include <stdint.h>

struct uint24_t
{
    uint8_t byte1 : 8; // Lower 8 bits
    uint8_t byte2 : 8; // Middle 8 bits
    uint8_t byte3 : 8; // Upper 8 bits

    // Constructor to initialize the 24-bit value
    uint24_t(uint32_t value = 0)
    {
        byte1 = static_cast<uint8_t>(value);         // Lower byte
        byte2 = static_cast<uint8_t>(value >> 8);    // Middle byte
        byte3 = static_cast<uint8_t>(value >> 16);   // Upper byte
    }

    // Convert to a 32-bit value (with sign extension)
    uint32_t to_uint32_t() const
    {
        return (static_cast<uint32_t>(byte3) << 16) |
               (static_cast<uint32_t>(byte2) << 8) |
               static_cast<uint32_t>(byte1);
    }

    // Conversion operator to uint32_t
    operator uint32_t() const
    {
        return to_uint32_t();
    }

    // Assignment operator from uint32_t
    uint24_t& operator=(uint32_t value)
    {
        byte1 = static_cast<uint8_t>(value);
        byte2 = static_cast<uint8_t>(value >> 8);
        byte3 = static_cast<uint8_t>(value >> 16);
        return *this;
    }

    // Assignment operator from uint16_t
    uint24_t& operator=(uint16_t value)
    {
        byte1 = static_cast<uint8_t>(value);
        byte2 = static_cast<uint8_t>(value >> 8);
        byte3 = 0;
        return *this;
    }

    // Assignment operator from uint8_t
    uint24_t& operator=(uint8_t value)
    {
        byte1 = static_cast<uint8_t>(value);
        byte2 = 0;
        byte3 = 0;
        return *this;
    }

    // Prefix increment operator
    uint24_t& operator++()
    {
        *this = uint24_t(*this + 1);
        return *this;
    }

    // Postfix increment operator
    uint24_t operator++(int)
    {
        uint24_t temp = *this;
        ++(*this);
        return temp;
    }

    // Prefix decrement operator
    uint24_t& operator--()
    {
        *this = uint24_t(*this - 1);
        return *this;
    }

    // Postfix decrement operator
    uint24_t operator--(int)
    {
        uint24_t temp = *this;
        --(*this);
        return temp;
    }

    // Comparison operators
    bool operator==(const uint24_t& other) const
    {
        return byte1 == other.byte1 && byte2 == other.byte2 && byte3 == other.byte3;
    }

    bool operator!=(const uint24_t& other) const
    {
        return !(*this == other);
    }

    // Comparison operators (for uint32_t)
    bool operator==(uint32_t value) const
    {
        return *this == uint24_t(value);
    }

    bool operator!=(uint32_t value) const
    {
        return !(*this == value);
    }

    // Comparison operators (for uint16_t)
    bool operator==(uint16_t value) const
    {
        return *this == uint24_t(value);
    }

    bool operator!=(uint16_t value) const
    {
        return !(*this == value);
    }

    // Comparison operators (for uint8_t)
    bool operator==(uint8_t value) const
    {
        return *this == uint24_t(value);
    }

    bool operator!=(uint8_t value) const
    {
        return !(*this == value);
    }
};