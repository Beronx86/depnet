
#include "dependency_network_wrap.h"

#include<boost/multi_array.hpp>
#include<boost/python/extract.hpp>
#include<memory>

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

        DependencyNetwork::train(samplesArr);
    }
}


