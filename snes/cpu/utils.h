#include <stdint.h>
struct uint24_t
{
    uint8_t v[3] = {0, 0, 0};

    // Construtores
    uint24_t() = default;
    uint24_t(uint32_t value) { *this = value; }  // Construtor de uint32_t

    // Operador de conversão para uint32_t
    operator uint32_t() const 
    {
        return (static_cast<uint32_t>(v[2]) << 16) |
               (static_cast<uint32_t>(v[1]) << 8) |
               static_cast<uint32_t>(v[0]);
    }

    // Operador de atribuição
    uint24_t& operator=(uint32_t value) 
    {
        v[0] = value & 0xFF;
        v[1] = (value >> 8) & 0xFF;
        v[2] = (value >> 16) & 0xFF;
        return *this;
    }

    // Operadores aritméticos
    uint24_t& operator+=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) + rhs;
        return *this;
    }

    uint24_t& operator-=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) - rhs;
        return *this;
    }

    uint24_t& operator*=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) * rhs;
        return *this;
    }

    uint24_t& operator/=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) / rhs;
        return *this;
    }

    uint24_t& operator%=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) % rhs;
        return *this;
    }

    // Operadores bitwise
    uint24_t& operator&=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) & rhs;
        return *this;
    }

    uint24_t& operator|=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) | rhs;
        return *this;
    }

    uint24_t& operator^=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) ^ rhs;
        return *this;
    }

    uint24_t& operator<<=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) << rhs;
        return *this;
    }

    uint24_t& operator>>=(uint32_t rhs) 
    {
        *this = static_cast<uint32_t>(*this) >> rhs;
        return *this;
    }

    // Operadores de incremento e decremento
    uint24_t& operator++() 
    {
        *this += 1;
        return *this;
    }

    uint24_t operator++(int) 
    {
        uint24_t temp = *this;
        ++(*this);
        return temp;
    }

    uint24_t& operator--() 
    {
        *this -= 1;
        return *this;
    }

    uint24_t operator--(int) 
    {
        uint24_t temp = *this;
        --(*this);
        return temp;
    }

    // Operadores de comparação
    friend bool operator==(const uint24_t& lhs, const uint24_t& rhs) 
    {
        return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
    }

    friend bool operator!=(const uint24_t& lhs, const uint24_t& rhs) 
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const uint24_t& lhs, const uint24_t& rhs) 
    {
        return static_cast<uint32_t>(lhs) < static_cast<uint32_t>(rhs);
    }

    friend bool operator>(const uint24_t& lhs, const uint24_t& rhs) 
    {
        return rhs < lhs;
    }

    friend bool operator<=(const uint24_t& lhs, const uint24_t& rhs) 
    {
        return !(rhs < lhs);
    }

    friend bool operator>=(const uint24_t& lhs, const uint24_t& rhs) 
    {
        return !(lhs < rhs);
    }
};
