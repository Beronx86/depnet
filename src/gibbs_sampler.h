
#pragma once

#ifndef GIBBS_SAMPLER_H
#define GIBBS_SAMPLER_H

#include "var_spec.h"
#include "conditional_model.h"

#include<memory>
#include<vector>

#include<boost/optional.hpp>

namespace depnet 
{

    typedef std::shared_ptr<std::map<std::shared_ptr<VariableSpecification>, double> > SampleType;

    /**
     * Performs Gibbs sampler over a set of local conditional models
     */
    class GibbsSampler 
    {
    public: 
        /**
         * Creates a Gibbs sampler to draw samples from 
         * the variables in a particular network
         * @param network The network to draw samples from
         * @param evidence values to condition on
         * @param numChains The number of Gibbs chains to draw samples from
         * @param initialSamples Samples to use when initializing each chain.
         * Supplying reasonable initial samples is recommended when the data involves 
         * unbounded (hasRange() is false) VariableSpecification instances
         */
        GibbsSampler(const std::map<std::shared_ptr<VariableSpecification>, 
                                std::shared_ptr<ConditionalModel> >& network,
                unsigned int numChains,
                boost::optional<const std::map<std::shared_ptr<VariableSpecification>, double> > evidence =
                    boost::optional<const std::map<std::shared_ptr<VariableSpecification>, double> >(),
                boost::optional<std::map<unsigned int, SampleType> > initialSamples = 
                    boost::optional<std::map<unsigned int, SampleType> >());

        /**
         * Retrieves variables metadata in the order that sampling is performed
         * @return A sequence of variable metadata in sampling order
         */
        std::vector<std::shared_ptr<VariableSpecification> > const& getSampleOrder() const;

        /** 
         * Establishes the sample order that should be used when performing sampling
         * @param sampleOrder A vector of variable metadata specified in 
         * the same order as sampling should be performed
         */
        void setSampleOrder(std::vector<std::shared_ptr<VariableSpecification> > sampleOrder);
    
        /** 
         * Sweeps through all variables, holding their Markov blankets 
         * constant, and samples a new value for each. 
         * Chains are sampled in succession, so the first call to this function 
         * will return a sample from the first chain, the second call from the second chain, and so on.
         * @return An assignment from variable metadata to value
         */
        SampleType sample();
        
    private:
        /** The order that new values should be sampled in */
        std::vector<std::shared_ptr<VariableSpecification> > sampleOrder;

        /** A map from a variable to a fixed value for that variable used as evidence */
        std::map<std::shared_ptr<VariableSpecification>, double> evidence;

        /** The number of chains to run and generate samples from */
        unsigned int numChains;

        /** The chain that will be sampled from on the next iteration */
        unsigned int currentChain;

        /** The current assignment of variables (value) for each chain (key) */
        std::map<unsigned int, SampleType> currentSamples;

        /** The variable models to draw samples from */
        std::map<std::shared_ptr<VariableSpecification>, std::shared_ptr<ConditionalModel> > models;

        /** A cache consisting of Markov blankets for each node in the network */
        std::map<std::shared_ptr<VariableSpecification>, std::vector<std::shared_ptr<VariableSpecification> > > markovBlankets;
    };
}

#endif

