#include "standard_factory.h"
#include "standard_var_spec.h"

namespace depnet
{

    std::shared_ptr<GibbsSampler> StandardFactory::createSampler(
        const std::map<std::shared_ptr<VariableSpecification>, 
            std::shared_ptr<ConditionalModel> >& network, unsigned int numChains) const
    {

    }

    std::shared_ptr<GibbsIterator> StandardFactory::createSampleIterator(
        std::shared_ptr<GibbsSampler> sampler, int warmUpPeriod, int interval) const
    {

    }

    std::shared_ptr<VariableSpecification> StandardFactory::createVariableSpec() const
    {
        return std::shared_ptr<VariableSpecification>(new StandardVariableSpecification());
    }

}


