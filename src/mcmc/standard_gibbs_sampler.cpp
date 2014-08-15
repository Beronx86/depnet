
#include "standard_gibbs_sampler.h"
#include<random>
#include<iostream>
#include<limits>

namespace depnet
{
    StandardGibbsSampler::StandardGibbsSampler(const std::map<std::shared_ptr<VariableSpecification>, 
                            std::shared_ptr<ConditionalModel> >& network,
            unsigned int numChains,
            boost::optional<const std::map<std::shared_ptr<VariableSpecification>, double> > evidence,
            boost::optional<std::map<unsigned int, SampleType> > initialSamples) :
                numChains(numChains), currentChain(0), models(network)
    {
        // for now just initializing an arbitrary sample order and saving the Markov blanket
        for(auto it = network.begin(); it != network.end(); ++it)
        {
            sampleOrder.push_back(it->first);
            this->markovBlankets[it->first] = it->second->getIndependentVars();
        }

        // initialize each chain with a random initial setting if no initial samples were identified
        if(!initialSamples)
        {
            std::default_random_engine generator;
            for(unsigned int curChain = 0; curChain < numChains; curChain++)
            {
                SampleType curSample(new std::map<std::shared_ptr<VariableSpecification>, double>());
                for(auto varSpec = sampleOrder.begin(); varSpec != sampleOrder.end(); varSpec++)
                {
                    if((*varSpec)->isDiscrete())
                    {
                        curSample->insert(std::make_pair(*varSpec, rand() % (*varSpec)->getNumLevels()));
                    } else // generate from the allowable range
                    {
                        double minVal, maxVal;
                        (*varSpec)->getRange(minVal, maxVal); // can be inf
                        std::uniform_real_distribution<double> distr(0.0, 10.0);
                            //std::isinf(minVal) ? std::numeric_limits<double>::min() : minVal,
                            //std::isinf(maxVal) ? std::numeric_limits<double>::max() : maxVal);

                        double val = distr(generator);
                        curSample->insert(std::make_pair(*varSpec, val));
                    }
                }

                this->currentSamples.insert(std::make_pair(curChain, curSample));
            }
        } else
        {
            this->currentSamples = std::move(*initialSamples);
        }
    }

    std::vector<std::shared_ptr<VariableSpecification> > const& StandardGibbsSampler::getSampleOrder() const
    {
        return this->sampleOrder;
    }

    void StandardGibbsSampler::setSampleOrder(std::vector<std::shared_ptr<VariableSpecification> > sampleOrder)
    {
        this->sampleOrder = std::move(sampleOrder);
    }

    SampleType StandardGibbsSampler::sample()
    {
        SampleType curChainSample = this->currentSamples[this->currentChain];
        for(auto varIt = sampleOrder.begin(); varIt != sampleOrder.end(); ++varIt)
        {
            // build up a vector of values representing the Markov blanket
            std::vector<std::shared_ptr<VariableSpecification> > markovBlanket = this->markovBlankets[*varIt];
            std::vector<double> indepVars;
            for(auto predictorIt = markovBlanket.begin(); 
                predictorIt != markovBlanket.end(); predictorIt++)
            {
                indepVars.push_back((*curChainSample)[*predictorIt]);
            }
            double newVal = this->models[*varIt]->predict(indepVars);
            (*curChainSample)[*varIt] = newVal;
        }

        this->currentChain = (this->currentChain + 1) % this->numChains;
        return curChainSample;
    }
}

