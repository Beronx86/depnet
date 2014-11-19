
#include "dependency_network.h"
#include "models/rdf_model.h"

#include<iostream>

namespace depnet
{
    DependencyNetwork::DependencyNetwork() { }

    DependencyNetwork::DependencyNetwork(
        const std::vector<std::shared_ptr<VariableSpecification> >& varSpecs,
            std::shared_ptr<Factory> factory) :
        varSpecs(varSpecs), factory(factory)
    {
    }

    DependencyNetwork::~DependencyNetwork()
    {
    }

    std::shared_ptr<GibbsIterator> DependencyNetwork::getSampler()
    {
        return gibbsIterator;
    }

    std::shared_ptr<boost::multi_array<double, 2> > DependencyNetwork::getSamples(int numSamples)
    {
        std::shared_ptr<boost::multi_array<double, 2> > result(
            new boost::multi_array<double, 2>(
                boost::extents[numSamples][this->varSpecs.size()]));
        for(unsigned int i = 0; i < numSamples; i++)
        {
            std::cout << "Advancing iterator" << std::endl;
            (*this->gibbsIterator)++;
            std::cout << "Getting a sample" << std::endl;
            SampleType sampleMap = *(*this->gibbsIterator);

            unsigned int featureCtr = 0;
            std::cout << "Assigning sampled values to variables" << std::endl;
            for(auto varSpec = this->varSpecs.begin(); varSpec != this->varSpecs.end(); ++varSpec)
            {
                (*result)[i][featureCtr] = (*sampleMap)[*varSpec];
                featureCtr++;
            }
        }

        return result;
    }

    const std::shared_ptr<ConditionalModel> DependencyNetwork::getModel(
        std::shared_ptr<VariableSpecification> varSpec) const
    {
        return this->models.at(varSpec);
    }

    void DependencyNetwork::resetSampler()
    {
        // TODO
    }

    void DependencyNetwork::train(boost::multi_array<double, 2> samples)
    {
        typedef boost::multi_array_types::index_range range;

        boost::multi_array<double, 2>::index depColumn = 0;
        for(auto varIt = varSpecs.begin(); varIt != varSpecs.end(); ++varIt)
        {
            // extract the independent variables
            std::vector<std::shared_ptr<VariableSpecification> > indepVars; 
            std::copy_if(varSpecs.begin(), varSpecs.end(), std::back_inserter(indepVars),
                [varIt](const std::shared_ptr<VariableSpecification>& v) { return v != *varIt; });

            // learn a model for the current column on all others
            std::shared_ptr<RandomForestModel> rfModel(new RandomForestModel(indepVars, *varIt, 0.1, 100));
            rfModel->train(samples, depColumn);
            models[*varIt] = rfModel;

            depColumn++;
        }

        std::shared_ptr<GibbsSampler> sampler = this->factory->createSampler(this->models, 10);
        this->gibbsIterator = this->factory->createSampleIterator(sampler, 500, 100);
    }

}

