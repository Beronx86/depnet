
#pragma once

#ifndef RDF_MODEL_H
#define RDF_MODEL_H

#include<memory>
#include<vector>

#include<boost/multi_array.hpp>

#include "alglib/dataanalysis.h"

#include "var_spec.h"
#include "conditional_model.h"

namespace depnet 
{
 
    typedef boost::multi_array<double, 2> array_type; 

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
         * @param trainRatio A value between 0 and 1 controlling the number of samples to train each tree with, 
         * with 1 indicating as many samples as were present in the training data and 0 indicating no samples at all.
         * Experiment with values in the range [0.05, 0.66] with the low end being very noisy and the high end 
         * running the risk of overfitting.
         * @param numTrees The number of trees in the forest. Recommended to be in the range [50, 100], defaulting to 100.
         */
        explicit RandomForestModel(
                    const std::vector<std::shared_ptr<VariableSpecification> >& indep, 
                    std::shared_ptr<VariableSpecification> dep, 
                    float trainRatio, int numTrees = 100);

        /** Destroys a random forest model */
        ~RandomForestModel();

        /**
         * Retrieves the independent variables in the order they were specified during initialization
         * @return The variables required for prediction in the same order that they should be specified for prediction
         */
        const std::vector<std::shared_ptr<VariableSpecification> > & getIndependentVars();

        /**
         * Retrieves the dependent variable being modeled
         * @return The variable this model builds predictions for
         */
        const std::shared_ptr<VariableSpecification> getDependentVar();

        /**
         * Retrieves the posterior density of the dependent variable given a set of independent variables.
         * This function supports discrete posterior probability mass functions only 
         * (e.g. the dependent var needs to be discrete). Throws DensityEstimationUnsupported otherwise.
         * @param indep The independent variables to use as evidence
         * @param posterior A reference in which to store a K-dimensional vector of posterior probabilities.
         * K is the number of levels of the dependent variable.
         */
        void getClassDensity(const std::vector<double>& indep, 
                std::vector<double> & posterior) const;

        /**
         * Indicates if this model supports estimation of posterior class densities.
         * This is true whenever the dependent variable is discrete. 
         * @return true if posterior mass estimation is supported, false otherwise 
         */
        bool supportsClassDensity();
        
        /**
         * Predicts the dependent variable value given an 
         * instantiation of the dependent variables. 
         * @param indep A 1D input vector of length K, where K is the number of 
         * independent features specifying the model.
         */
        /**
         * Predicts the dependent variable value given an 
         * instantiation of the dependent variables using a random decision forest. 
         * @param indep A 1D input vector of length K, where K is the number of 
         * independent features specifying the model.
         */
        double predict(const std::vector<double>& indep) const;

        /**
         * Trains the model from a 2D array of independent variable 
         * samples and a 1D array of dependent values using a random decision forest.
         * @param data A 2D array of doubles representing continuous values 
         * or discrete factor levels. Data instances should stored in rows and features should be stored in 
         * columns in the same order that indep metadata was supplied during construction.
         * @param dependentIndex The index of the dependent value in data
         */
        void train(const array_type& data, array_type::index dependentIndex);

    private:

        /** 
         * Encodes a set of independent variables in an alglib-compatible format
         * @param data The data matrix to encode
         * @param dependentIndex The index of the dependent variable in the data matrix
         * @param encoded The array to dynamically allocate and use to store the alglib-compatible data in
         * @param numRecords The number of rows, or data instances in the array view
         * @param origFeatures The number of columns, or features, in the original (pre-expansion) matrix
         * @param numFeatures The number of features in the expanded representation.
         */
        void encodeData(const array_type& data, array_type::index dependentIndex,
                std::vector<double>& encoded, int& numFeatures);

        /** The sequence of independent variables to fit a model against */
        std::vector<std::shared_ptr<VariableSpecification> > independentVars;
    
        /** The variable to build a predictor for (i.e. the single variable to the left of the conditioning bar)*/
        std::shared_ptr<VariableSpecification> dependentVar;

        /** A value between 0 and 1 controlling the number of training samples */
        float trainRatio;

        /** The number of trees to train */
        int numTrees;

        /** Decision forest which is built at train-time and used for prediction. */
        alglib::decisionforest forest;
    };

}

#endif

