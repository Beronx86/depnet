
#include "gibbs_iterator.h"

namespace depnet
{

    GibbsIterator::GibbsIterator(std::shared_ptr<GibbsSampler> sampler, 
        int warmUp, int interval) : sampler(sampler), numSamples(0), totalSamples(0), 
                    warmUp(warmUp), autoCorrInterval(interval)
    {
    }

    GibbsIterator::~GibbsIterator()
    {
    }

    void GibbsIterator::increment()
    {
        while(totalSamples < warmUp)
        {
            this->sampler->sample();
            totalSamples++;
        }
        while(totalSamples % autoCorrInterval != 0)
        {
            this->sampler->sample();
            totalSamples++;
        }

        this->sample = this->sampler->sample(); 
            totalSamples++;
        for(auto sampleIt = this->sample->begin(); sampleIt != this->sample->end(); sampleIt++)
            std::cout << sampleIt->first->getName() << "=" << sampleIt->second << std::endl;
    }

    SampleType const GibbsIterator::dereference() const
    {
        return this->sample;
    }

}

