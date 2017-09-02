#include "Bitmask.hpp"

Bitmask::Bitmask()
    : m_bits(0)
{ }

Bitmask::Bitmask(const uint32_t & bits)
    : m_bits(bits)
{ }

uint32_t Bitmask::getMask() const
{
    return m_bits;
}

void Bitmask::setMask(const uint32_t & bits)
{
    m_bits = bits;
}

bool Bitmask::matches(const Bitmask & bits)
{
    return (m_bits & bits.getMask()) == m_bits;
}

void Bitmask::setBit(const unsigned int & position)
{
    m_bits |= (1 << position);
}

void Bitmask::resetBit(const unsigned int & position)
{
    m_bits &= ~(1 << position);
}

bool Bitmask::getBit(const unsigned int & position)
{
    return (m_bits & (1 << position)) != 0;
}

void Bitmask::clear()
{
    m_bits = 0;
}
