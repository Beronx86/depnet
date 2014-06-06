
#pragma once

#ifndef GIBBS_ITERATOR_H
#define GIBBS_ITERATOR_H

#include <boost/iterator/iterator_facade.hpp>
#include <vector>
#include "gibbs_sampler.h"

namespace depnet {

    /**
     * An forward-traversal iterator over samples produced by Gibbs sampling
     */
    class GibbsIterator
        : public boost::iterator_facade<GibbsIterator, 
            SampleType, boost::forward_traversal_tag >
    {
     public:
        /** 
         * Creates an iterator over samples produced by a Gibbs sampler
         * @param sampler responsible for producing Gibbs samples
         * @param warmUp A number of samples to discard at the beginning of the 
         * sampling process to account for "warm up" effects
         * @param interval A number of samples to discard between each sample that is returned.
         * Accounts for autocorrelation effects
         */
        explicit GibbsIterator(std::shared_ptr<GibbsSampler> sampler, int warmUp = 0, int interval = 0);

     private:
        friend class boost::iterator_core_access;

        /**
         * Advances the sampler to the next iteration
         */
        void increment();

        /** Determines if two iterators are equal, which is true if they have they 
         * same sampler, warm up period, interval, and current sample 
         * @param other The iterator to compare this to
         */
        bool equal(GibbsIterator const& other) const;

        /** The sampler to use when retrieving samples */
        std::shared_ptr<GibbsSampler> sampler;
        
        /** The number of samples that have been retrieved from the sampler, excluding */
        long numSamples;

        /** The number of samples to discard before returning a sample */
        int warmUp;

        /** The number of samples to discard between samples */
        int autoCorrInterval;

        /**
         * Retrieves the sample at the current position
         * @return The most recent valid sample produced by the sampler
         */
        SampleType & dereference() const;

        /** The current sample */
        SampleType sample;
    };

}

#endif

