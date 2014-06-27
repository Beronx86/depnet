
#pragma once

#ifndef CONVERSION_EXCEPTION_H
#define CONVERSION_EXCEPTION_H

#include<exception>

namespace depnet
{

    /**
     * An exception type which is thrown when problems occur converting data.
     */
    class ConversionException : public std::runtime_error
    {
    public:
        ConversionException(std::string message) : std::runtime_error(message) {}

        virtual const char* what() const throw()
        {
            return std::exception::what();
        }
    };
}


#endif

