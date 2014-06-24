
#include "python/dependency_network_wrap.h"

#include<locale>
#include<cctype>
#include<boost/python.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(pydepnet)
{
    class_<depnet::PythonDependencyNetwork, boost::noncopyable>("DependencyNetwork",
        init<boost::python::list const&>())
        .def("train", &depnet::PythonDependencyNetwork::train)
    ;
}


