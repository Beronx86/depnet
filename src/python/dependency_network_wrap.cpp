
#include "dependency_network_wrap.h"
#include "exceptions/conversion.h"

#include<boost/multi_array.hpp>
#include<boost/python/extract.hpp>
#include<memory>
#include<sstream>

namespace depnet
{
    PythonDependencyNetwork::PythonDependencyNetwork(const boost::python::list& var_specs) : 
        DependencyNetwork()
    {
       this->varSpecs = to_std_vector<std::shared_ptr<VariableSpecification> >(var_specs);
    }

    void PythonDependencyNetwork::train(const boost::python::list& samples)
    {
        boost::multi_array<double, 2> samplesArr;
        this->convertData(samples, samplesArr);
        DependencyNetwork::train(samplesArr);
    }

    void PythonDependencyNetwork::convertData(
        const boost::python::list& samples, boost::multi_array<double, 2>& cSamples)
    {
        for(boost::python::ssize_t recordIndex = 0; 
                recordIndex < boost::python::len(samples); recordIndex++) 
        {
            // make sure this is a 2-d array of lists
            boost::python::extract<boost::python::list> listExtractor(samples[recordIndex]);

            if(!listExtractor.check())
                throw ConversionException("Expecting a training data to be supplied as a list of lists.");
            boost::python::list record = listExtractor();

            if(boost::python::len(record) != this->varSpecs.size())
            {
                std::stringstream ss;
                ss << "Training sample " << (recordIndex + 1) << " has " << 
                            boost::python::len(record) << " features, but " << 
                            this->varSpecs.size() << " variables were specified.";
                throw ConversionException(ss.str());
            }

            for(auto specIt = this->varSpecs.begin(); 
                specIt != this->varSpecs.end(); ++specIt)
            {

            }
        }
    }
}


