
#pragma once

#ifndef DEPENDENCY_NETWORK_H
#define DEPENDENCY_NETWORK_H

#include<cstdlib>
#include "var_spec.h"

namespace depnet {
    /**
     * Represents a general-purpose probabilistic model, 
     * and provides functions to learn and perform inference in that model.
     * See http://machinelearning.wustl.edu/mlpapers/paper_files/HeckermanCMRK00.pdf.
     */ 
    class DependencyNetwork {
    public:

        /**
         * Creates a dependency network for a set of variables
         * @param varSpecs Specifications for variables to be modeled by the network. 
         * The variables should be supplied in the same order as they will be during training.
         */
        DependencyNetwork(std::vector<std::shared_ptr<VariableSpecification> > varSpecs);

        /**
         * Destroys the dependency network
         */
        ~DependencyNetwork();

       /** 
        * Trains the dependency network with a set of samples specified as a 2D array.
        * @param A 2D array with features stored in columns. The columns should be arranged in 
        * the same order as VariableSpecifications where supplied during construction.
        */
       void train(boost::multi_array<double, 2> samples); 

         
    private:

        /** Variable metadata in the same order that variables will be 
            specified during training and returned during sampling. */
        std::vector<std::shared_ptr<VariableSpecification> > varSpecs;
    };

}

#endif

