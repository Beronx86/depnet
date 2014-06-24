
#include "rdf_model.h"
#include "alglib/dataanalysis.h"
#include<vector>
#include<boost/multi_array.hpp>
#include<iostream>
#include "exceptions/density.h"

namespace depnet
{
    RandomForestModel::RandomForestModel(
            const std::vector<std::shared_ptr<VariableSpecification> >& indep, 
            std::shared_ptr<VariableSpecification> dep,
            float trainRatio, int numTrees) : 
            independentVars(indep), dependentVar(dep),
            trainRatio(trainRatio), numTrees(numTrees) { }

    RandomForestModel::~RandomForestModel() { }

    double RandomForestModel::predict(const std::vector<double>& indep) const
    {
        alglib::real_1d_array indepArray;
        indepArray.setcontent(indep.size(), indep.data());

        alglib::real_1d_array depArray;
        alglib::dfprocess(this->forest, indepArray, depArray);

        // todo: pick most likely value if discrete
        return depArray[0];
    }

    const std::vector<std::shared_ptr<VariableSpecification> > & RandomForestModel::getIndependentVars()
    {
        return this->independentVars;
    }

    const std::shared_ptr<VariableSpecification> RandomForestModel::getDependentVar()
    {
        return this->dependentVar;
    }

    void RandomForestModel::getClassDensity(const std::vector<double>& indep, 
            std::vector<double> & posterior) const
    {
        if(!this->dependentVar->isDiscrete())
            throw DensityEstimationUnsupported(std::string("Cannot retrieve class densities for ") +
                         "a non-discrete probability distribution.");

        alglib::real_1d_array indepArray;
        indepArray.setcontent(indep.size(), indep.data());

        alglib::real_1d_array depArray;
        alglib::dfprocess(this->forest, indepArray, depArray);
        
        posterior.clear();
        for(unsigned int level = 0; level < this->dependentVar->getNumLevels(); level++)
        {
            posterior.push_back(depArray[level]);
        }
    }

    bool RandomForestModel::supportsClassDensity()
    {
        return this->dependentVar->isDiscrete();
    }

    void RandomForestModel::train(const array_type& data, array_type::index dependentIndex)
    {
        int numFeatures;
        std::vector<double> encoded;
        // encode the data in a alglib-compatible manner
        this->encodeData(data, dependentIndex, encoded, numFeatures);

        // load the encoded data into alglib's 2D array
        alglib::real_2d_array dataArray;
        dataArray.setcontent(data.size(), numFeatures, encoded.data());
        std::cout << "Training w/ data: " << std::endl << dataArray.tostring(3) << std::endl;

        alglib::ae_int_t returnCode;
        alglib::dfreport trainReport;

        alglib::dfbuildrandomdecisionforest(dataArray, 
                    data.size(), // number of training samples
                    numFeatures - 1,  // number of features
                    1, // todo: number of classes/levels of the dependent variable
                    this->numTrees, 
                    this->trainRatio, 
                    returnCode, // success or failure code
                    this->forest, // decision forest, set by reference
                    trainReport); // report on training errors

        //std::cout << trainReport << std::endl;
        // todo: check return code and record training errors
    }

    void RandomForestModel::encodeData(const array_type& data, 
            array_type::index dependentIndex,
            std::vector<double>& encoded, int& numFeatures)
    {
        // to encode discrete values, we need to create a boolean feature for each level
        // here, we count the number of new features as expanded under this rule
        numFeatures = 0;
        for(auto it = independentVars.begin(); it != independentVars.end(); ++it) 
        {
            numFeatures += it->get()->isDiscrete() ? it->get()->getLevels().size() : 1;
        }
        numFeatures += dependentVar->isDiscrete() ? dependentVar->getLevels().size() : 1;

        // storing expanded features in row-major format, filling with zeros, avoiding the 
        // need to set inactive discrete levels to 0 explicitly
        encoded = std::vector<double>(numFeatures * data.size());
        for(array_type::index rowIndex = 0; rowIndex < data.size(); rowIndex++)
        {
            auto varIt = independentVars.begin();
            int featureCounter = 0;
            for(array_type::index colIndex = 0; colIndex < data.shape()[1]; colIndex++)
            {
                std::shared_ptr<VariableSpecification> var = colIndex != dependentIndex ? *varIt : dependentVar;
                int strictlyDiscrete = var->isDiscrete() && !var->isBoolean() && !var->isOrdinal();
                int numLevels = strictlyDiscrete ? var->getLevels().size() : 1;

                int currCounter = colIndex == dependentIndex ? independentVars.size() : featureCounter;

                // in the discrete case, a variable is represented by |L| features, where L is the level set.
                // we need set the appropriate element of the L-element vector to 'true' and leave the other |L| elements 'false'/0
                int writePosition = rowIndex * numFeatures + currCounter + 
                            (strictlyDiscrete ? data[rowIndex][colIndex] : 0);
                double writeValue = strictlyDiscrete ? 1 : data[rowIndex][colIndex];
                /*
                std::cout << "Dependent? " << (colIndex == dependentIndex) << std::endl;
                std::cout << "Strictly discrete? " << strictlyDiscrete << std::endl;
                std::cout << "Current counter " << currCounter << std::endl;
                std::cout << "rowIndex=" << rowIndex << ", numfeatures=" << numFeatures 
                    << ", featureCtr=" << featureCounter << std::endl;
                std::cout << "Write position " << writePosition << std::endl;
                std::cout << "Write value " << writeValue << std::endl;
                */

                encoded[writePosition] = writeValue;

                // advance to the next variable, skipped if this column was the 
                // dependent since we're iterating over only independent variables
                if(colIndex != dependentIndex)
                {
                    ++varIt;
                    featureCounter++;
                }
            }
        }
    }

}

