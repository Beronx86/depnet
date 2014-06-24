
#pragma once

#ifndef DENSITY_EXCEPTION_H
#define DENSITY_EXCEPTION_H

#include<exception>

namespace depnet
{

    /**
     * An exception type which thrown when a request is made to perform 
     * density estimation in an unsupported scenario (e.g. an algorithm which cannot do density estimation, 
     * a request for a PDF when only PMFs can be estimated).
     */
    class DensityEstimationUnsupported : public std::runtime_error
    {
    public:
        DensityEstimationUnsupported(std::string message) : std::runtime_error(message) {}

        virtual const char* what() const throw()
        {
            return std::exception::what();
        }

    };

}

#endif

