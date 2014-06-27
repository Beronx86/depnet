
#pragma once

#ifndef DEPENDENCY_NETWORK_WRAP_H
#define DEPENDENCY_NETWORK_WRAP_H

#include "dependency_network.h"

#include<vector>

#include<boost/python/numeric.hpp>
#include<boost/python/tuple.hpp>
#include<boost/python/list.hpp>
#include<boost/python/stl_iterator.hpp>

namespace depnet
{
    template<typename T>
    inline
    std::vector<T> to_std_vector(const boost::python::list& iterable)
    {
            return std::vector<T>( boost::python::stl_input_iterator<T>(iterable),
                                     boost::python::stl_input_iterator<T>());
    }

    /**
     * An adaptor of the dependency network base type which 
     * provides a "Pythonic" interface to the library
     */
    class PythonDependencyNetwork : public DependencyNetwork
    {
    public:
        /**
         * Creates a dependency network from a set of 
         * variable specifitions organized in a dictionary
         * @param var_specs A sequence of VariableSpecificationWrap instances
         */
        PythonDependencyNetwork(const boost::python::list& var_specs);

        /**
         * Trains the network with a 2D numpy array with data instances 
         * in rows and features in columns.
         * @param samples Instantiations of all variables to use when learning conditional models
         */
        void train(const boost::python::list& samples);
    private:
        /**
         * Converts a 2-dimensional list of samples from Python's 
         * representation to the internal numeric-only representation
         * @param samples The samples to convert from the Pythonic representation
         * @param cSamples The array to be populated with the samples
         */
        void convertData(const boost::python::list& samples, boost::multi_array<double, 2>& cSamples);
    };

}

#endif

