
#pragma once

#ifndef RDF_MODEL_H
#define RDF_MODEL_H

#include<memory>
#include "var_spec.h"
#include<vector>
#include<boost/multi_array.hpp>

namespace depnet 
{
    /**
     * A model used for regression or classification based on Random Decision Forests.
     * This is a wrapper around alglib.
     */
    class RandomForestModel : public ConditionalModel 
    {
    public:
        
        /**
         * Creates a model for random forests for a set of independent variables and a dependent variable
         * @param indep The sequence of independent variables to sample from. The order that variables are supplied in 
         * here should match the order that columns are supplied in when calling train.
         * @param dep The dependent variable to build a model for
         */
        explicit RandomForestModel(
                    std::vector<std::shared_ptr<VariableSpecification> > indep, 
                    std::shared_ptr<VariableSpecification> dep);

        /** Destroys a random forest model */
        ~RandomForestModel();

        /**
         * Predicts the dependent variable value given an 
         * instantiation of the dependent variables using a random decision forest. 
         * @param indep A 1D input vector of length K, where K is the number of 
         * independent features specifying the model.
         */
        double predict(std::vector<double> indep);

        /**
         * Trains the model from a 2D array of independent variable 
         * samples and a 1D array of dependent values using a random decision forest.
         * @param indep A 2D array of doubles representing continuous values 
         * or discrete factor levels. Data instances should stored in rows and features should be stored in 
         * columns in the same order that indep metadata was supplied during construction.
         * @param dep An array of doubles representing continuous values or discrete factor levels.
         */
        void train(boost::multi_array<double, 2> indep, std::vector<double> dep);
    private:

        /** The sequence of independent variables to fit a model against */
        std::vector<std::shared_ptr<VariableSpecification> > independentVars;
    
        /** The variable to build a predictor for (i.e. the single variable to the left of the conditioning bar)*/
        std::shared_ptr<VariableSpecification> dependentVar;
    };

}

#endif

