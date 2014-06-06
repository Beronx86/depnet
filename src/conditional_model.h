
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
    protected:

        /**
         * Predicts the dependent variable value given an 
         * instantiation of the dependent variables. 
         * @param indep A 1D input vector of length K, where K is the number of 
         * independent features specifying the model.
         */
        virtual double predict(std::vector<double> indep) = 0;

        /**
         * Trains the model from a 2D array of independent variable 
         * samples and a 1D array of dependent values.
         * @param indep A 2D array of doubles representing continuous values 
         * or discrete factor levels. Data instances should stored in rows and features should be stored in columns.
         * @param dep An array of doubles representing continuous values or discrete factor levels.
         */
        virtual void train(boost::multi_array<double, 2> indep, std::vector<double> dep) = 0;
    };

}

#endif

