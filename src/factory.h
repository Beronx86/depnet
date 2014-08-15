#pragma once

#ifndef FACTORY_H
#define FACTORY_H

#include "mcmc/gibbs_sampler.h"
#include "mcmc/gibbs_iterator.h"
#include "var_spec.h"
#include "models/conditional_model.h"

namespace depnet
{
    /**
     * Provides object construction
     */
    class Factory
    {
    public:
        /**
         * Creates a sampler as a map from variable 
         * specification to a conditional model
         * @param network A map from a variable to a conditional model for that variable
         * @param numChains The number of chains to run concurrently
         * @return A sampler over the specified network
         */
        virtual std::shared_ptr<GibbsSampler> createSampler(
            const std::map<std::shared_ptr<VariableSpecification>, 
                std::shared_ptr<ConditionalModel> >& network, unsigned int numChains) const = 0;

        /**
         * Creates an iterator over a Gibbs sampler.
         * @param sampler Used to produce samples from a network
         * @param warmUpPeriod A number of samples to discard at the beginning of the 
         * sampling process to account for "warm up" effects
         * @param interval A number of samples to discard between each sample that is returned
         * @return An iterator over samples
         */
        virtual std::shared_ptr<GibbsIterator> createSampleIterator(
            std::shared_ptr<GibbsSampler> sampler, int warmUpPeriod = 0, int interval = 0) const = 0;

        /**
         * Creates a variable specification of the appropriate type.
         * @return A pointer to the newly created variable specification.
         */
        virtual std::shared_ptr<VariableSpecification> createVariableSpec() const = 0;

    };
}

#endif




