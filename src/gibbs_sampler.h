
#pragma once

#ifndef GIBBS_SAMPLER_H
#define GIBBS_SAMPLER_H

namespace depnet {

    typedef SampleType std::map<std::shared_ptr<VariableSpecification>, double>;

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
         */
        GibbsSampler(std::shared_ptr<DependencyNetwork> network);

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
         * constant, and samples a new value for each
         * @return An assignment from variable metadata to value
         */
        SampleType sample();
    private:
        /** The order that new values should be sampled in */
        std::vector<std::shared_ptr<VariableSpecification> > sampleOrder;

        /** The current assignment of variables */
        SampleType currentSample;

        /** The network to draw samples from */
        std::shared_ptr<DependencyNetwork> network;
    };
}

#endif

