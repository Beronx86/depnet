
#pragma once

#ifndef CONDITIONAL_MODEL_H
#define CONDITIONAL_MODEL_H

#include<boost/multi_array.hpp>
#include<memory>

namespace depnet 
{
    /**
     * Specifies a set of functionality that all local conditional models 
     * should implement. Supports modeling a single variable left of the conditioning bar.
     */
    class ConditionalModel 
    {
    public:

        /**
         * Retrieves the independent variables in the order they were specified during initialization
         * @return The variables required for prediction in the same order that they should be specified for prediction
         */
        virtual const std::vector<std::shared_ptr<VariableSpecification> > & getIndependentVars() = 0;

        /**
         * Retrieves the dependent variable being modeled
         * @return The variable this model builds predictions for
         */
        virtual const std::shared_ptr<VariableSpecification> getDependentVar() = 0;

        /**
         * Retrieves the posterior density of the dependent variable given a set of independent variables.
         * This function supports discrete posterior probability mass functions only 
         * (e.g. the dependent var needs to be discrete), and not all implementations are required to 
         * support even this use case. If unsupported, DensityEstimationUnsupported is thrown.
         * @param indep The independent variables to use as evidence
         * @param posterior A reference in which to store a K-dimensional vector of posterior probabilities.
         * K is the number of levels of the dependent variable.
         */
        virtual void getClassDensity(const std::vector<double>& indep, 
                std::vector<double> & posterior) const = 0;

        /**
         * Indicates if this model supports estimation of posterior class densities.
         * If this model does not support such estimation, ConditionalModel::getClassDensity 
         * will always throw DensityEstimationUnsupported.
         * @return true if posterior mass estimation is supported, false otherwise 
         */
        virtual bool supportsClassDensity() = 0;
        
        /**
         * Predicts the dependent variable value given an 
         * instantiation of the dependent variables. 
         * @param indep A 1D input vector of length K, where K is the number of 
         * independent features specifying the model.
         */
        virtual double predict(const std::vector<double>& indep) const = 0;

        /**
         * Trains the model from a 2D data matrix.
         * @param data A 2D array of doubles representing continuous values 
         * or discrete factor levels. Data instances should stored in rows and features should be stored in columns.
         * @param dependentIndex The index of the dependent variable in the multi_array
         */
        virtual void train(const boost::multi_array<double, 2>& data, 
            boost::multi_array<double, 2>::index dependentIndex) = 0;
    };

}

#endif

