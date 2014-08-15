
#include "dependency_network.h"
#include "var_spec.h"
#include "factory.h"
#include "standard_factory.h"

#include<memory>
#include<vector>
#include<iostream>
#include<random>

#include "math.h"

int main(int argc, char** argv)
{
    std::vector<std::shared_ptr<depnet::VariableSpecification> > varSpecs;
    std::shared_ptr<depnet::Factory> factory(new depnet::StandardFactory());

    auto xVar = factory->createVariableSpec();
    xVar->setName("x");
    varSpecs.push_back(xVar);

    auto yVar = factory->createVariableSpec();
    yVar->setName("y");
    varSpecs.push_back(yVar);

    int numPoints = 5000;
    depnet::DependencyNetwork network(varSpecs);
    boost::multi_array<double, 2> arr(boost::extents[numPoints][2]);

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distr(0.0, 20.0);
    for(int i = 0; i < 5000; i++)
    {
        arr[i][0] = distr(generator);

        std::normal_distribution<double> norm(arr[i][0], 5);
        arr[i][1] = norm(generator);
    }

    network.train(arr);

    for(int i = 0; i < 15; i++)
    {
        std::vector<double> vals = {(double) i};
        auto varModel = network.getModel(yVar);
        double output = varModel->predict(vals);
        std::cout << output << "=f(" << i << ")" << std::endl;
    }

    network.getSamples(5000);
}

