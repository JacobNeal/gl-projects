#ifndef BITMASK_HPP
#define BITMASK_HPP

#include <stdint.h>

class Bitmask
{
    public:
        Bitmask();
        Bitmask(const uint32_t & bits);

        uint32_t getMask() const;
        void setMask(const uint32_t & bits);

        bool matches(const Bitmask & bits);

        void setBit(const unsigned int & position);
        void resetBit(const unsigned int & position);
        bool getBit(const unsigned int & position);

        void clear();

    private:
        /****************************************
         * Data members
        ****************************************/
        uint32_t  m_bits;
};

#endif
