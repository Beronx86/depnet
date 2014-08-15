
#pragma once

#ifndef GIBBS_SAMPLER_H
#define GIBBS_SAMPLER_H

#include "var_spec.h"
#include "models/conditional_model.h"

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
         * Retrieves variables metadata in the order that sampling is performed
         * @return A sequence of variable metadata in sampling order
         */
        virtual std::vector<std::shared_ptr<VariableSpecification> > const& getSampleOrder() const = 0;

        /** 
         * Establishes the sample order that should be used when performing sampling
         * @param sampleOrder A vector of variable metadata specified in 
         * the same order as sampling should be performed
         */
        virtual void setSampleOrder(std::vector<std::shared_ptr<VariableSpecification> > sampleOrder) = 0;
    
        /** 
         * Sweeps through all variables, holding their Markov blankets 
         * constant, and samples a new value for each. 
         * Chains are sampled in succession, so the first call to this function 
         * will return a sample from the first chain, the second call from the second chain, and so on.
         * @return An assignment from variable metadata to value
         */
        virtual SampleType sample() = 0;
    };
}

#endif

