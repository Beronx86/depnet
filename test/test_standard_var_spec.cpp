
#define BOOST_TEST_MODULE "depnet_test"

#include <boost/test/unit_test.hpp>
#include "standard_var_spec.h"

// test construction of a variable specification to 
// ensure reasonable initial defaults
BOOST_AUTO_TEST_CASE(test_construction)
{
    depnet::StandardVariableSpecification varSpec;
    BOOST_CHECK_MESSAGE(!varSpec->hasRange(), 
        "Variable specifications should not have a range after construction.");
}



