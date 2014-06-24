
#pragma once

#ifndef DEPENDENCY_NETWORK_H
#define DEPENDENCY_NETWORK_H

#include<cstdlib>
#include<memory>

#include "var_spec.h"
#include "gibbs_iterator.h"

namespace depnet 
{

    /**
     * Represents a general-purpose probabilistic model, 
     * and provides functions to learn and perform inference in that model.
     * See http://machinelearning.wustl.edu/mlpapers/paper_files/HeckermanCMRK00.pdf.
     */ 
    class DependencyNetwork 
    {
    public:

        /**
         * Creates a dependency network for a set of variables
         * @param varSpecs Specifications for variables to be modeled by the network. 
         * The variables should be supplied in the same order as they will be during training.
         */
        DependencyNetwork(const std::vector<std::shared_ptr<VariableSpecification> >& varSpecs);

        /**
         * Destroys the dependency network
         */
        ~DependencyNetwork();

        /** 
         * Retrieve a sampler over the learned network model 
         * @return An iterator over warm-up and autocorrelation-corrected Gibbs samples
         */
        std::shared_ptr<GibbsIterator> getSampler();

        /**
         * Retrieves the conditional model corresponding to the variable specification
         * @param varSpec The variable specification to retrieve the model for
         * @return The model that was learned for the specified variable
         */ 
        const std::shared_ptr<ConditionalModel> getModel(
            std::shared_ptr<VariableSpecification> varSpec) const;

        /**
         * Retrieve numSamples valid samples from a Gibbs sampler 
         * @param numSamples The number of samples to extract from the sampler, 
         * after correcting for warm-up and autocorrelation
         * @return A 2D array representing numSamples instances, samples in rows and features in columns
         */
        std::shared_ptr<boost::multi_array<double, 2> > getSamples(int numSamples);

        /**
         * Resets Gibbs iteration to a new random initial state
         */
        void resetSampler();

       /** 
        * Trains the dependency network with a set of samples specified as a 2D array.
        * @param A 2D array with features stored in columns. The columns should be arranged in 
        * the same order as VariableSpecifications where supplied during construction.
        */
       void train(boost::multi_array<double, 2> samples); 
    protected:
        /** Constructor which does not require variable instantiation, to be used by subclasses */
        DependencyNetwork();

        /** Variable metadata in the same order that variables will be 
            specified during training and returned during sampling. */
        std::vector<std::shared_ptr<VariableSpecification> > varSpecs;
    private:

        /** An iterator over Gibbs samples */
        std::shared_ptr<GibbsIterator> gibbsIterator;

        /** The local conditional model for each variable */
        std::map<std::shared_ptr<VariableSpecification>, std::shared_ptr<ConditionalModel> > models;
    };

}

#endif

